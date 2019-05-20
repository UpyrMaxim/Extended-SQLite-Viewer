#ifndef QSQLITETABLELIST_H
#define QSQLITETABLELIST_H

#include <QAbstractListModel>
#include <QtSql>
#include <QObject>

#include "dbasesingleton.h"

class QSQLiteTableList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit QSQLiteTableList(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE int setDataBase(QString dataBaseName = "");
    //Q_INVOKABLE void* getDataConection();

private:
     bool dataBaseActive = false;
};

#endif // QSQLITETABLELIST_H
