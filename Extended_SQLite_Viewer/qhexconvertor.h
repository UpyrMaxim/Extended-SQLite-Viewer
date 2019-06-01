#ifndef QHEXCONVERTOR_H
#define QHEXCONVERTOR_H

#include <QObject>
#include <QString>
#include <fstream>
#include <memory>
#include <vector>
#include <Database.h>

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
    explicit QHexConvertor(QObject *parent = nullptr);

    Q_INVOKABLE QString getHexData(const QString &,const QString &);

signals:

public slots:
private:
    char byteToCHarView(char);

private:
    Database * m_rawData;
};

#endif // QHEXCONVERTOR_H
