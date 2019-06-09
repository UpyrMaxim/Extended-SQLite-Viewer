#include "qsqlitetablelist.h"
#include <iostream>

QSQLiteTableList::QSQLiteTableList(QObject *parent)
    : QAbstractListModel(parent)
{
}

QVariant QSQLiteTableList::headerData(int section, Qt::Orientation orientation, int role) const
{
    return "Tables";
}

int QSQLiteTableList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
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

    switch (role) {
           case Qt::DisplayRole:
             if(DBaseSingleton::getInstance().tables().size()){
               return DBaseSingleton::getInstance().tables().at(index.row());
             } else {
                 return "test";
             }
           default:
               break;
    }


    // FIXME: Implement me!
    return QVariant();
}

int QSQLiteTableList::setDataBase(QString dataBaseName)
{
    beginResetModel();
    std::cout << "setDataBase start List" << std::endl;
    DBaseSingleton::getInstance().setDatabaseName(dataBaseName);
    if (!DBaseSingleton::getInstance().open()) {
        qDebug() << DBaseSingleton::getInstance().lastError();
        dataBaseActive = false;
        return -1;
    }
    std::cout << "DB was added ListView" << std::endl;
    dataBaseActive = true;
    endResetModel();
    return 0;
}

//void* QSQLiteTableList::getDataConection()
//{
//    if(dataBaseActive)
//    {
//          qInfo() << "return: " << &DBaseSingleton::getInstance() ;
//        return &DBaseSingleton::getInstance();
//    }
//    qInfo() << "return nullPtr";
//    return nullptr;
//}
