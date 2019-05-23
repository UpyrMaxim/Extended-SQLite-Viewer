#include "qsqlitemodel.h"
#include <iostream>
#include <QDebug>

QSQLiteModel::QSQLiteModel(QObject *parent)
    : QSqlTableModel (parent, DBaseSingleton::getInstance()), rowCountVal(0), columnCountVal(0), TableData(nullptr)
{
}

QSQLiteModel::~QSQLiteModel()
{

}

QVariant QSQLiteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
         return  TableData.at(section);
    }
    return QVariant();
}


int QSQLiteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !dataBaseActive)
        return 0;

    return  QSqlQueryModel::rowCount();
}

int QSQLiteModel::columnCount(const QModelIndex &parent) const
{

    if (parent.isValid() || !dataBaseActive)
        return 0;

   return QSqlQueryModel::record().count();
}

QVariant QSQLiteModel::data(const QModelIndex &index, int role) const // в теорії получаєш дані за індексом
{
   if (!index.isValid())
        return QVariant();

//   if(index.row() == 0)
//        return TableData.at(index.column());
//   else
        return QSqlTableModel::data(index,role);
}

bool QSQLiteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void QSQLiteModel::removeRow(int row)
{
    beginResetModel();
    qDebug() << "delete row " << row;
    QSqlTableModel::removeRow(row);
    endResetModel();

}

Qt::ItemFlags QSQLiteModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool QSQLiteModel::setTableContent()
{
    this->select();
    qDebug() << "selected : ";

    TableData.clear();
    for (int i = 0;i < this->record().count(); ++i) {
        TableData.push_back(this->record().fieldName(i));
         qDebug() << "selected : "<< this->record().fieldName(i);
    }

    return false;
}


int QSQLiteModel::setDataBase(const QString &tableName)
{
    beginResetModel();

    qDebug() << "choosed tableName: " << tableName;
    this->setTable(tableName);
    qDebug() << "setTable end: " << tableName;
    setTableContent();
    dataBaseActive = true;

    endResetModel();
    return 0;
}


