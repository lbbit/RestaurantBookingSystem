#ifndef CALENDARSTRING_H
#define CALENDARSTRING_H
#include<QStringList>

class CalendarString
{
private:
    int year;
    int month;
public:
    CalendarString();
    CalendarString(int y,int m);
    void setYM(int y,int m);
    int getYear();
    int getMonth();
    QStringList getCalendarString();
};

#endif // CALENDARSTRING_H
