#ifndef DBASE_SINGLETON_H
#define DBASE_SINGLETON_H

#include <QtSql>

// Singleton.h
class QSqlDatabase;
class DBaseSingleton;  // опережающее объявление

class SingletonDestroyer
{
  private:
    DBaseSingleton* p_instance;
  public:
    ~SingletonDestroyer();
    void initialize( DBaseSingleton* p );
};

class DBaseSingleton : public QSqlDatabase
{
  private:
    static DBaseSingleton* p_instance;
    static SingletonDestroyer destroyer;

  protected:
    DBaseSingleton() { }
    DBaseSingleton(QSqlDatabase par) : QSqlDatabase(par) { }
    DBaseSingleton( const DBaseSingleton& );
    DBaseSingleton& operator=( DBaseSingleton& );
   ~DBaseSingleton() { }
    friend class SingletonDestroyer;

  public:
    static DBaseSingleton& getInstance();
};
#endif // SINGLETON_H
