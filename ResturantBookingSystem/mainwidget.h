#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include"orderschart.h"
#include"calendarwidget.h"
#include"walkin_dialog.h"
#include"addbooking_dialog.h"
#include<QLCDNumber>
#include<QTimer>
class Mainwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Mainwidget(QWidget *parent = 0);
    ~Mainwidget();
public slots:
    void click_order();
    void click_arrival();
    void click_close();
    void timeout_flushtime();
private:
    QLabel *label_logo; //显示logo图片
    QLabel *label_today;    //显示今天的日期
    OrdersChart *orderchart;
    CalendarWidget *calendar;
    QLCDNumber *lcd_nowtime;    //显示当前时间的lcd
    QPushButton *button_makeorder;
    QPushButton *button_makearrival;
    QPushButton *button_close;
    QVBoxLayout *vlayout_buttons;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout_all;
    QTimer *time_flush; //用于刷新当前时间的计时器
    void init_layout();
    void init_connect();

};

#endif // MAINWIDGET_H
