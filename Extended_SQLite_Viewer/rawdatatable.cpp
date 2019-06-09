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

QVariant RAWDataTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if(deletedContent.size() > static_cast<size_t>(index.row()))
    {
        if(deletedContent.at(static_cast<size_t>(index.row())).size() > static_cast<size_t>(index.column()))
        {
            return deletedContent.at(static_cast<size_t>(index.row())).at(static_cast<size_t>(index.column())).c_str();
        }
    }

    return QVariant();
}

void RAWDataTable::setDataBase(const QString &dbPath, const QString &TableName)
{
    resetRawDataBaseObject(dbPath.toLocal8Bit().data());
    std::vector<std::string> types;
    tableName = TableName.toLocal8Bit().data();
    getTypesList(types);

    deletedContent = m_rawData->get_parsed_data(TableName.toLocal8Bit().data(), types);
      beginResetModel();
    for(const auto & val : deletedContent){
        for(const auto & str : val){
            qDebug() << str.c_str();
        }
    }
//    deletedContent.clear();
//    deletedContent = {{"TEst1","test1_1","test1_2"},{"TEst2","test2_1","test2_2"},{"TEst3","test3_1","test3_2"}};
    endResetModel();
}

void RAWDataTable::getTypesList(std::vector<std::string> & outPut)
{
    auto var = DBaseSingleton::getInstance().record(tableName.c_str());
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
        return "FLOAT";
    if(TypeName == "double")
        return "FLOAT";
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

//void RAWDataTable::setTableContent()
//{
//    this->select();
//    TableData.clear();
//    for (int i = 0;i < this->record().count(); ++i)
//    {
//        TableData.push_back(this->record().fieldName(i));
//    }

//    return false;
//}
