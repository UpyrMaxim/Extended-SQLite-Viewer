#ifndef QHEXCONVERTOR_H
#define QHEXCONVERTOR_H

#include <QObject>
#include <QString>
#include <fstream>
#include <memory>
#include <vector>
#include <Database.h>
#include "rawdatabaseparserwrapper.h"


class SimpleFileGuard {
public:
    SimpleFileGuard(std::ifstream &file) : fileUnderProtect(&file) { }
    std::ifstream &getFile() {
        return *fileUnderProtect;
    }

    ~SimpleFileGuard() {
        if (fileUnderProtect != nullptr)
        {
            fileUnderProtect->close();
        }
    }

private:
    std::ifstream *fileUnderProtect;
};

class QHexConvertor : public QObject
{
    Q_OBJECT
public:
    QHexConvertor(RawDataBaseParserWrapper *,QObject *parent = nullptr);

    Q_INVOKABLE QString getHexData(const QString = "");
    Q_INVOKABLE void resetRawDB(const QString = "");

signals:

public slots:
private:
    char byteToCHarView(char);
    void loadBynaryData(QByteArray&,const std::string&);
    void convertToHexView(const QByteArray&, QString&);


private:
    RawDataBaseParserWrapper * m_RawDataObj;
};

#endif // QHEXCONVERTOR_H
