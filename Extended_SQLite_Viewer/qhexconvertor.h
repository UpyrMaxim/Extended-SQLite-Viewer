#ifndef QHEXCONVERTOR_H
#define QHEXCONVERTOR_H

#include <QObject>
#include <QString>
#include <fstream>

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

    Q_INVOKABLE QString getHexData(const QString &FilePath);

signals:

public slots:
};

#endif // QHEXCONVERTOR_H
