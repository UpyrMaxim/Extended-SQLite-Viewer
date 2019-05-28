#include <iostream>
#include "Database.h"



std::string freeblock_cell_parse(std::string freeblock){
    size_t freeblock_size = (freeblock[0] << 0) | (freeblock[1] << 8);
    std::cout << "block size: " << freeblock_size << std::endl;
    return "bullshit";
}




int main() {
    auto db = new Database("/home/denis/CLionProjects/Extended-SQLite-Viewer/parser/cmake-build-debug/deleteddata.db");
    db->print_db_header();
    db->identify_tables();
    db->scan_freeblocks();
    auto data = db->get_deleted_data_from_table("Testing2");


//    std::cout << "DATA from Testing1:" << std::endl;
//    for (auto &it : data){
//        std::cout << "FreeBlock content: " << std::endl;
//        std::cout << freeblock_cell_parse(it) << std::endl;
//    }
    delete db;
    return 0;
}
