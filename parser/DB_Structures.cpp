//
// Created by denis on 24.05.19.
//

#include <sstream>
#include "Database.h"

size_t to_little_endian (uint8_t *big_endian, int size) {
    size_t lil_endian = 0;
    auto big_end = big_endian;
    int offset = 0;
    for (int i{size-1}; i >= 0; i--){
        lil_endian |= (big_end[i]<<offset);
        offset+=8;
    }
    return lil_endian;
}

#pragma pack(push, 1)
struct Database::SQLite_header{
    uint8_t header_string[16];
    //uint16_t database_page_size;
    uint8_t database_page_size[2];
    uint8_t file_format_write_v;
    uint8_t file_format_read_v;
    uint8_t reserves_bytes_after_header;
    uint8_t max_epf;
    uint8_t min_epf;
    uint8_t leaf_payload_fraction;
    uint8_t file_change_counter[4];
    uint8_t pages_amount[4];
    uint8_t page_number_first_freelist[4];
    uint8_t total_number_freelist_pages[4];
    uint32_t schema_cookie;
    uint32_t schema_format_number;
    uint32_t page_cache_size;
    uint32_t number_of_largest_btree_page;
    uint32_t text_encoding;
    uint32_t user_version;
    uint32_t incremental_vacuum_mode_flag;
    uint32_t app_id;
    uint8_t reserved_for_epansion[20];
    uint32_t version_valid;
    uint8_t SQL_v_number[4];

    std::string get_header() const
    {
        std::string s{};
        for (size_t i(0); i < 15; i++){
            s+=header_string[i];
        }
        return s;
    }
    size_t get_database_page_size()
    {
        return to_little_endian(database_page_size,2);
    }
    size_t get_file_change_counter()
    {
        return to_little_endian(file_change_counter,4);
    }
    size_t get_pages_amount()
    {
        return to_little_endian(pages_amount,4);
    }
    size_t get_first_freelist_number() {
        return to_little_endian(page_number_first_freelist, 4);
    };
    size_t get_total_number_of_freelist_pages() {
        return to_little_endian(total_number_freelist_pages,4);
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Database::Btree_header{
    uint8_t flag;
    uint8_t start_freeblock_on_page[2];
    uint8_t cells_number[2];
    uint8_t cell_position[2];
    uint8_t number_of_freeblocks;
    uint8_t right_most_pointer[4];

    void print_btree_header(){
        std::cout << "Flag: " << (int)flag << std::endl;
        std::cout << "Amount of cells on the page: " << get_cells_number() << std::endl;
        std::cout << "Start of first cell: " << get_cell_position() << std::endl;
        std::cout << "First freeblock position: "  << get_first_freeblock_position() << std::endl;
        std::cout << "Freeblocks less then 3 bytes number : " << (int)number_of_freeblocks << std::endl;
    }

    size_t get_cell_position() const
    {
        return (cell_position[1]<<0)|(cell_position[0]<<8);
    }

    size_t get_first_freeblock_position() const
    {
        return (start_freeblock_on_page[1]<<0)|(start_freeblock_on_page[0]<<8);
    }
    size_t get_cells_number() const
    {
        return (cells_number[1]<<0)|(cells_number[0]<<8);
    }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Database::FreeBlock_header {
    uint8_t next_freeblock_offset[2];
    uint8_t length_of_freeblock[2];

    size_t get_next_offset(){
        return to_little_endian(next_freeblock_offset,2);
    };
    size_t get_length(){
        return to_little_endian(length_of_freeblock,2);
    }
};
#pragma pack(pop)

