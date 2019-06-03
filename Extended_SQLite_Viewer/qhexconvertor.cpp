#include "qhexconvertor.h"
#include <QDebug>
#include <QTextStream>

QHexConvertor::QHexConvertor(QObject *parent) : QObject(parent)
{
        m_rawData = new Database();
}

//QString QHexConvertor::getHexData(const QString &FilePath)
//{
//    qDebug() << "Get Hex data start";
//    if(FilePath.size()){
//        QByteArray bitArray = FilePath.toLocal8Bit();
//        const char *c_str = bitArray.data();
//        std::ifstream file (c_str, std::ios::in| std::ios::binary| std::ios::ate);
//        if (file.is_open())
//        {
//            SimpleFileGuard FileGuard(file);
//            qDebug() << "File opened";
//            unsigned int size = static_cast<unsigned int>(FileGuard.getFile().tellg());
//            auto memblock = std::make_shared<char*>(new char [size+1]);
//            FileGuard.getFile().seekg(0, std::ios::beg);
//            FileGuard.getFile().read(*memblock.get(), size);

//            bitArray.setRawData(*memblock.get(),size);
//            QString basic_val = QString("%1").arg(0, 10, 16) + " | ";
//            QString resultStr = basic_val + bitArray.toHex(' ');

//            int offset = 0;
//            int step = 48 + basic_val.size();
//            for (int i = step; i <= resultStr.size(); i+=step + 1){
//                resultStr.insert(i, QString("\n%1").arg(++offset * 16, 10, 16) + " | ");
//            }

//            return resultStr.toUpper();
//        }
//    }
//    return QString("HEX DATA FIELD");
//}

QString QHexConvertor::getHexData(const QString &FilePath, const QString &TableName)
{


    qDebug() << "Get Hex data start "  << TableName;


    if(FilePath.size() && TableName.size()){

        if(m_rawData == nullptr)
             m_rawData = new Database(); // если у нас не сохдан екземпляр Database

//        m_rawData.fr

        QByteArray bitArray;

        qDebug() << "Path: " <<  FilePath.toLocal8Bit().data() << " table: " << TableName.toLocal8Bit().data();

//        m_rawData->print_db_header();
//        m_rawData->scan_freeblocks();
//        m_rawData->identify_tables();
         m_rawData->reset_path(FilePath.toLocal8Bit().data());
         m_rawData->parse_database();
        auto tableData = m_rawData->get_raw_data(TableName.toLocal8Bit().data());

        if(!tableData.size()){
             return QString("Empty raw data");
        }
//        for (auto str :  m_rawData->get_raw_data(TableName.toLocal8Bit().data())){
//            std::cout << "RAW data from freeblock:\n" << str << std::endl;
//        }
        qDebug() << "Debag raw data in hex format:" ;
        for (auto i : tableData) {
            for (auto  elem : i) {

              bitArray.push_back(static_cast<char>(elem));
            }
        }

        if(!bitArray.size()){
            qDebug() << "bitarrey size is " << bitArray.size();
            return QString("HEX DATA FIELD");
        }

        QString resultStr = bitArray.toHex(' ');
        qDebug() << "our string: " << resultStr;
        int baseStep = 3;
        int byteInLine = 16;
        int stepModif = byteInLine * baseStep;
        int bytePos = 0;

        QString butesLineStringView;
        for (int i = baseStep; i <= resultStr.size() + 2; i+=baseStep, ++bytePos)
        {
            butesLineStringView.append(byteToCHarView(bitArray.at(bytePos)));
            if(i >= resultStr.size() && i < stepModif ){
                resultStr.resize(stepModif, ' ');
                i = stepModif;
            }
            if( i ==  stepModif)
            {
                resultStr.insert(i, QString(" | ") + butesLineStringView + QString("\n"));
                i+= butesLineStringView.size() + QString(" | \n").size();
                stepModif = i + byteInLine * baseStep;
                qDebug() << butesLineStringView << " stepMod val: " << stepModif << " resSize: " << resultStr.size();
                butesLineStringView.clear();
            }
        }

        return resultStr.toUpper();

    }
    return QString("HEX DATA FIELD");
}

char QHexConvertor::byteToCHarView(char charItem)
{
    if ( (charItem < 0x20) || (charItem > 0x7e)){
       charItem  = '.';
    }
    return charItem;
}

