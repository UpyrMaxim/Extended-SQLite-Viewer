#include "rawdatatable.h"

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

    QByteArray byteArray = dbPath.toLocal8Bit();
    const char *c_path = byteArray.data();
    rawData = new Database(c_path);
}
