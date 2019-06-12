#include "qsqlitetablelist.h"
#include <iostream>

QSQLiteTableList::QSQLiteTableList(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant QSQLiteTableList::headerData(int, Qt::Orientation, int) const
{
    return "Tables";
}

int QSQLiteTableList::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if(dataBaseActive)
    {
        return DBaseSingleton::getInstance().tables().count();
    }
    return 0;
}

QVariant QSQLiteTableList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
           case Qt::DisplayRole:
             if(DBaseSingleton::getInstance().tables().size() < index.row())
             {
               return DBaseSingleton::getInstance().tables().at(index.row());
             }
             break;
           default:
             break;
    }
    return QVariant();
}

int QSQLiteTableList::setDataBase(QString dataBaseName)
{
    beginResetModel();
    DBaseSingleton::getInstance().setDatabaseName(dataBaseName);
    if (!DBaseSingleton::getInstance().open())
    {
        qDebug() << DBaseSingleton::getInstance().lastError();
        dataBaseActive = false;
        return -1;
    }
    dataBaseActive = true;
    endResetModel();
    return 0;
}

