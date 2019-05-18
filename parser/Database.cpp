//
// Created by denis on 15.05.19.
//

#include <shared_mutex>
#include "Database.h"


Database::Database(unsigned char *buffer) {
    db_header = reinterpret_cast<SQLite_header*>(buffer);
    auto pages_amount = db_header->get_pages_amount();
    auto page_size = db_header->get_database_page_size();
    for (size_t i{1}; i < pages_amount; i++){
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

void Database::parse_page(unsigned char* page){
    auto btree_header = reinterpret_cast<Btree_header*>(page);
    if (btree_header->flag == 13){
        std::string parsed_data;
        size_t freeblock_offset = btree_header->get_first_freeblock_position();
        auto freeblock_header = reinterpret_cast<FreeBlock_header *>(page + freeblock_offset);
#pragma  omp critical (first)
        std::cout << "Deleted data on freeblock:" << std::endl;
        for (;;) {
            for (size_t i{0}; i < freeblock_header->get_length(); i++) {
                std::cout << page[freeblock_offset + i];
                parsed_data += page[freeblock_offset + i];
            };
            std::cout << std::endl;
            freeblock_offset = freeblock_header->get_next_offset();
            if (freeblock_offset == 0) break;
            freeblock_header = reinterpret_cast<FreeBlock_header *>(page + freeblock_header->get_next_offset());
        }
#pragma omp critical (second)
        deleted_data.push_back(parsed_data);
    }
}


std::vector<std::string> Database::scan_freeblocks() {
    omp_set_num_threads(std::thread::hardware_concurrency());
#pragma omp parallel for
    for (size_t it = 0;it < db_header->get_pages_amount()-1; it++){
    parse_page(pages[it]);
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