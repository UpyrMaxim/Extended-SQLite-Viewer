#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include "mysqltablemodel.h"


MySQLTableModel::MySQLTableModel()
{
}

MySQLTableModel::~MySQLTableModel()
{
    delete SQLTableModel;
}

//bool MySQLTableModel::select()
//{
//    if(SQLTableModel != nullptr){
//        bool ret = SQLTableModel->select();

//        if (ret)
//            generateRoleNames();

//       return ret;
//    }

//    return false;
//}

int  MySQLTableModel::setDataBase(QString dataBaseName)
{
    qDebug() << "setDataBase: method start";
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(dataBaseName);
    if (!dbase.open()) {
        qDebug() << dbase.lastError();
        return -1;
    }

    if(SQLTableModel != nullptr){
        qDebug() << "setDataBase: delete old SQLTableModel";
        delete SQLTableModel;
    }

    SQLTableModel = new QSqlRelationalTableModel(this,dbase);

    qDebug() << "SQLTableModel was created";
    emit dataBaseChanged();
    return 0;
}

//QVariant MySQLTableModel::data(const QModelIndex &item, int role) const
//{
//     if(SQLTableModel != nullptr){
//        if (item.row() >= SQLTableModel->rowCount())
//            return QString();

//        if (role < Qt::UserRole)
//            return SQLTableModel->QSqlQueryModel::data(item, role);
//        else
//        {
//            int columnIdx = role - Qt::UserRole - 1;
//            QModelIndex modelIndex = SQLTableModel->index(item.row(), columnIdx);
//            return SQLTableModel->QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
//        }
//     }
//     return  NULL;
//}

QString MySQLTableModel::getTestData()
{

    if(SQLTableModel == nullptr){
         return "Choose DB please";
    }
    /* вивести 1 строку */
    /* в ідеалі цей метод має повернути список таблиц в бд, но поки що тест дані*/

    QSqlQuery a_query;

    if (!a_query.exec("SELECT * FROM test_sqlite_table")) {
        qDebug() << "cant select data ";
        qDebug() << a_query.lastError();
        return "Error"; // TODO: нужно создать ексепшен
    }

    QSqlRecord rec = a_query.record();
    int PK = 0,
           NumericField = 0;
    QString StringField = "";
    QString TestResult = "";

    while (a_query.next()) {
        PK = a_query.value(rec.indexOf("PK")).toInt();
        StringField = a_query.value(rec.indexOf("StringField")).toString();
        NumericField = a_query.value(rec.indexOf("NumericField")).toInt();

        TestResult = "StringField is: " +  StringField;
    }

    return TestResult;
}

QStringList MySQLTableModel::getTableList()
{
    QSqlDatabase dbase;
    return dbase.tables();
}

//int MySQLTableModel::generateRoleNames()
//{

//    if(SQLTableModel != nullptr){

//        role_names.clear();
//        for (int i = 0; i < SQLTableModel->record().count(); ++i)
//        {
//            role_names[Qt::UserRole + i + 1] = SQLTableModel->record().fieldName(i).toUtf8(); // Qt::UserRole любий тип
//        }

//        return 0;
//    }

//    return -1;
//}
