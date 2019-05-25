#include "qhexconvertor.h"
#include <QDebug>
#include <memory>
#include <iomanip>
#include <QTextStream>

QHexConvertor::QHexConvertor(QObject *parent) : QObject(parent)
{

}

QString QHexConvertor::getHexData(const QString &FilePath)
{
    qDebug() << "Get Hex data start";
    if(FilePath.size()){
        QByteArray bitArray = FilePath.toLocal8Bit();
        const char *c_str = bitArray.data();
        std::ifstream file (c_str, std::ios::in| std::ios::binary| std::ios::ate);
        if (file.is_open())
        {
            SimpleFileGuard FileGuard(file);
            qDebug() << "File opened";
            unsigned int size = static_cast<unsigned int>(FileGuard.getFile().tellg());
            auto memblock = std::make_shared<char*>(new char [size+1]);
            FileGuard.getFile().seekg(0, std::ios::beg);
            FileGuard.getFile().read(*memblock.get(), size);

            bitArray.setRawData(*memblock.get(),size);
            QString basic_val = QString("%1").arg(0, 10, 16) + " | ";
            QString resultStr = basic_val + bitArray.toHex(' ');

            int offset = 0;
            int step = 48 + basic_val.size();
            for (int i = step; i <= resultStr.size(); i+=step + 1){
                resultStr.insert(i, QString("\n%1").arg(++offset * 16, 10, 16) + " | ");
            }

            return resultStr.toUpper();
        }
    }
    return QString("HEX DATA FIELD");
}

