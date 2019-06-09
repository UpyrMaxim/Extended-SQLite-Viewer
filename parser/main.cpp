#include <iostream>
#include <functional>
#include "Database.h"
#include "FreeBlock_parser.h"


int main() {
    auto db = new Database("testing3.db");
    db->parse_database();
//    db->reset_path("testing2.db");
    db->parse_database();
    db->print_db_header();
    for (auto it : db->get_tables_pages()){
        std::cout << "You have table " << it.first << std::endl;
    }
    auto data = db->get_all_raw_deleted_data();
    for (auto page : data){
        std::cout << "Data from page " << page.first << std::endl;
        for (auto freeblock : page.second){
            for (auto byte : freeblock){
                std::cout << byte;
            }
            std::cout << std::endl;
        }
    }

    auto raw_data = db->get_raw_data("table1");

    for (auto record : raw_data){
        for (auto byte : record){
            std :: cout << std::hex << (int)byte << ' ';
        }
    }


    std::cout << std::endl;
    std::vector<std::string> types = {"INT","TEXT","BLOB","FLOAT"};
    std::cout << "parsed data: "<< std::endl;
    auto parsed_data = db->get_parsed_data("table1", types);
    for (auto page : parsed_data){
        for (auto record : page){
            std::cout << record << std::endl;
        }
    }

    delete db;
}
