#ifndef RAWDATATABLE_H
#define RAWDATATABLE_H

#include <QAbstractTableModel>
#include <Database.h>
#include <vector>
#include "rawdatabaseparserwrapper.h"


class RAWDataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    RAWDataTable(RawDataBaseParserWrapper *RawDB, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void setDataBase(const QString tableName = "");

private:
    std::string tableName;
    RawDataBaseParserWrapper *m_RawDataObj;

private:
    std::vector<std::vector<std::string >> deletedContent;
    void getTypesList(std::vector<std::string>&);
    std::string convertQTTypetoSQLType(const QString &);
};

#endif // RAWDATATABLE_H
