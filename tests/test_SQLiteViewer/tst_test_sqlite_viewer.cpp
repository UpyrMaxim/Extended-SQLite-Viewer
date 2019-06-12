#include <QtTest>

// add necessary includes here

#include "../Extended_SQLite_Viewer/qhexconvertor.h"
#include "../Extended_SQLite_Viewer/rawdatabaseparserwrapper.h"
#include "../Extended_SQLite_Viewer/rawdatatable.h"
#include "../Extended_SQLite_Viewer/dbasesingleton.h"
#include "../Extended_SQLite_Viewer/qsqlitetablelist.h"
#include "../Extended_SQLite_Viewer/qsqlitemodel.h"


class test_qhex : public QHexConvertor
{
public:
    test_qhex(RawDataBaseParserWrapper* parser) : QHexConvertor(parser){}

    RawDataBaseParserWrapper * getRawDataObj(){

        return QHexConvertor::getRawDataObj();
    }

    void convertToHexView(const QByteArray &bitArray, QString& resultStr){
        QHexConvertor::convertToHexView(bitArray,resultStr);
    }

    void loadBynaryData(QByteArray &bitArray, const std::string& TableName)
    {
        QHexConvertor::loadBynaryData(bitArray, TableName);
    }
};

class test_rawData : public RAWDataTable
{
public:
    test_rawData(RawDataBaseParserWrapper* parser) : RAWDataTable(parser){}

    RawDataBaseParserWrapper * getRawDataObj()
    {
        return RAWDataTable::getRawDataObj();
    }

    std::string convertQTTypetoSQLType(const QString &TypeName)
    {
        return RAWDataTable::convertQTTypetoSQLType(TypeName);
    }

    QVariant headerData(int section, Qt::Orientation orien, int role) const
    {
       return RAWDataTable::headerData(section, orien, role);
    }

    void setTableData(std::string& table)
    {
        RAWDataTable::setTableData(table);
    }
};


class test_sqlite_viewer : public QObject
{
    Q_OBJECT

public:
    test_sqlite_viewer();
    ~test_sqlite_viewer();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_qhexconvertor_rawdatatable_interaction();
    void test_rawdatatable_headerData();
    void test_rawdatatable_headerData_bad_index();
    void test_rawdatatable_get_type();
    void test_rawdatatable_get_type_wrong_paramters();
    void test_rawdatatable_get_type_empty();
    void test_qhexconvertor_convert_to_hex();
    void test_qhexconvertor_convert_to_hex_empty();
    void test_qhexconvertor_load();
    void test_qhexconvertor_load_wrong_table_name();
    void test_qsqlitetablelist_set_DB();
    void test_qsqlitetablelist_get_row_count();
    void test_qsqlitemodel_get_header_data();
    void test_qsqlitemodel_get_header_data_wrong_index();
private:
    std::vector<RawDataBaseParserWrapper*> RDBParser;
};

test_sqlite_viewer::test_sqlite_viewer()
{
    RDBParser.emplace_back(new RawDataBaseParserWrapper());
    QString qStr = "../new_test_db_3.sqlite";
    DBaseSingleton::getInstance().setDatabaseName(qStr);
    DBaseSingleton::getInstance().open();
}


test_sqlite_viewer::~test_sqlite_viewer()
{

}

void test_sqlite_viewer::initTestCase()
{

}

void test_sqlite_viewer::cleanupTestCase()
{

}

void test_sqlite_viewer::test_qhexconvertor_rawdatatable_interaction()
{
    test_rawData tRW(RDBParser.front());
    test_qhex tQH(RDBParser.front());
    // test data base
    QString qStr = "../new_test_db_3.sqlite";
    tQH.resetRawDB(qStr);
    QCOMPARE(tQH.getRawDataObj(),tRW.getRawDataObj());
}
void test_sqlite_viewer::test_rawdatatable_headerData()
{
    test_rawData tRW(RDBParser.front());
    std::string tableName = "test";
    tRW.setTableData(tableName);
    auto header = tRW.headerData(1,Qt::Orientation(),1).toString();
    QCOMPARE("number",header);
}
void test_sqlite_viewer::test_rawdatatable_headerData_bad_index()
{
    test_rawData tRW(RDBParser.front());
    std::string tableName = "test";
    tRW.setTableData(tableName);
    auto header = tRW.headerData(9,Qt::Orientation(),1).toString();
    QCOMPARE("",header);
}
void test_sqlite_viewer::test_rawdatatable_get_type()
{
     test_rawData tRW(RDBParser.front());
     QCOMPARE("INT", tRW.convertQTTypetoSQLType("int").c_str());
}
void test_sqlite_viewer::test_rawdatatable_get_type_wrong_paramters()
{
    test_rawData tRW(RDBParser.front());
    QCOMPARE("BLOB", tRW.convertQTTypetoSQLType("asdasdasd").c_str());
}
void test_sqlite_viewer::test_rawdatatable_get_type_empty()
{
    test_rawData tRW(RDBParser.front());
    QCOMPARE("BLOB", tRW.convertQTTypetoSQLType("").c_str());
}
void test_sqlite_viewer::test_qhexconvertor_convert_to_hex()
{
   test_qhex tQH(RDBParser.front());
   QByteArray  bitArray;

   bitArray.resize(16);
   bitArray[0] = 0x3c;
   bitArray[1] = 0x48;
   bitArray[2] = 0x64;
   bitArray[3] = 0x18;
   bitArray[4] = 0x3a;
   bitArray[5] = 0x20;
   bitArray[6] = 0x64;
   bitArray[7] = 0x18;
   bitArray[8] = 0x5a;
   bitArray[9] = 0x18;
   bitArray[10] = 0x64;
   bitArray[11] = 0x10;
   bitArray[12] = 0x01;
   bitArray[13] = 0x70;
   bitArray[14] = 0x64;
   bitArray[15] = 0x18;

   QString resultStr;
   tQH.convertToHexView(bitArray,resultStr);
   QCOMPARE("3c 48 64 18 3a 20 64 18 5a 18 64 10 01 70 64 18  | <Hd.: d.Z.d..pd.\n", resultStr);
}
void test_sqlite_viewer::test_qhexconvertor_convert_to_hex_empty()
{
   test_qhex tQH(RDBParser.front());
   QByteArray bitArray;
   QString resultStr;
   tQH.convertToHexView(bitArray,resultStr);
   QCOMPARE("", resultStr);
}
void test_sqlite_viewer::test_qhexconvertor_load()
{
    test_qhex tQH(RDBParser.front());
    QByteArray bitArray;
    QString tableName = "test";
    tQH.loadBynaryData(bitArray,tableName.toUtf8().data());
    QString resultStr;
    tQH.convertToHexView(bitArray,resultStr);
    /* неуверен правильно ли так, но нужно проверить возвращаемое значение */
    QCOMPARE("0f 5d 00 15 01 13 04 34 74 68 0f 86 0f 0f 5d 00  | .].....4th....].\n08 06 14 04 00 0f 80 00 07 01 00 0b 0f 9e 00 0a  | ................\n01 13 02 32 74 68 0f bb 00 07 05 1c 04 0f ed 00  | ...2th..........\n11 01 13 03 33 74 68 0f ed 00 07 01 00 14 00 00  | ....3th.........\n00 09 01 11 10 31 37                             | .....17\n", resultStr);
}
void test_sqlite_viewer::test_qhexconvertor_load_wrong_table_name()
{
    test_qhex tQH(RDBParser.front());
    QByteArray bitArray;
    QString tableName = "sdsdsd";
    tQH.loadBynaryData(bitArray,tableName.toUtf8().data());
    QString resultStr;
    tQH.convertToHexView(bitArray,resultStr);
    QCOMPARE("", resultStr);
}
void test_sqlite_viewer::test_qsqlitetablelist_set_DB()
{
    QSQLiteTableList qTList;
    QString qStr = "../new_test_db_3.sqlite";
    QCOMPARE(0, qTList.setDataBase(qStr));
}
void test_sqlite_viewer::test_qsqlitetablelist_get_row_count()
{
    QSQLiteTableList qTList;
    QString qStr = "../new_test_db_3.sqlite";
    qTList.setDataBase(qStr);
    QCOMPARE(1, qTList.rowCount());
}
void test_sqlite_viewer::test_qsqlitemodel_get_header_data()
{
    QSQLiteModel qTList;
    QString qStr = "test";
    qTList.setDataBase(qStr);
    QCOMPARE("number", qTList.headerData(0,Qt::Horizontal,Qt::DisplayRole));
}
void test_sqlite_viewer::test_qsqlitemodel_get_header_data_wrong_index()
{
    QSQLiteModel qTList;
    QString qStr = "test";
    qTList.setDataBase(qStr);
    QCOMPARE(QVariant(), qTList.headerData(5,Qt::Horizontal,Qt::DisplayRole));
}

QTEST_APPLESS_MAIN(test_sqlite_viewer)

#include "tst_test_sqlite_viewer.moc"
