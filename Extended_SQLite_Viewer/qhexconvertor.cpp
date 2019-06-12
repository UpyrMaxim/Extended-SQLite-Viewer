#include "qhexconvertor.h"
#include <QDebug>
#include <QTextStream>

QHexConvertor::QHexConvertor(RawDataBaseParserWrapper * RawData, QObject *parent) : QObject(parent), m_RawDataObj(RawData)
{

}

QString QHexConvertor::getHexData(const QString TableName)
{
    if(TableName.size())
    {
        QByteArray bitArray;
        QString resultStr;

        loadBynaryData(bitArray,TableName.toLocal8Bit().data());
        if(!bitArray.size())
        {
            return QString("HEX DATA ABSENT");
        }
        convertToHexView(bitArray,resultStr);
        return resultStr.toUpper();

    }
    return QString("HEX DATA FIELD");
}

void QHexConvertor::resetRawDB(const QString path)
{
    std::string pathStr = path.toUtf8().data();
    m_RawDataObj->resetRawDataBase(pathStr);
}

char QHexConvertor::byteToCHarView(char charItem)
{
    if ( (charItem < 0x20) || (charItem > 0x7e))
    {
       charItem  = '.';
    }
    return charItem;
}

void QHexConvertor::loadBynaryData(QByteArray &bitArray, const std::string& TableName)
{
   if(m_RawDataObj->getRawDataBaseObject()){
       auto tableData = m_RawDataObj->getRawDataBaseObject()->get_raw_data(TableName);

       if(!tableData.size())
       {
            return;
       }
       for (auto i : tableData)
       {
           for (auto  elem : i)
           {
             bitArray.push_back(static_cast<char>(elem));
           }
       }
   }
}

void QHexConvertor::convertToHexView(const QByteArray &bitArray, QString& resultStr)
{
    const int baseStep = 3;
    const int byteInLine = 16;
    int stepModif = byteInLine * baseStep;
    int bytePos = 0;

    QString bytesLineStringView;
    resultStr = bitArray.toHex(' ');
    for (int i = baseStep; i <= resultStr.size() + 2; i+=baseStep, ++bytePos)
    {
        bytesLineStringView.append(byteToCHarView(bitArray.at(bytePos)));
        if(i >= resultStr.size() && i < stepModif )
        {
            resultStr.resize(stepModif, ' ');
            i = stepModif;
        }
        if( i ==  stepModif)
        {
            resultStr.insert(i, QString(" | ") + bytesLineStringView + QString("\n"));
            i+= bytesLineStringView.size() + QString(" | \n").size();
            stepModif = i + byteInLine * baseStep;
            bytesLineStringView.clear();
        }
    }
}

RawDataBaseParserWrapper *QHexConvertor::getRawDataObj()
{
    return m_RawDataObj;
}
