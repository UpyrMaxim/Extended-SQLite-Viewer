#include "rawdatabaseparserwrapper.h"
#include <QtDebug>
RawDataBaseParserWrapper::RawDataBaseParserWrapper()
{
    p_rawDatabase = new Database();
}

void RawDataBaseParserWrapper::resetRawDataBase(const std::string& dbPath)
{
     qDebug()<<"reset obj" << p_rawDatabase;
    if(p_rawDatabase != nullptr)
    {
         delete p_rawDatabase;
    }

    p_rawDatabase = new Database();
    p_rawDatabase->reset_path(dbPath);
     qDebug()<<"reset finished" << p_rawDatabase;
    p_rawDatabase->parse_database();
}

Database *RawDataBaseParserWrapper::getRawDataBaseObject()
{
    qDebug()<<"get obj" << p_rawDatabase;
    return p_rawDatabase;
}

RawDataBaseParserWrapper::~RawDataBaseParserWrapper()
{
    if(p_rawDatabase != nullptr)
        delete p_rawDatabase;
}
