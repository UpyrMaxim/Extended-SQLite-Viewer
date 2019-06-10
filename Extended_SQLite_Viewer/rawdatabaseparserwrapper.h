#ifndef RAWDATABASEPARSERWRAPPER_H
#define RAWDATABASEPARSERWRAPPER_H

#include "Database.h"

class RawDataBaseParserWrapper
{
public:
    RawDataBaseParserWrapper();
    RawDataBaseParserWrapper(RawDataBaseParserWrapper &) = default;
    void resetRawDataBase(const std::string& dbPath);
    Database *getRawDataBaseObject();
    ~RawDataBaseParserWrapper();
private:
    Database *p_rawDatabase;

};

#endif // RAWDATABASEPARSERWRAPPER_H
