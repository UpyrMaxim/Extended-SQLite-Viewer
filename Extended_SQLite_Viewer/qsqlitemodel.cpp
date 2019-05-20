#include "qsqlitemodel.h"
#include <iostream>
#include <QDebug>

QSQLiteModel::QSQLiteModel(QObject *parent)
    : QAbstractTableModel(parent), rowCountVal(0), columnCountVal(0), TableData(nullptr)
{
}

QSQLiteModel::~QSQLiteModel()
{
    if(TableData != nullptr){
       delete[] TableData;
    }
}

QVariant QSQLiteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    if(dataBaseActive){
//        QStringList headers;
//            QSqlQuery q("select * from " + TableName);
//            QSqlRecord rec = q.record();
//               for(int i = 0; i < rec.count() ; ++i ){
//                   headers.push_back(rec.fieldName(i));
//               }
//               return  headers;
//    }
    return "header ";
   // return QVariant();
}

bool QSQLiteModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int QSQLiteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return rowCountVal ? rowCountVal : 0;


}

int QSQLiteModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

   return columnCountVal ? columnCountVal : 0;
}

QVariant QSQLiteModel::data(const QModelIndex &index, int role) const // в теорії получаєш дані за індексом
{
   if (!index.isValid())
        return QVariant();


   if(dataBaseActive){
        switch (role) {
              case Qt::DisplayRole:
                if(TableData != nullptr){
                  return TableData[index.row()].at(index.column());
                } else {
                    return "test";
                }
              default:
                  break;
       }
    }
   // FIXME: Implement me!
   return QVariant();
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

Qt::ItemFlags QSQLiteModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

bool QSQLiteModel::setTableContent()
{

    QSqlQuery q("select * from " + TableName);

    if(TableData != nullptr){
        delete[] TableData;
    }
    TableData = new QStringList[rowCountVal >= 0 ? rowCountVal : 1 ];

    for (int i = 0;i < q.record().count(); ++i) {
        TableData[0].push_back(q.record().fieldName(i));
    }
    int row = 1, col = 0;
    while (q.next()) {
        for (col = 0; col < columnCountVal; ++col) {
            TableData[row].push_back(q.record().value(col).toString());
        }
        ++row;
    }

    return false;
}

//QHash<int, QByteArray> QSQLiteModel::roleNames() const
//{
//    QHash<int, QByteArray> result;
//    result[] = "id";
//    result[TitleRole] = "title";
//    result[DurationRole] = "duration";
//    return result;
//}

int QSQLiteModel::setDataBase(const QString &tableName)
{
    beginResetModel();

    TableName = tableName;
    dataBaseActive = true;

    qDebug() << "choosed tableName: " << tableName;


    /* init request*/
    QSqlQuery q("select * from " + TableName); // all table content
    int rowCount = 1;
    while (q.next()) {
         ++rowCount;
    }

    rowCountVal = rowCount;
    columnCountVal = q.record().count();

    setTableContent();

    endResetModel();
    return 0;
}

//QSqlDatabase* QSQLiteModel::getDataConection()
//{
//    if(dataBaseActive)
//    {
//        return dbase;
//    }
//    return nullptr;
//}
