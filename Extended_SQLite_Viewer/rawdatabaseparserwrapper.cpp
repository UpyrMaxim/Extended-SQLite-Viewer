#include "rawdatabaseparserwrapper.h"
#include <QtDebug>
RawDataBaseParserWrapper::RawDataBaseParserWrapper()
{
    p_rawDatabase = new Database();
}

void RawDataBaseParserWrapper::resetRawDataBase(const std::string& dbPath)
{
    if(p_rawDatabase != nullptr)
    {
         delete p_rawDatabase;
    }

    p_rawDatabase = new Database();
    p_rawDatabase->reset_path(dbPath);
    p_rawDatabase->parse_database();
}

Database *RawDataBaseParserWrapper::getRawDataBaseObject()
{
    return p_rawDatabase;
}

RawDataBaseParserWrapper::~RawDataBaseParserWrapper()
{
    if(p_rawDatabase != nullptr)
        delete p_rawDatabase;
}
