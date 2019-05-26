#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Database.h"

int main() {
//    std::unique_ptr<unsigned char[]> buffer(new unsigned char[max_data_length]);
//    std::ifstream file("sqlite_dump.sqlite", std::ios_base::binary | std::ios::ate);
//    std::streamsize size = file.tellg();
//    file.seekg(0, std::ios::beg);
//
//    file.read((char*)&buffer[0], sizeof(sqlite_header));
//    file.read((char*)&buffer[0], size);
    Database db("deleteteddata.db");
    db.print_db_header();
    //db.identify_tables();
    //db.scan_freeblocks();
    //db.get_deleted_data_from_table("testing2");
    return 0;
}