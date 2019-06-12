#ifndef QHEXCONVERTOR_H
#define QHEXCONVERTOR_H

#include <QObject>
#include <QString>
#include <memory>
#include <vector>
#include <Database.h>
#include "rawdatabaseparserwrapper.h"


class QHexConvertor : public QObject
{
    Q_OBJECT
public:
    QHexConvertor(RawDataBaseParserWrapper *,QObject *parent = nullptr);

    Q_INVOKABLE QString getHexData(const QString = "");
    Q_INVOKABLE void resetRawDB(const QString = "");

signals:

public slots:
protected:
    char byteToCHarView(char);
    void loadBynaryData(QByteArray&,const std::string&);
    void convertToHexView(const QByteArray&, QString&);
    RawDataBaseParserWrapper *getRawDataObj();


protected:
    RawDataBaseParserWrapper * m_RawDataObj;
};

#endif // QHEXCONVERTOR_H
