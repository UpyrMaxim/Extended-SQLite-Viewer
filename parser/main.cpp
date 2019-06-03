#include <iostream>
#include <functional>
#include "Database.h"
#include "FreeBlock_parser.h"


int main() {
    auto db = new Database();
    db->reset_path("places.sqlite");
    db->parse_database();
    db->print_db_header();
    for (auto it : db->get_tables_pages()){
        std::cout << "You have table " << it.first << std::endl;
    }
   for (auto str : db->get_raw_data("qlite_sta")){
        std::cout << "RAW data from freeblock:\n" << str << std::endl;
    }
//
//
//    std::vector<std::string> types = {"INT","TEXT", "TEXT"};
//    for (auto pair : db->get_parsed_data("table2", types)){
//        std::cout << "We got type " << pair.first << " and data in it is: " << pair.second << std::endl;
//    }



    delete db;
    return 0;
}
