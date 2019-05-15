#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Database.h"


static int max_data_length = 65536;




int main() {
    unsigned char buffer[max_data_length];
    std::ifstream file("my_db.sqlite", std::ios_base::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

//    file.read((char*)&buffer[0], sizeof(sqlite_header));
    file.read((char*)&buffer[0], size);
    Database db(buffer);
    db.print_header();
    db.scan_freeblocks();



//    auto header2 = reinterpret_cast<btree_header*>(buffer + sizeof(sqlite_header) + bytes_reserved);
//    std::cout << "test1: " << (int)header2->flag << std::endl;
//    std::cout << "Amount of cells on the page: " << header2->get_amount_of_pages() << std::endl;
//    std::cout << "Start of first cell: " << std::hex << header2->get_cell_position() << std::endl;
//    std::cout << "First freeblock position: "  << header2->get_first_freeblock_position() << std::endl;
//    std::cout << "Fragmented free bytes: " << (int)header2->fragmented_free_bytes << std::endl;
//
//
//
//    auto header3 = reinterpret_cast<btree_header*>(buffer + header->get_database_page_size());
//    std::cout << "page 2 btree header flag: " << (int)header3->flag << std::endl;
//    std::cout << "Amount of cells on the page: " << header3->get_amount_of_pages() << std::endl;
//    std::cout << "Start of first cell: " << std::hex << header3->get_cell_position() << std::endl;
//    std::cout << "First freeblock position: "  << header3->get_first_freeblock_position() << std::endl;
//    std::cout << "Fragmented free bytes: " << (int)header3->fragmented_free_bytes << std::endl;
//
//    std::for_each(buffer+header->get_database_page_size(),buffer + 2*header->get_database_page_size(),[](unsigned char &ch){
//        if (ch != 0)
//            std::cout << ch;
//    });


    return 0;
}