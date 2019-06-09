#include "qhexconvertor.h"
#include <QDebug>
#include <QTextStream>

QHexConvertor::QHexConvertor(QObject *parent) : QObject(parent)
{
}

QString QHexConvertor::getHexData(const QString &FilePath, const QString &TableName)
{
    if(FilePath.size() && TableName.size())
    {
        QByteArray bitArray;
        QString resultStr;

        loadBynaryData(bitArray,FilePath.toLocal8Bit().data(),TableName.toLocal8Bit().data());
        if(!bitArray.size())
        {
            return QString("HEX DATA ABSENT");
        }
        convertToHexView(bitArray,resultStr);
        return resultStr.toUpper();

    }
    return QString("HEX DATA FIELD");
}

char QHexConvertor::byteToCHarView(char charItem)
{
    if ( (charItem < 0x20) || (charItem > 0x7e))
    {
       charItem  = '.';
    }
    return charItem;
}

void QHexConvertor::loadBynaryData(QByteArray &bitArray, const std::string& FilePath, const std::string& TableName)
{
   resetRawDataBaseObject(FilePath);
   auto tableData = m_rawData->get_raw_data(TableName);
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

void QHexConvertor::convertToHexView(const QByteArray &bitArray, QString& resultStr)
{
    int baseStep = 3;
    int byteInLine = 16;
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

void QHexConvertor::resetRawDataBaseObject(const std::string& dbPath)
{
    if(m_rawData != nullptr)
    {
         delete m_rawData;
    }
    m_rawData = new Database();
    m_rawData->reset_path(dbPath);
    m_rawData->parse_database();
}

