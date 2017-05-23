#include "calendarstring.h"
#include<QDate>
CalendarString::CalendarString()
{
    year=QDate::currentDate().year();
    month=QDate::currentDate().month();
}
CalendarString::CalendarString(int y, int m)
{
    year=y;
    month=m;
}
void CalendarString::setYM(int y, int m)
{
    year=y;
    month=m;
}
int CalendarString::getYear()
{
    return year;
}
int CalendarString::getMonth()
{
    return month;
}
QStringList CalendarString::getCalendarString()
{
    QStringList days;
    for(int i=0;i<42;i++)
        days.append("0");
    QDate indexdate(year,month,1);
    int week=indexdate.dayOfWeek();
    int day=0;
    //判断大月份
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
       day=31;
    }
    //判断小月
    else if(month==4||month==6||month==9||month==11)
    {
       day=30;
    }
    //判断平年与闰年
    else if(month==2)
    {
        if(((year%4==0)&&(year%100!=0))||(year%400==0))
        {
           day=29;
        }

        else
        {
           day=28;
        }
    }
    for(int i=week,n=1;i<week+day;i++)
    {
      days[i]=QString::number(n);
      n++;
    }
    return days;
}
