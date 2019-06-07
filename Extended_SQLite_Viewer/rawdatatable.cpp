#include "rawdatatable.h"
#include "dbasesingleton.h"
#include <QtSql>

RAWDataTable::RAWDataTable(QObject *parent)
    : QAbstractTableModel(parent)
{
            m_rawData = new Database();
}

QVariant RAWDataTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return QVariant();
}

int RAWDataTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int RAWDataTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant RAWDataTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void RAWDataTable::setDataBase(const QString &dbPath, const QString &TableName)
{
    if(m_rawData == nullptr){
        m_rawData = new Database();;
    }
    qDebug() << "init path: "<< dbPath;

    qDebug() << "deleted content start: "<< TableName;
    m_rawData->reset_path(dbPath.toLocal8Bit().data());
    std::vector<std::string> types;

    getTypesList(types,TableName);
    for (auto pair : m_rawData->get_parsed_data(TableName.toLocal8Bit().data(), types)){
        for (auto item : pair){
            std::cout << item << " ";
        }
    }



}

void RAWDataTable::getTypesList(std::vector<std::string> & outPut, const QString &tableName)
{
    auto var = DBaseSingleton::getInstance().record(tableName);
    for(int i = 0; i < var.count(); ++i)
    {
        outPut.push_back(convertQTTypetoSQLType(QVariant(var.field(i).type()).typeName()));
    }
}

std::string  RAWDataTable::convertQTTypetoSQLType(const QString &TypeName)
{
    if(TypeName == "int")
        return  "INT";
    if(TypeName == "QString")
        return "TEXT";

    return "undefined";
}
