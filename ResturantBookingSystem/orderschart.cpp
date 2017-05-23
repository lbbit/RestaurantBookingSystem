#include "orderschart.h"
#include<QDate>
#include"dbconnect.h"
#include"modifyorder_dialog.h"
#include<QHeaderView>
OrdersChart::OrdersChart(QWidget *parent) : QWidget(parent)
{
    year=QDate::currentDate().year();
    month=QDate::currentDate().month();
    day=QDate::currentDate().day();
    init_layout();
    init_connect();
    showDateOrder(QDate::currentDate().toString("yyyy-MM-dd"));
}
OrdersChart::~OrdersChart()
{
    delete label_phone;
    delete label_thedate;
    delete lineedit_phone;
    delete button_searchbyphone;
    delete table_orders;
    delete hlayout;
    delete vlayout;
}
void OrdersChart::init_connect()
{
    connect(button_searchbyphone,&QPushButton::clicked,this,&OrdersChart::searchButtonClicked);
    connect(table_orders,&QTableWidget::cellDoubleClicked,this,&OrdersChart::modifyorder);
}

void OrdersChart::init_layout()
{
    label_thedate=new QLabel(QDate::currentDate().toString("yyyy年MM月dd日的订单信息"));
    label_phone=new QLabel("电话号码：");
    lineedit_phone=new QLineEdit();
    lineedit_phone->setMaximumWidth(120);
    button_searchbyphone=new QPushButton("搜索订单");
    table_orders=new QTableWidget();
    table_orders->setColumnCount(8);
    table_orders->setMinimumHeight(220);    //设置表格最小高度
    //table_orders->setMinimumWidth(300);
    QStringList table_header;   //表头
    table_header<<"订单号"<<"桌号"<<"姓名"<<"人数"<<"电话"<<"日期"<<"用餐时段"<<"当前状态";
    table_orders->setHorizontalHeaderLabels(table_header);
    table_orders->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    table_orders->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    table_orders->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置禁止编辑
    table_orders->horizontalHeader()->setStretchLastSection(true);  //设置表格最后一列延伸至表格最右边
    table_orders->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);   //列宽度自适应

    hlayout=new QHBoxLayout();
    vlayout=new QVBoxLayout();
    hlayout->addWidget(label_thedate);
    hlayout->addStretch();
    hlayout->addWidget(label_phone);
    hlayout->addWidget(lineedit_phone);
    hlayout->addWidget(button_searchbyphone);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(table_orders);
    this->setLayout(vlayout);
}

void OrdersChart::showDateOrder(QString datestr)
{
    QDate indexdate=QDate::fromString(datestr,"yyyy-MM-dd");
    year=indexdate.year();
    month=indexdate.month();
    day=indexdate.day();
    QSqlDatabase db=DBConnect::initDB();
    label_thedate->setText(QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day)+" 订单信息");
    if(db.open())
    {
        qDebug()<<"Database Opened";
        QSqlQuery sql_query;
        //查询当天的订单
        QString selectsql="select * from Rorder where date=? order by state desc";
        //查询所有记录
        sql_query.prepare(selectsql);
        sql_query.bindValue(0,datestr);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {

            table_orders->clearContents();  //清空表格内容
            int rowindex=0;
            table_orders->setRowCount(rowindex);
            //qDebug()<<"select success!";
            while(sql_query.next())
            {
                //将查询的内容写入表格
                table_orders->setRowCount(++rowindex);
                for(int col=0;col<8;col++)
                {
                    table_orders->setItem(rowindex-1,col,new QTableWidgetItem(sql_query.value(col).toString()));
                }

            }
        }
        db.close();
    }
    //设置表格列宽适应内容
    for(int i=0;i<8;i++)
    {
        table_orders->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

}

void OrdersChart::searchButtonClicked()
{
    label_thedate->setText("全部搜索结果");
    QSqlDatabase db=DBConnect::initDB();
    if(db.open())
    {
        qDebug()<<"Database Opened";
        QSqlQuery sql_query;
        QString selectsql;
        if(lineedit_phone->text().isEmpty())
        {
            selectsql="select * from Rorder order by state";
            //当没有输入电话号码时查询所有记录
            sql_query.prepare(selectsql);
        }
        else
        {
            QString numindex=lineedit_phone->text();
            selectsql="select * from Rorder where phone like ? order by state";
            //查询以编辑框中输入的电话开头的所有记录
            sql_query.prepare(selectsql);
            sql_query.bindValue(0,numindex+"%");
        }

        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {

            table_orders->clearContents();  //清空表格内容
            int rowindex=0;
            table_orders->setRowCount(rowindex);
            //qDebug()<<"select success!";
            while(sql_query.next())
            {
                //将查询的内容写入表格
                table_orders->setRowCount(++rowindex);
                for(int col=0;col<8;col++)
                {
                    table_orders->setItem(rowindex-1,col,new QTableWidgetItem(sql_query.value(col).toString()));
                }

            }
        }
        db.close();
    }
    //设置表格列宽适应内容
    for(int i=0;i<8;i++)
    {
        table_orders->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
}
void OrdersChart::modifyorder(int row,int column)
{
    ModifyOrder_Dialog *mod=new ModifyOrder_Dialog(table_orders->item(row,0)->text().toInt());
    connect(mod,&ModifyOrder_Dialog::droporder,this,&OrdersChart::deleteanorder);
    connect(mod,&ModifyOrder_Dialog::updateorder,this,&OrdersChart::updateorder);
    connect(mod,&ModifyOrder_Dialog::confirmIn,this,&OrdersChart::confirmin);
    connect(mod,&ModifyOrder_Dialog::droporder,this,&OrdersChart::droporder);
    mod->setWindowModality(Qt::ApplicationModal);//让Dialog窗口置顶，并禁用其它窗口
    mod->show();
}
void OrdersChart::deleteanorder()
{
    int indexrow=table_orders->currentRow();
    if(indexrow!=-1)
    {
        table_orders->removeRow(indexrow);
    }
}
void OrdersChart::updateorder(int tid)
{
    int indexrow=table_orders->currentRow();
    table_orders->setItem(indexrow,1,new QTableWidgetItem(QString::number(tid)));
}
void OrdersChart::confirmin()
{
    int indexrow=table_orders->currentRow();
    table_orders->setItem(indexrow,7,new QTableWidgetItem("正在用餐"));
}
