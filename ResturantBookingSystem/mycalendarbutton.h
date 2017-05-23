#ifndef MYCALENDARBUTTON_H
#define MYCALENDARBUTTON_H
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
class MyCalendarButton : public QPushButton
{
    Q_OBJECT
public:
    MyCalendarButton();
    ~MyCalendarButton();
    void setYear(int);
    void setMonth(int);
    void setDay(int);
    void setOrdercount(int);
    int getYear();
    int getMonth();
    int getDay();
    int getOrdercount();
private:
    QLabel *label_day;
    QLabel *label_ordercount;
    QVBoxLayout *vlayout;
    int year;
    int month;
    int day;
    int ordercount;
    void initLayout();
    void initconnect();

private slots:
    void myclick();
signals:
    void sendDate(QString);
};

#endif // MYCALENDARBUTTON_H
