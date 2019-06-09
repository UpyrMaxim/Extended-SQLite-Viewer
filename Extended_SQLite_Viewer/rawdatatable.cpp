#include "rawdatatable.h"
#include "dbasesingleton.h"
#include <QtSql>
#include <QDebug>

RAWDataTable::RAWDataTable(QObject *parent)
    : QAbstractTableModel(parent)
{
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
    resetRawDataBaseObject(dbPath.toLocal8Bit().data());
    std::vector<std::string> types;

    getTypesList(types,TableName);


  //  auto deletedContent = m_rawData->get_parsed_data(TableName.toLocal8Bit().data(), types);

    std::vector<std::vector<std::string >> deletedContent = {{"TEst1","test1_1","test1_2"},{"TEst2","test2_1","test2_2"},{"TEst3","test3_1","test3_2"}};
    for (const auto &pair : deletedContent){
        for (const auto &item : pair)
        {
            qDebug() << QString(item.c_str()) << " - ";
        }
    }
    QAbstractTableModel::


    qDebug() << "deleted content end: "<< TableName;

}

void RAWDataTable::getTypesList(std::vector<std::string> & outPut, const QString &tableName)
{
    auto var = DBaseSingleton::getInstance().record(tableName);
    for(int i = 0; i < var.count(); ++i)
    {
        outPut.push_back(convertQTTypetoSQLType(QVariant(var.field(i).type()).typeName()));
        qDebug() << QString(outPut.rbegin()->c_str());
    }
}

std::string RAWDataTable::convertQTTypetoSQLType(const QString &TypeName)
{
    if(TypeName == "int")
        return  "INT";
    if(TypeName == "QString")
        return "TEXT";
    if(TypeName == "float")
        return "REAL";
    if(TypeName == "double")
        return "REAL";
    // просто набор байтиков :)
    return "BLOB"; // хз как называется
}

void RAWDataTable::resetRawDataBaseObject(const std::string& dbPath)
{
    if(m_rawData != nullptr)
    {
         delete m_rawData;
    }
    m_rawData = new Database();
    m_rawData->reset_path(dbPath);
    m_rawData->parse_database();
}
