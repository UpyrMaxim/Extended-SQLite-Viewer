#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Database.h"


constexpr size_t max_data_length = 1024 * 1024 * 100;




int main() {
    std::unique_ptr<unsigned char[]> buffer(new unsigned char[max_data_length]);
    std::ifstream file("sqlite_dump.sqlite", std::ios_base::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

//    file.read((char*)&buffer[0], sizeof(sqlite_header));
    file.read((char*)&buffer[0], size);
    Database db(buffer.get());
    db.identify_tables();
    //db.print_db_header();
    //auto vec = db.scan_freeblocks();
    return 0;
}