#include <iostream>
#include <functional>
#include "Database.h"
#include "FreeBlock_parser.h"
//
//int to_little_endian (uint8_t *big_endian, int size) {
//    int lil_endian = 0;
//    auto big_end = big_endian;
//    int offset = 0;
//    for (int i{size - 1}; i >= 0; i--) {
//        lil_endian |= (big_end[i] << offset);
//        offset += 8;
//    }
//    return lil_endian;
//}
//
//bool compare_values_with_type (int value, std::string type){
//    if ((type == "INT") && ((value >= 0 && value <= 6) || (value == 0))) return true;
//    if ((type == "FLOAT") && (value == 7 || value == 0)) return true;
//    if ((type == "BLOB") &&  (value > 12 && ((value % 2) == 0))) return true;
//    return (type == "TEXT") && ((value > 13 && ((value % 2) == 1)));
//};
//
//int find_types_values_match(std::vector<uint8_t> freeblock, std::vector<std::string> types_sequence) {
//    size_t freeblock_size = (freeblock[3] << 0) | (freeblock[2] << 8);
//    //std::cout << "block size: " << freeblock_size << std::endl;
//    bool flag = true;
//    int variable_length = 4;
//    for (int x{3}; x < (freeblock_size - 3); x++){
//        for (auto it : types_sequence){
//            flag *= compare_values_with_type((int)freeblock[x],it);
//            x++;
//        }
//        if (flag){
//            variable_length = x - types_sequence.size();
//            break;
//        }
//        flag = true;
//        x-=types_sequence.size();
//    }
//    std::cout << "variable length of this freblock is:" << variable_length << std::endl;
//    return variable_length;
//}
//
//std::string parse_free_block(std::vector<uint8_t> freeblock, std::vector<std::string> types_sequense){
//    auto x = find_types_values_match(freeblock,types_sequense);
//    int reserved_global = 0;
//    int unreaded_data_offset = x + types_sequense.size();
//    for (int i{0}; i < types_sequense.size(); i++, x++) {
//        int value = (int) freeblock[x];
//        int data_length = 0;
//        if (value < 5){
//            data_length = value;
//        }
//        if (value == 5){
//            data_length = 6;
//        }
//        if (value == 6) {
//            data_length = 8;
//        }
//        if (value == 7){
//            data_length = 8;
//        }
//        if (value > 12){
//            data_length = static_cast<int>((value - 12) / 2);
//        }
//
//
//        std::cout << std::endl << "We think the data of type " << types_sequense[i] << " in this bytes: " << std::endl;
//        for (int j{0}; j < data_length; j ++){
//            std::cout << std::hex << (int)freeblock[unreaded_data_offset + j] << " ";
//        }
//
//
//        if(value < 7){
//           uint8_t big_endian[data_length];
//            for (int j{0}; j < data_length; j ++){
//                big_endian[j] = (freeblock[unreaded_data_offset + j]);
//            }
//            std :: cout << "Int in lil endian is " << std::dec << to_little_endian(big_endian, data_length);
//        }
//
//        if (value > 12){
//            std::cout << "TEXT/BLOB is like this: " << std::endl;
//            for (int j{0}; j < data_length; j ++){
//                std::cout << freeblock[unreaded_data_offset + j];
//            }
//        }
//
//
//
//        unreaded_data_offset += data_length;
//
//    }
//    return "    \n";
//}




int main() {
    auto db = new Database();
    db->reset_path("testing3.db");
    db->parse_database();
    for (auto str : db->get_raw_data("table2")){
        std::cout << "RAW data from freeblock:\n" << str << std::endl;
    }


    std::vector<std::string> types = {"INT","TEXT", "TEXT"};
    for (auto pair : db->get_parsed_data("table2", types)){
        std::cout << "We got type " << pair.first << " and data in it is: " << pair.second << std::endl;
    }

//    db->print_db_header();
//    db->identify_tables();
//    db->scan_freeblocks();
//    auto all_data = db->get_deleted_data();
//    auto data = db->get_deleted_data_from_table("table2");
//    std::vector<std::string> types = {"INT","TEXT", "TEXT"};
//
//
//    for (auto pages : all_data){
//        std::cout << std::endl;
//        for (auto freeblock : pages.second){
//            for (auto byte : freeblock){
//                std :: cout << byte;
//            }
//        }
//    }
//
//
//    std::cout << "DATA from table3:" << std::endl;
//    int i{0};
//    for (auto freeblock : data ){
//       FreeBlock_parser::parse_free_block(freeblock,types);
//            for (auto byte : freeblock){
//                std::cout << std::hex << (int)byte << " ";
//            }
//            std::cout << std::endl;
//            for (auto byte : freeblock){
//            std::cout << byte << " ";
//            }
//        }

    delete db;
    return 0;
}
