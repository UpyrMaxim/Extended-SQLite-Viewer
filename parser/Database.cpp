//
// Created by denis on 15.05.19.
//

#include "Database.h"


Database::Database(unsigned char *buffer) {
    db_header = reinterpret_cast<SQLite_header*>(buffer);
    auto pages_amount = db_header->get_pages_amount();
    auto page_size = db_header->get_database_page_size();
    for (int i{1}; i < pages_amount; i++){
        auto page = new unsigned char[page_size];
        for (int j{0}; j < page_size; j++ ){
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


void Database::print_header() {
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

void Database::scan_freeblocks() {
    for (auto it : pages){
        auto btree_header = reinterpret_cast<Btree_header*>(it);
        btree_header->print_btree_header();
        if (btree_header->flag == 13){
            std::cout << "First freeblock pos: " << btree_header->get_first_freeblock_position() << " First cell pos:" << btree_header->get_cell_position() << std::endl;
            std::for_each(it + btree_header->get_first_freeblock_position(),it + btree_header->get_cell_position(),[](unsigned char &ch){
                if (ch != 0)
                    std::cout << ch;
                });
        }
    }
}