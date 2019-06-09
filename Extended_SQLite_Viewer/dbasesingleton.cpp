// Singleton.cpp
#include "dbasesingleton.h"

DBaseSingleton * DBaseSingleton::p_instance = nullptr;
SingletonDestroyer DBaseSingleton::destroyer;

SingletonDestroyer::~SingletonDestroyer() {
    qDebug() << "singleTon deleted";
    delete p_instance;
}
void SingletonDestroyer::initialize( DBaseSingleton* p ) {
    if(p_instance == nullptr)
        p_instance = p;
}


DBaseSingleton& DBaseSingleton::getInstance() {
    if(!p_instance)
    {
        p_instance = new DBaseSingleton(QSqlDatabase::addDatabase("QSQLITE"));
        destroyer.initialize( p_instance);
    }
    return *p_instance;
}

