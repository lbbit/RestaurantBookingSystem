#include "mycalendarbutton.h"
#include<QDate>
MyCalendarButton::MyCalendarButton()
{
    initLayout();
    initconnect();
    setOrdercount(0);
    setMinimumSize(60,60);
}
//发出本身按钮的日期信号
void MyCalendarButton::myclick()
{
    if(day>0)
    {
        QDate indexdate;
        indexdate.setDate(year,month,day);
        emit sendDate(indexdate.toString("yyyy-MM-dd"));
    }

}
void MyCalendarButton::initLayout()
{
    label_day=new QLabel();
    label_ordercount=new QLabel();
    label_day->setAlignment(Qt::AlignCenter);   //设置文字居中对齐
    label_ordercount->setAlignment(Qt::AlignCenter);
    vlayout=new QVBoxLayout();
    vlayout->addWidget(label_day);
    vlayout->addWidget(label_ordercount);
    this->setLayout(vlayout);
}
void MyCalendarButton::initconnect()
{
    connect(this,&MyCalendarButton::clicked,this,&MyCalendarButton::myclick);
}
MyCalendarButton::~MyCalendarButton()
{
    delete label_day;
    delete label_ordercount;
    delete vlayout;
}
void MyCalendarButton::setYear(int y)
{
    year=y;
}
void MyCalendarButton::setMonth(int m)
{
    month=m;
}
void MyCalendarButton::setDay(int d)
{
    day=d;
    label_day->setText(QString::number(day));

    if(day>0)
    {
        QDate indexdate=QDate::currentDate();
        if(indexdate.year()==year&&indexdate.month()==month&&indexdate.day()==day)
        {
            this->setStyleSheet ("color: rgb(255,0,0);");
        }
        else
        {
            this->setStyleSheet ("QPushButton:hover{"
                                 "background-color:#FFE4B5"
                                 "}"
                             "QPushButton:pressed{"
                                 "background-color:#FFC125"
                             "}");
        }
    }


}
void MyCalendarButton::setOrdercount(int oc)
{
    ordercount=oc;
    if(ordercount>0)
    {
        label_ordercount->setText(QString::number(ordercount));
        label_ordercount->setStyleSheet("background-color: #EEB4B4;");
    }
    else
    {
        label_ordercount->setText("");
        label_ordercount->setStyleSheet("");
    }
}
int MyCalendarButton::getYear()
{
    return year;
}
int MyCalendarButton::getMonth()
{
    return month;
}
int MyCalendarButton::getDay()
{
    return day;
}
int MyCalendarButton::getOrdercount()
{
    return ordercount;
}
