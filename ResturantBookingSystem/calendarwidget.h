#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include"mycalendarbutton.h"
#include"calendarstring.h"
#include<QGridLayout>
#include<QHBoxLayout>
class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();
private:
    QPushButton *button_lastmonth;
    QPushButton *button_nextmonth;
    QPushButton *button_currentmonth;
    QLabel *label_currentmonth;
    QLabel *labels_weekday[7];
    MyCalendarButton *mcbuttons_day[42];
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QGridLayout *glayout;
    CalendarString *CStr;
    void init_layout();
    void init_connect();
    int year,nowyear,month,nowmonth;
signals:
    void sendDate(QString);
public slots:
    void flushbuttons(int y,int m);
    void flushnowbuttons(); //刷新当前显示的月份视图
    void click_lastmonth();
    void click_nextmonth();
    void click_currentmonth();
};

#endif // CALENDARWIDGET_H
