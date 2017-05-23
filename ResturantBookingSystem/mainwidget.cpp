#include "mainwidget.h"
#include<QMessageBox>
#include<QTime>
Mainwidget::Mainwidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("餐厅预订系统");
    time_flush=new QTimer();
    time_flush->setInterval(1000);  //每秒刷新一次
    time_flush->start();
    init_layout();;
    init_connect();
}
Mainwidget::~Mainwidget()
{

    time_flush->stop();
    delete time_flush;
    delete label_logo;
    delete label_today;
    delete lcd_nowtime;
    delete button_makearrival;
    delete button_makeorder;
    delete orderchart;
    delete calendar;
    delete vlayout_all;
    delete vlayout_buttons;
    delete hlayout;

}
void Mainwidget::init_layout()
{
    //this->setStyleSheet("text-align:center;");
    label_logo=new QLabel("logo");
    label_logo->setMinimumSize(150,100);
    QImage img(":/logo/RBS.png");
    label_logo->setPixmap(QPixmap::fromImage(img));
    label_today=new QLabel(QDate::currentDate().toString("yyyy年MM月dd日"));
    label_today->setAlignment(Qt::AlignCenter);   //设置文字居中对齐
    lcd_nowtime=new QLCDNumber();
    //设置晶体管控件QLCDNumber能显示的位数
    lcd_nowtime->setDigitCount(8);
    //设置显示的模式为十进制
    lcd_nowtime->setMode(QLCDNumber::Dec);
    //设置显示方式
    lcd_nowtime->setSegmentStyle(QLCDNumber::Flat);
    lcd_nowtime->display(QTime::currentTime().toString("hh:mm:ss"));    //显示当前时间
    button_makearrival=new QPushButton("现场就餐");
    button_makearrival->setMinimumSize(90,45);
    button_makeorder=new QPushButton("预订餐桌");
    button_makeorder->setMinimumSize(90,45);
    button_close=new QPushButton("关闭系统");
    button_close->setMinimumSize(90,45);
    orderchart=new OrdersChart();
    calendar=new CalendarWidget();
    calendar->setMinimumHeight(400);
    calendar->setMaximumHeight(400);
    //calendar->setStyleSheet("");
    vlayout_buttons=new QVBoxLayout();
    vlayout_all=new QVBoxLayout();
    hlayout=new QHBoxLayout();
    vlayout_buttons->addWidget(label_logo);
    vlayout_buttons->addWidget(label_today);
    vlayout_buttons->addWidget(lcd_nowtime);
    vlayout_buttons->addStretch();
    vlayout_buttons->addWidget(button_makeorder);
    vlayout_buttons->addWidget(button_makearrival);
    vlayout_buttons->addWidget(button_close);
    vlayout_buttons->addStretch();
    hlayout->addLayout(vlayout_buttons);
    hlayout->addStretch();
    hlayout->addWidget(calendar);
    vlayout_all->addLayout(hlayout);
    vlayout_all->addStretch();
    vlayout_all->addWidget(orderchart);
    vlayout_all->setSpacing(0);
    this->setLayout(vlayout_all);
}
void Mainwidget::init_connect()
{
    connect(time_flush,&QTimer::timeout,this,&Mainwidget::timeout_flushtime);
    connect(button_makearrival,&QPushButton::clicked,this,&Mainwidget::click_arrival);
    connect(button_makeorder,&QPushButton::clicked,this,&Mainwidget::click_order);
    connect(button_close,&QPushButton::clicked,this,&Mainwidget::click_close);
    connect(calendar,&CalendarWidget::sendDate,orderchart,&OrdersChart::showDateOrder);
    connect(orderchart,&OrdersChart::droporder,calendar,&CalendarWidget::flushnowbuttons);
}
void Mainwidget::timeout_flushtime()
{
    lcd_nowtime->display(QTime::currentTime().toString("hh:mm:ss"));    //显示当前时间
}
void Mainwidget::click_arrival()
{
    WalkIn_Dialog *wd=new WalkIn_Dialog(QDate::currentDate());
    wd->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口
    connect(wd,&WalkIn_Dialog::addAnorder,calendar,&CalendarWidget::flushnowbuttons);
    wd->show();
}
void Mainwidget::click_order()
{
    Addbooking_Dialog *ad=new Addbooking_Dialog();
    connect(ad,&Addbooking_Dialog::addAnorder,calendar,&CalendarWidget::flushnowbuttons);
    ad->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口
    ad->show();
}
void Mainwidget::click_close()
{
    if(QMessageBox::question(this, "提示", "是否确认退出系统？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        this->close();
    }
}
