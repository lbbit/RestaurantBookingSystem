#include "calendarwidget.h"
#include<QDate>
#include<QStringList>
#include"dbconnect.h"
CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent)
{
    nowyear=QDate::currentDate().year();
    year=nowyear;
    nowmonth=QDate::currentDate().month();
    month=nowmonth;
    CStr=new CalendarString(year,month);
    init_layout();
    init_connect();
    flushbuttons(nowyear,nowmonth);
}
CalendarWidget::~CalendarWidget()
{
    delete hlayout;
    delete vlayout;
    delete glayout;
    delete button_lastmonth;
    delete button_nextmonth;
    delete button_currentmonth;
    delete label_currentmonth;
    for(int i=0;i<7;i++)
        delete labels_weekday[i];
    for(int i=0;i<42;i++)
        delete mcbuttons_day[i];
}
void CalendarWidget::init_layout()
{
    hlayout=new QHBoxLayout();
    vlayout=new QVBoxLayout();
    glayout=new QGridLayout();
    button_lastmonth=new QPushButton("上个月");
    button_lastmonth->setDisabled(true);    //不可查询当前月份以前的订单
    button_nextmonth=new QPushButton("下个月");
    button_currentmonth=new QPushButton("回到当月");
    label_currentmonth=new QLabel();
    QString str_weekdays[7]={"日","一","二","三","四","五","六"};
    for(int i=0;i<7;i++)
    {
        labels_weekday[i]=new QLabel();
        labels_weekday[i]->setText(str_weekdays[i]);
        labels_weekday[i]->setAlignment(Qt::AlignCenter);   //设置文字居中对齐
    }
    for(int i=0;i<42;i++)
    {
        mcbuttons_day[i]=new MyCalendarButton();
    }
    hlayout->addWidget(button_lastmonth);
    hlayout->addStretch();
    hlayout->addWidget(label_currentmonth);
    hlayout->addStretch();
    hlayout->addWidget(button_nextmonth);
    hlayout->addWidget(button_currentmonth);
    for(int i=0;i<7;i++)
    {
        glayout->addWidget(labels_weekday[i],0,i);
    }
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<7;j++)
        {
            glayout->addWidget(mcbuttons_day[i*7+j],i+1,j);
        }
    }
    //设置按钮之间间距
    glayout->setSpacing(4);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(glayout);
    vlayout->addStretch();
    this->setLayout(vlayout);
}
void CalendarWidget::init_connect()
{
    connect(button_lastmonth,&QPushButton::clicked,this,&CalendarWidget::click_lastmonth);
    connect(button_nextmonth,&QPushButton::clicked,this,&CalendarWidget::click_nextmonth);
    connect(button_currentmonth,&QPushButton::clicked,this,&CalendarWidget::click_currentmonth);
    for(int i=0;i<42;i++)
    {
        connect(mcbuttons_day[i],&MyCalendarButton::sendDate,this,&CalendarWidget::sendDate);
    }
}
void CalendarWidget::flushbuttons(int y, int m)
{
    label_currentmonth->setText(QString::number(y)+"年"+QString::number(m)+"月");
    QSqlDatabase db=DBConnect::initDB();
    if(db.open())
    {
        qDebug()<<"Database Opened";
        QSqlQuery sql_query;
        //查询当天未被占用的容量大于人数的桌子语句
        QString selectsql="SELECT DAY(date),count(*) "
                "FROM Rorder "
                "WHERE YEAR(date)=? AND MONTH(date)=? "
                "GROUP by date "
                "ORDER BY date";
        //查询所有记录
        sql_query.prepare(selectsql);
        sql_query.bindValue(0,y);
        sql_query.bindValue(1,m);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            QMap<int,int> countmap;
            while(sql_query.next())
            {
                countmap.insert(sql_query.value(0).toInt(),sql_query.value(1).toInt());
            }
            CStr->setYM(y,m);
            QStringList indexstrlist=CStr->getCalendarString();
            for(int i=0;i<42;i++)
            {
                if(indexstrlist[i]=="0")
                {
                    mcbuttons_day[i]->setVisible(false);
                }
                else
                {
                    int indexday=indexstrlist[i].toInt();
                    mcbuttons_day[i]->setVisible(true);
                    mcbuttons_day[i]->setYear(y);
                    mcbuttons_day[i]->setMonth(m);
                    mcbuttons_day[i]->setDay(indexday);
                    if(countmap.contains(indexday))
                    {
                        mcbuttons_day[i]->setOrdercount(countmap[indexday]);
                    }
                    else
                    {
                        mcbuttons_day[i]->setOrdercount(0);
                    }
                }
            }
        }
        db.close();
    }


}
void CalendarWidget::click_lastmonth()
{
    if(month==1)
    {
        month=12;
        year=year-1;
    }
    else
    {
        month=month-1;
    }
    if(month==nowmonth&&year==nowyear)
    {
        button_lastmonth->setDisabled(true);
    }
    flushbuttons(year,month);
}
void CalendarWidget::click_nextmonth()
{
    if(month==12)
    {
        month=1;
        year=year+1;
    }
    else
    {
        month=month+1;
    }
    button_lastmonth->setDisabled(false);
    flushbuttons(year,month);
}
void CalendarWidget::click_currentmonth()
{
    year=nowyear;
    month=nowmonth;
    button_lastmonth->setDisabled(true);
    flushbuttons(year,month);
}
void CalendarWidget::flushnowbuttons()
{
    flushbuttons(year,month);
}
