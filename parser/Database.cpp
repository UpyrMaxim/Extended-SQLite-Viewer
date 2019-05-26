//
// Created by denis on 15.05.19.
//

//#include <shared_mutex>
#include "Database.h"
//#include "DB_Structures.cpp"


Database::Database(unsigned char *buffer) {
    db_header = reinterpret_cast<SQLite_header*>(buffer);
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
    auto btree_header = reinterpret_cast<Btree_header*>(pages[number]);
    if (btree_header->flag == 13){
        std::string parsed_data;
        size_t freeblock_offset = btree_header->get_first_freeblock_position();
        auto freeblock_header = reinterpret_cast<FreeBlock_header *>(pages[number] + freeblock_offset);
#pragma  omp critical (first)
        std::cout << "Deleted data on freeblock:" << std::endl;
        for (;;) {
            for (size_t i{0}; i < freeblock_header->get_length(); i++) {
                std::cout << pages[number][freeblock_offset + i];
                parsed_data += pages[number][freeblock_offset + i];
            };
            std::cout << std::endl;
            freeblock_offset = freeblock_header->get_next_offset();
            if (freeblock_offset == 0) break;
            freeblock_header = reinterpret_cast<FreeBlock_header *>(pages[number] + freeblock_header->get_next_offset());
        }
#pragma omp critical (second)
        deleted_data.emplace_back(std::pair<int,std::string>(number,parsed_data));
    }
}


std::vector<std::pair<int,std::string>> Database::scan_freeblocks() {
    omp_set_num_threads(std::thread::hardware_concurrency());
#pragma omp parallel for
    for (size_t it = 0;it < db_header->get_pages_amount(); it++){
    parse_page(it);
    }
    return deleted_data;
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
    std::vector<std::pair<int,std::string>> tables_map;
    size_t found = 0;
    while (found != std::string::npos){
        found = header_page.find("CREATE TABLE",found + 1);
        if (found!=std::string::npos) {
            tables_map.emplace_back(std::pair<int, std::string>((int) header_page[found - 1],
                    header_page.substr(found + 12, header_page.find('(', found)  - found - 12 )));
        }
    }

    bool unchecked_pages = true;

    while(unchecked_pages){
        for (auto it : tables_map){
            auto page = pages[it.first-1];
            auto page_header = reinterpret_cast<Btree_header*>(page);
            if (page_header->flag == 13) {
                unchecked_pages = false;
            }
            if (page_header->flag == 5){
                size_t cell_number = page_header->get_cells_number();
                size_t cells_offset[cell_number];
                for (size_t i{0}; i < cell_number; i++){
                    cells_offset[i] = (page[13+i*2] << 0) | (page[14+i*2] << 8);
                }

                for (auto i : cells_offset) {
                    int child_page_number =
                            (page[i] << 0) | (page[i + 1] << 8) | (page[i + 2] << 16) |
                            (page[i + 3] << 24);
                    tables_map.emplace_back(std::pair<int, std::string>(child_page_number - 1, it.second));
                    unchecked_pages = true;
                }
                it.first = 0;
            }
        }
    }

    tables_pages = tables_map;
//    for (auto it : tables_map){
//        std::cout << "Binded page: " << it.first << " Table name:" << it.second << std::endl;
//    }


}


std::vector<std::string> Database::get_deleted_data_from_table(std::string table_name) {
    std::vector<std::string> deleted_data_from_table;
    for (auto it:tables_pages){
        if(it.second == table_name){
            for (auto iterator : deleted_data){
                if (iterator.first == it.first){
                    deleted_data_from_table.push_back(iterator.second);
                }
            }
        }
    }
}


