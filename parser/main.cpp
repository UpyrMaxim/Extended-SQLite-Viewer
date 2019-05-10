#include <iostream>
#include <string>
#include <sstream>
#include <fstream>



static int max_data_length = 65536;

#pragma pack(push, 1)
struct sqlite_header{
    uint8_t header_string[16];
    uint16_t database_page_size;
    uint8_t file_format_write_v;
    uint8_t file_format_read_v;
    uint8_t unused_bytes_at_the_end_of_page;
    uint8_t max_epf;
    uint8_t min_epf;
    uint8_t leaf_payload_fraction;

    std::string get_header() const
    {
        std::string s{};
        for (size_t i(0); i < 15; i++){
            //std::cout << std::hex << header_string[i] << " ";
            s+=header_string[i];
        }
        //std::cout << std::endl;
        return s;
    }

    size_t get_database_page_size() const
    {
        //std::cout << std::hex << database_page_size << std::endl;
        return database_page_size;
    }
};

#pragma pack(pop)

//union header_uinion{
//    char* cBuffer;
//    sqlite_header* myBuffer;
//};


int main() {
    unsigned char buffer[max_data_length];
    std::ifstream file("test1.db", std::ios_base::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    file.read((char*)&buffer[0], sizeof(sqlite_header));
    auto header = reinterpret_cast<sqlite_header*>(buffer);
    std::cout << "The header string: \"SQLite format 3\\000\": " << header->get_header() << std::endl;
    std::cout << "The database page size in bytes: " << (int)header->get_database_page_size() << std::endl;
    std::cout << "Leaf payload fraction: "<< (int)header->leaf_payload_fraction << std::endl;


    return 0;
}