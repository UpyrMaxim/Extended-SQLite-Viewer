//
// Created by denis on 31.05.19.
//

#include "FreeBlock_parser.h"


int FreeBlock_parser::to_little_endian (std::vector<uint8_t> &big_endian, int size) {
    int lil_endian = 0;
    auto big_end = big_endian;
    int offset = 0;
    for (int i{size - 1}; i >= 0; i--) {
        lil_endian |= (big_end[i] << offset);
        offset += 8;
    }
    return lil_endian;
}

bool FreeBlock_parser::compare_values_with_type (int value, std::string type){
    if ((type == "INT") && ((value >  0 && value <= 6))) return true;
    if ((type == "FLOAT") && (value == 7 || value == 0)) return true;
    return (((type == "TEXT") || (type == "BLOB")) && (value > 12));
};

int FreeBlock_parser::find_types_values_match(std::vector<uint8_t> freeblock, std::vector<std::string> types_sequence) {
    size_t freeblock_size = freeblock.size();
    if (freeblock_size < types_sequence.size()){
        return 0;
    }
    //std::cout << "block size: " << freeblock_size << std::endl;
    bool flag = true;
    int variable_length = 0;
    for (int x{3}; x < (freeblock_size - 3); x++){
        for (auto it : types_sequence){
            flag *= compare_values_with_type((int)freeblock[x],it);
            x++;
        }
        if (flag){
            variable_length = x - types_sequence.size();
            break;
        }
        flag = true;
        x-=types_sequence.size();
    }
    //std::cout << "variable length of this freblock is:" << variable_length << std::endl;
    return variable_length;
}

std::vector<std::pair<std::string,std::string>> FreeBlock_parser::parse_free_block(std::vector<uint8_t> freeblock, std::vector<std::string> types_sequense){
    std::vector<std::pair<std::string,std::string>> data_from_freeblock;
    unsigned long unreaded_data_offset = 0;
    std::vector<uint8_t > sliced_cell = freeblock;
    int cell_start = 1;
    while ( sliced_cell.size() > types_sequense.size() * 2  ) {
        sliced_cell = std::vector<uint8_t>(sliced_cell.begin() + unreaded_data_offset, sliced_cell.end());
        auto types = types_sequense;
        cell_start = find_types_values_match(sliced_cell, types);
        if (cell_start == 0) {
            types = std::vector<std::string>(types.begin() + 1, types.end());
            cell_start = find_types_values_match(sliced_cell, types);
            data_from_freeblock.emplace_back(std::pair<std::string, std::string>(types_sequense[0], "can't parse data"));
        if (cell_start == 0) {
            return data_from_freeblock;
        }
    }

        unreaded_data_offset = cell_start + types.size();
        for (int i{0}; i < types.size(); i++, cell_start++) {
            int value = (int) sliced_cell[cell_start];
            int data_length = 0;
            if (value < 5) {
                data_length = value;
            }
            if (value == 5) {
                data_length = 6;
            }
            if (value == 6) {
                data_length = 8;
            }
            if (value == 7) {
                data_length = 8;
            }
            if (value > 12) {
                data_length = (value - 12) / 2;
            }


//        std::cout << std::endl << "We think the data of type " << types_sequense[i] << " in this bytes: " << std::endl;
//        for (int j{0}; j < data_length; j ++){
//            std::cout << std::hex << (int)freeblock[unreaded_data_offset + j] << " ";
//        }


            if (value < 7) {
                std::vector<uint8_t> big_endian;
                big_endian.resize(static_cast<size_t>(data_length));
                if (unreaded_data_offset + data_length > sliced_cell.size()) {
                    data_from_freeblock.emplace_back(
                            std::pair<std::string, std::string>(types[i], "can't parse data"));
                    continue;
                }
                for (int j{0}; j < data_length; j++) {
                    big_endian[j] = (sliced_cell[unreaded_data_offset + j]);
                }
                int little_endian = to_little_endian(big_endian, data_length);
                data_from_freeblock.emplace_back(
                        std::pair<std::string, std::string>(types[i], std::to_string(little_endian)));
            }

            if (value == 7) {
                std::string big_endian;
                big_endian.resize(static_cast<size_t>(data_length));
                if (unreaded_data_offset + data_length > sliced_cell.size()) {
                    data_from_freeblock.emplace_back(
                            std::pair<std::string, std::string>(types[i], "can't parse data"));
                    continue;
                }
                for (int j{0}; j < data_length; j++) {
                    big_endian[j] = (sliced_cell[unreaded_data_offset + j]);
                }
                data_from_freeblock.emplace_back((std::pair<std::string, std::string>(types[i], big_endian)));
            }

            if (value > 12) {
//            std::cout << "TEXT/BLOB is like this: " << std::endl;
                std::string data;
                if (unreaded_data_offset + data_length > sliced_cell.size()) {
                    data_from_freeblock.emplace_back(
                            std::pair<std::string, std::string>(types[i], "can't parse data"));
                    continue;
                }
                for (int j{0}; j < data_length; j++) {
                    data += sliced_cell[unreaded_data_offset + j];
                }
                data_from_freeblock.emplace_back(std::pair<std::string, std::string>(types[i], data));
            }


            unreaded_data_offset += data_length;

        }
    }
    return data_from_freeblock;
}
