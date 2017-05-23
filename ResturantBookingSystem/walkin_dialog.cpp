#include "walkin_dialog.h"
#include<QDebug>
#include"dbconnect.h"
#include<QMessageBox>
WalkIn_Dialog::WalkIn_Dialog(QDate today,QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle("现场到达");
    todaydate=today;
    initlayout();   //初始化布局
    initconnect();  //连接信号和槽
}

void WalkIn_Dialog::initlayout()
{
    label_peoplenum=new QLabel("人数：");
    label_tablenum=new QLabel("桌号：");
    label_time=new QLabel("当前时段：");
    lineedit_peoplenum=new QLineEdit();
    combobox_tablenum=new QComboBox();
    combobox_time=new QComboBox();
    combobox_time->addItem("简餐");
    combobox_time->addItem("正餐");
    combobox_time->addItem("夜宵");
    button_confirm=new QPushButton("确定");
    button_cancel=new QPushButton("取消");
    formlayout_all=new QFormLayout();
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, lineedit_peoplenum );
    lineedit_peoplenum->setValidator(validator);
    formlayout_all->addRow(label_peoplenum,lineedit_peoplenum);
    formlayout_all->addRow(label_time,combobox_time);
    formlayout_all->addRow(label_tablenum,combobox_tablenum);
    formlayout_all->addRow(button_confirm,button_cancel);
    this->setLayout(formlayout_all);

}
void WalkIn_Dialog::initconnect()
{
    connect(button_confirm,&QPushButton::clicked,this,&WalkIn_Dialog::confirmbutton);
    connect(button_cancel,&QPushButton::clicked,this,&WalkIn_Dialog::cancelbutton);
    connect(lineedit_peoplenum,&QLineEdit::textChanged,this,&WalkIn_Dialog::flushcombobox);
    connect(combobox_time,&QComboBox::currentTextChanged,this,&WalkIn_Dialog::flushcombobox);
    //connect(combobox_tablenum,SIGNAL(currentIndexChanged(int)),this,SLOT(showIndex()));
}

void WalkIn_Dialog::flushcombobox()
{
    if(lineedit_peoplenum->text().isEmpty())
    {
        //没有可选的桌子
    }
    else
    {
        //将当天未被占用的容量大于人数的桌子加入下拉菜单
        QSqlDatabase db = DBConnect::initDB();
        if(db.open())
        {
            qDebug()<<"Database Opened";
            int peoplenum=lineedit_peoplenum->text().toInt();
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString selectsql="select tID,tSize from Rtable where tSize>=? and tID not in "
                              "(select tID from Rorder where date=? and time=?)";
            //查询所有记录
            sql_query.prepare(selectsql);
            sql_query.bindValue(0,peoplenum);
            sql_query.bindValue(1,todaydate.toString("yyyy-MM-dd"));
            sql_query.bindValue(2,combobox_time->currentText());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                //qDebug()<<"select success!";
                combobox_tablenum->clear();
                while(sql_query.next())
                {
                    int tableID = sql_query.value(0).toInt();
                    int tableSize = sql_query.value(1).toInt();
                    combobox_tablenum->addItem(QString::number(tableID)+"号("+QString::number(tableSize)+"人)");
                }
            }
            db.close();
        }
    }
}

void WalkIn_Dialog::showIndex()
{
    qDebug()<<QString::number(combobox_tablenum->currentIndex());
}

void WalkIn_Dialog::confirmbutton()
{
    //将就餐信息插入订单表
    if(lineedit_peoplenum->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("请输入人数！"));
    }
    else if(combobox_tablenum->currentIndex()==-1)
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("没有可用的桌子！"));
    }
    else
    {
        QSqlDatabase db = DBConnect::initDB();
        if(db.open())
        {
            qDebug()<<"Database Opened";
            int peoplenum=lineedit_peoplenum->text().toInt();
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString insertsql="insert into Rorder(tID,count,date,time,state) values(?,?,?,?,'正在用餐')";
            QString indexstr=combobox_tablenum->currentText();
            int tableID=(indexstr.mid(0,indexstr.indexOf("号",0))).toInt();
            //查询所有记录
            sql_query.prepare(insertsql);
            sql_query.bindValue(0,tableID);
            sql_query.bindValue(1,peoplenum);
            sql_query.bindValue(2,todaydate.toString("yyyy-MM-dd"));
            sql_query.bindValue(3,combobox_time->currentText());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"insert success!";
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("入座成功！"));
                emit addAnorder();
                db.close();
                this->close();
            }
        }
    }


}
void WalkIn_Dialog::cancelbutton()
{
    this->close();
}
WalkIn_Dialog::~WalkIn_Dialog()
{
    delete label_peoplenum;
    delete label_tablenum;
    delete lineedit_peoplenum;
    delete combobox_tablenum;
    delete button_cancel;
    delete button_confirm;
    delete formlayout_all;
}
