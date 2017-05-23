#include "dbconnect.h"

DBConnect::DBConnect()
{
}
QSqlDatabase DBConnect::initDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("RBS");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("zhang120");
    return db;
}
