#ifndef RAWDATATABLE_H
#define RAWDATATABLE_H

#include <QAbstractTableModel>
#include <Database.h>

class RAWDataTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RAWDataTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void setDataBase(const QString &dbPath, const QString &tableName);

private:
    Database * rawData = nullptr;
};

#endif // RAWDATATABLE_H
