#ifndef QSQLITEMODEL_H
#define QSQLITEMODEL_H

#include <QAbstractTableModel>
#include <QtSql>
#include <QObject>

#include "dbasesingleton.h"

class QSQLiteModel : public QSqlTableModel
{
    Q_OBJECT

public:
    explicit QSQLiteModel(QObject *parent = nullptr);
    ~QSQLiteModel() override;
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void removeRow(int row);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    Q_INVOKABLE int setDataBase(const QString &tableName);

signals:
      void tableNameWasChanged();

private:
        bool setTableContent();
public slots:

private:
    QString TableName;
    bool dataBaseActive = false;
    int rowCountVal;
    int columnCountVal;
    QStringList TableData;
};

#endif // QSQLITEMODEL_H
