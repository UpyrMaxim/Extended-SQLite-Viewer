//
// Created by denis on 31.05.19.
//

#ifndef PARSER_FREEBLOCK_PARSER_H
#define PARSER_FREEBLOCK_PARSER_H


#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

class FreeBlock_parser {
public:
    static int to_little_endian(uint8_t*,int);
    static bool compare_values_with_type (int, std::string);
    static int find_types_values_match(std::vector<uint8_t>, std::vector<std::string>);
    static std::vector<std::pair<std::string,std::string>> parse_free_block(std::vector<uint8_t> freeblock, std::vector<std::string> types_sequense);
};


#endif //PARSER_FREEBLOCK_PARSER_H
