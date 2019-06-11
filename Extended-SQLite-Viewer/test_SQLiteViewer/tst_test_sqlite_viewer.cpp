#include <QtTest>

// add necessary includes here
#include "../Extended_SQLite_Viewer/qhexconvertor.h"
#include "../Extended_SQLite_Viewer/rawdatabaseparserwrapper.h"
#include "../Extended_SQLite_Viewer/rawdatatable.h"
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
private:
    std::vector<RawDataBaseParserWrapper*> RDBParser;
};

test_sqlite_viewer::test_sqlite_viewer()
{
    RDBParser.emplace_back(new RawDataBaseParserWrapper());
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

}

QTEST_APPLESS_MAIN(test_sqlite_viewer)

#include "tst_test_sqlite_viewer.moc"
