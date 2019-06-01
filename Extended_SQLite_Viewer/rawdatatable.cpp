#include "rawdatatable.h"
#include "dbasesingleton.h"
#include <QtSql>

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

void RAWDataTable::setDataBase(const QString &dbPath, const QString &tableName)
{
    if(rawData != nullptr){
        delete rawData;
    }
    std::vector<const char*> types;
    qDebug() << "setRawDataBase";
    getTypesList(types,tableName);
}

void RAWDataTable::getTypesList(std::vector<const char *> & outPut, const QString &tableName)
{
    auto var = DBaseSingleton::getInstance().record(tableName);
    for(int i = 0; i < var.count(); ++i)
    {
        qDebug() << convertQTTypetoSQLType(QVariant(var.field(i).type()).typeName());
    }
}

const char *RAWDataTable::convertQTTypetoSQLType(const QString &TypeName)
{
    if(TypeName == "int")
        return  "Int";
    if(TypeName == "QString")
        return "Text";

    return "undefined";
}
