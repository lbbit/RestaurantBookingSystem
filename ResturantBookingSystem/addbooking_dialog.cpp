#include "addbooking_dialog.h"
#include <QSqlDatabase>
#include"dbconnect.h"
#include<QMessageBox>
Addbooking_Dialog::Addbooking_Dialog(QWidget *parent)
    :QDialog(parent)
{
    this->setWindowTitle("新增订单");
    initlayout();
    initconnect();
}

void Addbooking_Dialog::initlayout()
{
    label_name=new QLabel("姓名：");
    label_phone=new QLabel("电话：");
    label_count=new QLabel("人数：");
    label_table=new QLabel("桌号：");
    label_date=new QLabel("日期：");
    label_time=new QLabel("用餐时段：");
    lineedit_count=new QLineEdit();
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, lineedit_count );
    lineedit_count->setValidator(validator);
    lineedit_name=new QLineEdit();
    lineedit_phone=new QLineEdit();
    combobox_time=new QComboBox();
    combobox_time->addItem("简餐");
    combobox_time->addItem("正餐");
    combobox_time->addItem("夜宵");
    combobox_table=new QComboBox();
    dateedit_date=new QDateEdit();
    dateedit_date->setCalendarPopup(true);
    dateedit_date->setDate(QDate::currentDate());
    button_cancel=new QPushButton("取消");
    button_confirm=new QPushButton("确认");
    formlayout_form=new QFormLayout();
    formlayout_form->addRow(label_name,lineedit_name);
    formlayout_form->addRow(label_phone,lineedit_phone);
    formlayout_form->addRow(label_count,lineedit_count);
    formlayout_form->addRow(label_date,dateedit_date);
    formlayout_form->addRow(label_time,combobox_time);
    formlayout_form->addRow(label_table,combobox_table);
    formlayout_form->addRow(button_confirm,button_cancel);
    this->setLayout(formlayout_form);

}

void Addbooking_Dialog::initconnect()
{
    connect(button_confirm,&QPushButton::clicked,this,&Addbooking_Dialog::confirmbutton);
    connect(button_cancel,&QPushButton::clicked,this,&Addbooking_Dialog::cancelbutton);
    connect(lineedit_count,&QLineEdit::textChanged,this,&Addbooking_Dialog::flushcombobox);
    connect(dateedit_date,&QDateEdit::dateChanged,this,&Addbooking_Dialog::flushcombobox);
    connect(combobox_time,&QComboBox::currentTextChanged,this,&Addbooking_Dialog::flushcombobox);
}

void Addbooking_Dialog::flushcombobox()
{
    if(lineedit_count->text().isEmpty())
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
            int peoplenum=lineedit_count->text().toInt();
            QDate date=dateedit_date->date();
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString selectsql="select tID,tSize from Rtable where tSize>=? and tID not in "
                              "(select tID from Rorder where date=? and time=?)";
            //查询所有记录
            sql_query.prepare(selectsql);
            sql_query.bindValue(0,peoplenum);
            sql_query.bindValue(1,date.toString("yyyy-MM-dd"));
            sql_query.bindValue(2,combobox_time->currentText());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                //qDebug()<<"select success!";
                combobox_table->clear();
                while(sql_query.next())
                {
                    int tableID = sql_query.value(0).toInt();
                    int tableSize = sql_query.value(1).toInt();
                    combobox_table->addItem(QString::number(tableID)+"号("+QString::number(tableSize)+"人)");
                }
            }
            db.close();
        }
    }
}

void Addbooking_Dialog::confirmbutton()
{
    //将就餐信息插入订单表
    if(lineedit_count->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("请输入人数！"));
    }
    else if(combobox_table->currentIndex()==-1)
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("没有可用的桌子！"));
    }
    else if(lineedit_name->text().isEmpty()||lineedit_phone->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("警告"),
                                 tr("信息不完整！"));
    }
    else
    {
        QSqlDatabase db = DBConnect::initDB();
        if(db.open())
        {
            qDebug()<<"Database Opened";
            int peoplenum=lineedit_count->text().toInt();
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString insertsql="insert into Rorder(tID,name,phone,count,date,time,state) values(?,?,?,?,?,?,'预订中')";
            QString indexstr=combobox_table->currentText();
            int tableID=(indexstr.mid(0,indexstr.indexOf("号",0))).toInt();
            //查询所有记录
            sql_query.prepare(insertsql);
            sql_query.bindValue(0,tableID);
            sql_query.bindValue(1,lineedit_name->text());
            sql_query.bindValue(2,lineedit_phone->text());
            sql_query.bindValue(3,peoplenum);
            sql_query.bindValue(4,dateedit_date->date().toString("yyyy-MM-dd"));
            sql_query.bindValue(5,combobox_time->currentText());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"insert success!";
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("预订成功！"));
                emit addAnorder();
                db.close();
                this->close();
            }
        }
    }
}

void Addbooking_Dialog::cancelbutton()
{
    this->close();
}

Addbooking_Dialog::~Addbooking_Dialog()
{
    delete label_count;
    delete label_date;
    delete label_name;
    delete label_phone;
    delete label_table;
    delete label_time;
    delete lineedit_count;
    delete lineedit_name;
    delete lineedit_phone;
    delete combobox_table;
    delete combobox_time;
    delete dateedit_date;
    delete button_cancel;
    delete button_confirm;
    delete formlayout_form;
}
