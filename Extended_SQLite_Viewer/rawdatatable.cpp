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
        qDebug() <<  " objPointre "<<m_RawDataObj->getRawDataBaseObject();
        deletedContent = m_RawDataObj->getRawDataBaseObject()->get_parsed_data(tableName.c_str(), types);
        //deletedContent = {{"test1","test1_1","test_1_2"},{"test2","test2_1","test_2_2"},{"test3","test3_1","test_3_2"}};
        qDebug() << "after get setDataBase";
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
    qDebug() << TypeName;
    if(TypeName == "int")
        return  "INT";
    if(TypeName == "QString")
        return "TEXT";
    if(TypeName == "float")
        return "FLOAT";
    if(TypeName == "double")
        return "FLOAT";
    // просто набор байтиков :)
    return "BLOB";
}
