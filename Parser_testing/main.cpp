#include <iostream>
#include <vector>
#include "Database.h"
#include "FreeBlock_parser.h"
#include "gtest/gtest.h"

using namespace testing;

class DatabaseTEST : public Test{
public:
Database database;
};

TEST_F(DatabaseTEST, table_existance_test1){
    database = Database("testing2.db");
    std::map<std::string,std::vector<int>> expecting_map;
    database.parse_database();
    expecting_map = database.get_tables_pages();
    ASSERT_TRUE(expecting_map.find("table1") != expecting_map.end());
}

TEST_F(DatabaseTEST, table_exitance_test2){
    database = Database("testing2.db");
    std::map<std::string,std::vector<int>> expecting_map;
    database.parse_database();
    expecting_map = database.get_tables_pages();
    ASSERT_TRUE(expecting_map.find("table2") != expecting_map.end());
}

TEST_F(DatabaseTEST, getRawDataTest1){
    database = Database("testing2.db");
    database.parse_database();
    auto data = database.get_raw_data("table2");
    std::string data_text;
    for ( auto vector : data){
        for (auto it : vector){
            data_text += (char)it;
        }
    }

    ASSERT_TRUE(data_text.find("deleted") != std::string::npos);
}

TEST_F(DatabaseTEST, getParsedDataTest1){
    database = Database("testing2.db");
    database.parse_database();
    std::vector<std::string> types = {"INT","TEXT","BLOB"};
    auto data = database.get_parsed_data("table2",types);
    bool flag = false;
    for (auto freeblock : data){
        for (auto string : freeblock){
            if (string.find("deleted") != std::string::npos){
                flag = true;
            }
        }
    }
    ASSERT_TRUE(flag);
}




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}