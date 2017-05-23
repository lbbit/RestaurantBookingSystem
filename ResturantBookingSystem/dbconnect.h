#ifndef DBCONNECT_H
#define DBCONNECT_H
#include<QtSql>
#include <QSqlDatabase>

class DBConnect
{
public:
    DBConnect();
    static QSqlDatabase initDB();
};

#endif // DBCONNECT_H
