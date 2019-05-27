#include <iostream>
#include "Database.h"

int main() {
    Database db("deleteddata.db");
    db.print_db_header();
    db.identify_tables();
    db.scan_freeblocks();
    auto data = db.get_deleted_data_from_table("Testing2");


    std::cout << "DATA from Testing2:" << std::endl;
    for (auto &it : data){
        std::cout << it << std::endl;
    }
    return 0;
}