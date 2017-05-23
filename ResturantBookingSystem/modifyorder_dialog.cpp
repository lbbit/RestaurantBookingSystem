#include "modifyorder_dialog.h"
#include"dbconnect.h"
#include<QMessageBox>
ModifyOrder_Dialog::ModifyOrder_Dialog(int oID)
{
    this->setWindowTitle("修改订单");
    this->oID=oID;
    isinorder=false;
    init_layout();
    init_data();
    init_connect();
}
ModifyOrder_Dialog::~ModifyOrder_Dialog()
{
    delete label_textoid;
    delete label_readoid;
    delete label_texttid;
    delete label_readtid;
    delete label_textname;
    delete label_readname;
    delete label_textcount;
    delete label_readcount;
    delete label_textphone;
    delete label_readphone;
    delete label_textdate;
    delete label_readdate;
    delete label_texttime;
    delete label_readtime;
    delete label_textstate;
    delete label_readstate;
    delete label_texttotable;
    delete button_modify;
    delete button_delete;
    delete button_checkout;
    delete button_cancel;
    delete combobox_table;
    delete formlayout;
}
void ModifyOrder_Dialog::init_data()
{
    QSqlDatabase db = DBConnect::initDB();
    if(db.open())
    {
        qDebug()<<"Database Opened";
        QSqlQuery sql_query;
        //查询出需要修改的订单信息
        QString selectsql="select * from Rorder where oID=?";
        sql_query.prepare(selectsql);
        sql_query.bindValue(0,oID);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            //qDebug()<<"select success!";
            if(sql_query.next())
            {
                tid= sql_query.value(1).toInt();
                name = sql_query.value(2).toString();
                count=sql_query.value(3).toInt();
                phone=sql_query.value(4).toString();
                date=sql_query.value(5).toString();
                time=sql_query.value(6).toString();
                state=sql_query.value(7).toString();
                //预订中的订单不可以结账
                if(date!=QDate::currentDate().toString("yyyy-MM-dd"))
                {
                    button_checkout->setVisible(false);
                }
                if(state=="预订中")
                {
                    button_checkout->setText("确认到达");
                    isinorder=true;
                }
                label_readtid->setText(QString::number(tid)+"号");
                label_readname->setText(name);
                label_readcount->setText(QString::number(count)+"人");
                label_readphone->setText(phone);
                label_readdate->setText(date);
                label_readtime->setText(time);
                label_readstate->setText(state);
                //载入下拉框
                selectsql="select tID,tSize from Rtable where tSize>=? and tID not in "
                          "(select tID from Rorder where date=? and time=?)";
                //查询所有记录
                sql_query.prepare(selectsql);
                sql_query.bindValue(0,count);
                sql_query.bindValue(1,date);
                sql_query.bindValue(2,time);
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
            }
            else
            {
                button_delete->setVisible(false);
                button_checkout->setVisible(false);
                button_modify->setVisible(false);
            }
        }
        db.close();
    }
}
void ModifyOrder_Dialog::init_layout()
{
    label_textoid=new QLabel("订单号：");
    label_readoid=new QLabel(QString::number(oID));
    label_texttid=new QLabel("当前餐桌号：");
    label_readtid=new QLabel();
    label_textname=new QLabel("姓名：");
    label_readname=new QLabel();
    label_textcount=new QLabel("人数：");
    label_readcount=new QLabel();
    label_textphone=new QLabel("电话：");
    label_readphone=new QLabel();
    label_textdate=new QLabel("日期：");
    label_readdate=new QLabel();
    label_texttime=new QLabel("用餐时段：");
    label_readtime=new QLabel();
    label_textstate=new QLabel("订单状态：");
    label_readstate=new QLabel();
    label_texttotable=new QLabel("可调餐桌");
    button_modify=new QPushButton("调换餐桌");
    button_delete=new QPushButton("删除订单");
    button_checkout=new QPushButton("结账");
    button_cancel=new QPushButton("取消");
    combobox_table=new QComboBox();
    formlayout=new QFormLayout();
    formlayout->addRow(label_textoid,label_readoid);
    formlayout->addRow(label_textname,label_readname);
    formlayout->addRow(label_textcount,label_readcount);
    formlayout->addRow(label_textphone,label_readphone);
    formlayout->addRow(label_textdate,label_readdate);
    formlayout->addRow(label_texttime,label_readtime);
    formlayout->addRow(label_textstate,label_readstate);
    formlayout->addRow(label_texttid,label_readtid);
    formlayout->addRow(label_texttotable,combobox_table);
    formlayout->addRow(button_modify,button_delete);
    formlayout->addRow(button_checkout,button_cancel);
    this->setLayout(formlayout);
}
void ModifyOrder_Dialog::init_connect()
{
    connect(button_cancel,&QPushButton::clicked,this,&ModifyOrder_Dialog::click_button_cancel);
    connect(button_checkout,&QPushButton::clicked,this,&ModifyOrder_Dialog::click_button_checkout);
    connect(button_delete,&QPushButton::clicked,this,&ModifyOrder_Dialog::click_button_delete);
    connect(button_modify,&QPushButton::clicked,this,&ModifyOrder_Dialog::click_button_modify);
}

void ModifyOrder_Dialog::click_button_modify()
{
    if(combobox_table->currentIndex()==-1)
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
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString updatesql="update Rorder set tID=? where oID=?";
            QString indexstr=combobox_table->currentText();
            int tableID=(indexstr.mid(0,indexstr.indexOf("号",0))).toInt();
            //查询所有记录
            sql_query.prepare(updatesql);
            sql_query.bindValue(0,tableID);
            sql_query.bindValue(1,oID);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"insert success!";
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("调换餐桌成功！"));
                emit updateorder(tableID);
                db.close();
                this->close();
            }
        }
    }

}
void ModifyOrder_Dialog::click_button_delete()
{
    if(QMessageBox::question(this, "question", "是否确认删除该订单", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        QSqlDatabase db = DBConnect::initDB();
        if(db.open())
        {
            qDebug()<<"Database Opened";
            QSqlQuery sql_query;
            //查询当天未被占用的容量大于人数的桌子语句
            QString deletesql="delete from Rorder where oID=?";
            //查询所有记录
            sql_query.prepare(deletesql);
            sql_query.bindValue(0,oID);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"insert success!";
                QMessageBox::information(this,
                                         tr("提示"),
                                         tr("删除订单成功！"));
                emit droporder();
                db.close();
                this->close();
            }
        }
    }
}
void ModifyOrder_Dialog::click_button_checkout()
{
    if(isinorder)
    {
        if(QMessageBox::question(this, "question", "是否确认到达", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            QSqlDatabase db = DBConnect::initDB();
            if(db.open())
            {
                qDebug()<<"Database Opened";
                QSqlQuery sql_query;
                //查询当天未被占用的容量大于人数的桌子语句
                QString updatesql="update Rorder set state=? where oID=?";
                //查询所有记录
                sql_query.prepare(updatesql);
                sql_query.bindValue(0,"正在用餐");
                sql_query.bindValue(1,oID);
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    qDebug()<<"insert success!";
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("记录到达成功！"));
                    emit confirmIn();
                    db.close();
                    this->close();
                }
            }
        }
    }
    else
    {
        if(QMessageBox::question(this, "question", "是否确认结账", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            QSqlDatabase db = DBConnect::initDB();
            if(db.open())
            {
                qDebug()<<"Database Opened";
                QSqlQuery sql_query;
                //查询当天未被占用的容量大于人数的桌子语句
                QString insertsql="insert into Rdownorder values(?,?,?,?,?,?,?)";
                sql_query.prepare(insertsql);
                sql_query.bindValue(0,oID);
                sql_query.bindValue(1,tid);
                sql_query.bindValue(2,name);
                sql_query.bindValue(3,count);
                sql_query.bindValue(4,phone);
                sql_query.bindValue(5,date);
                sql_query.bindValue(6,time);
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                QString deletesql="delete from Rorder where oID=?";
                //查询所有记录
                sql_query.prepare(deletesql);
                sql_query.bindValue(0,oID);
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    qDebug()<<"insert success!";
                    QMessageBox::information(this,
                                             tr("提示"),
                                             tr("结账成功！"));
                    emit droporder();
                    db.close();
                    this->close();
                }
            }
        }
    }

}
void ModifyOrder_Dialog::click_button_cancel()
{
    this->close();
}
