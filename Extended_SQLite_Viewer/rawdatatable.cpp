#include "rawdatatable.h"
#include "dbasesingleton.h"
#include <QtSql>
#include <QDebug>


RAWDataTable::RAWDataTable(RawDataBaseParserWrapper *RawDB, QObject *parent) : QAbstractTableModel(parent), m_RawDataObj(RawDB)
{

}

QVariant RAWDataTable::headerData(int section, Qt::Orientation, int) const
{
    return DBaseSingleton::getInstance().record(tableName.c_str()).fieldName(section);
}

int RAWDataTable::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return static_cast<int>(deletedContent.size());
    // FIXME: Implement me!
}

int RAWDataTable::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return DBaseSingleton::getInstance().record(tableName.c_str()).count();
    // FIXME: Implement me!
}

QVariant RAWDataTable::data(const QModelIndex &index, int) const
{
    if(deletedContent.size() > static_cast<size_t>(index.row()) && index.isValid())
    {
        if(deletedContent.at(static_cast<size_t>(index.row())).size() > static_cast<size_t>(index.column()))
        {
            return deletedContent.at(static_cast<size_t>(index.row())).at(static_cast<size_t>(index.column())).c_str();
        }
    }

    return QVariant();
}

void RAWDataTable::setDataBase(const QString TableName)
{
     if(m_RawDataObj->getRawDataBaseObject() && TableName.size()){
        std::vector<std::string> types;
        tableName = TableName.toLocal8Bit().data();
        getTypesList(types);
        beginResetModel();
        deletedContent = m_RawDataObj->getRawDataBaseObject()->get_parsed_data(tableName.c_str(), types);
        endResetModel();
    }
}

void RAWDataTable::getTypesList(std::vector<std::string> & outPut)
{
    auto var = DBaseSingleton::getInstance().record(tableName.c_str());
    for(int i = 0; i < var.count(); ++i)
    {
        outPut.push_back(convertQTTypetoSQLType(QVariant(var.field(i).type()).typeName()));
    }
}

std::string RAWDataTable::convertQTTypetoSQLType(const QString &TypeName)
{
    if(TypeName == "int")
        return  "INT";
    if(TypeName == "QString")
        return "TEXT";
    if(TypeName == "float")
        return "FLOAT";
    if(TypeName == "double")
        return "FLOAT";

    // в остальных случаях воспринимать как последовательность битов
    return "BLOB";
}

RawDataBaseParserWrapper* RAWDataTable::getRawDataObj()
{
    return m_RawDataObj;
}

void RAWDataTable::setTableData(std::string &tName)
{
    tableName = tName;
}


