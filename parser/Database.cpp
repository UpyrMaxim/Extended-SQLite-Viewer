//
// Created by denis on 15.05.19.
//

#include "Database.h"
//#include "DB_Structures.cpp"


Database::Database(std::string file_name) {
    std::ifstream file(file_name, std::ios_base::binary | std::ios::ate);
    if (!file){
        throw "no such file";
    };
    std::streamsize size = file.tellg();
    buffer.resize(size);
    file.seekg(0, std::ios::beg);
    file.read(buffer.data(), size);
    db_header = reinterpret_cast<SQLite_header*>(buffer.data());
    unsigned long pages_amount = db_header->get_pages_amount();
    auto page_size = db_header->get_database_page_size();
    for (size_t i{0}; i < pages_amount; i++){
        auto page = new unsigned char[page_size];
        for (size_t j{0}; j < page_size; j++ ){
            page[j] = buffer[j + i*page_size];
        }
        pages.emplace_back(page);
    }
}

Database::~Database() {
    for (auto it : pages){
        delete[] it;
    }
}


void Database::print_db_header() {
    std::cout << "The header string: \"SQLite format 3\\000\": " << db_header->get_header() << std::endl;
    std::cout << "The database page size in bytes: " << db_header->get_database_page_size() << std::endl;
    std::cout << "Leaf payload fraction: "<< db_header->leaf_payload_fraction << std::endl;
    std::cout << "File change counter: " << db_header->get_file_change_counter() << std::endl;
    std::cout << "Amount of pages: " << db_header->get_pages_amount() << std::endl;
    std::cout << "Bytes resevred: " << db_header->reserves_bytes_after_header << std::endl;
    std::cout << "Total number of freelist pages: " << db_header->get_total_number_of_freelist_pages() << std::endl;
    std::cout << "First freelist page number : " << db_header->get_first_freelist_number() << std::endl;
    std::cout << "Size of sqlite db header: " << sizeof(SQLite_header) << std::endl;
}

void Database::parse_page(int number){
    auto page = pages[number];
    auto btree_header = reinterpret_cast<Btree_header*>(page);
    if (btree_header->flag == 13){
        size_t freeblock_offset = btree_header->get_first_freeblock_position();
        auto freeblock_header = reinterpret_cast<FreeBlock_header *>(page + freeblock_offset);
        std::vector<std::vector<uint8_t >> freeblocks_vector;
        for (;;) {
            std::vector<uint8_t> free_block_data;
            for (size_t i{0}; i < freeblock_header->get_length(); i++) {
                free_block_data.push_back(page[freeblock_offset + i]);
            };
            freeblocks_vector.emplace_back(free_block_data);
//          free_block_data.clear();
            freeblock_offset = freeblock_header->get_next_offset();
            if (freeblock_offset == 0) break;
            freeblock_header = reinterpret_cast<FreeBlock_header*>(page + freeblock_header->get_next_offset());
        }
#pragma omp critical
        deleted_data.emplace(number + 1, freeblocks_vector);
    }
}


void Database::scan_freeblocks() {
    omp_set_num_threads(std::thread::hardware_concurrency());
    #pragma omp parallel for
    for (int it = 0;it < db_header->get_pages_amount(); it++){
    parse_page(it);
    }
//
//    for (auto it : deleted_data) {
//        for (auto i : it.second) {
//            std::cout << "Page: " << it.first << " Data from page: " << i << std::endl;
//        }
//    }
}

size_t Database::to_little_endian (uint8_t *big_endian, int size) {
    size_t lil_endian = 0;
    auto big_end = big_endian;
    int offset = 0;
    for (int i{size-1}; i >= 0; i--){
        lil_endian |= (big_end[i]<<offset);
        offset+=8;
    }
    return lil_endian;
}


void Database::identify_tables() {
    std::string header_page;
    for (size_t i{0}; i < db_header->get_database_page_size(); i++ ){
        header_page += pages[0][i];
    }
    std::map<std::string,std::vector<int>> tables_map;
    size_t found = 0;
    while (found != std::string::npos){
        found = header_page.find("CREATE TABLE",found + 1);
        if (found!=std::string::npos) {
            std::vector<int> vec;
            vec.push_back(header_page[found - 1]);
            tables_map.emplace(header_page.substr(found + 14, header_page.find('(', found)  - found - 16 ), vec);
        }
    }

    bool unchecked_pages = true;

    while(unchecked_pages){
        for (auto it : tables_map) {
            for (auto i : it.second) {
                auto page = pages[i-1];
                auto page_header = reinterpret_cast<Btree_header *>(page);
                if (page_header->flag == 13) {
                    unchecked_pages = false;
                }
                if (page_header->flag == 5) {
                    size_t cell_number = page_header->get_cells_number();
                    size_t cells_offset[cell_number];
                    for (size_t i{0}; i < cell_number; i++) {
                        cells_offset[i] = (page[13 + i * 2] << 0) | (page[14 + i * 2] << 8);
                    }

                    for (auto j : cells_offset) {
                        int child_page_number =
                                (page[j] << 0) | (page[j + 1] << 8) | (page[j + 2] << 16) |
                                (page[j + 3] << 24);
                        it.second.push_back(child_page_number - 1);
                        unchecked_pages = true;
                    }
                    i = 0;
                }
            }
        }
    }

//    for (auto it : tables_map){
//        std::cout << "Binded page: " << it.first << " Table name:" << it.second << std::endl;
//    }
    tables_pages = std::move(tables_map);
}


std::vector<std::vector<uint8_t >> Database::get_deleted_data_from_table(std::string table_name) {
    std::vector<std::vector<uint8_t >> deleted_data_from_table;
    if (tables_pages.find(table_name) == tables_pages.end()){
        std::cout << "no table with that name" << std::endl;
    };
    for (auto it : tables_pages[table_name]){
        for (auto i : deleted_data[it]) {
            deleted_data_from_table.emplace_back(i);
        }
    }
    return deleted_data_from_table;
}


