#include <QApplication>
#include<QDebug>
#include"mainwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QDate today=QDate::currentDate();
    WalkIn_Dialog w(today,0);
    w.show();
    */
    /*
    Addbooking_Dialog ad(0);
    ad.show();
    */
    //qDebug()<<QDate::currentDate().dayOfWeek();
    /*
    CalendarWidget cw;
    cw.show();
    */
    /*
    OrdersChart oc;
    oc.show();
    */
    /*
    ModifyOrder_Dialog mod(9);
    mod.show();
    */

    Mainwidget mw;
    mw.show();
    return a.exec();
}
