#ifndef ORDERSCHART_H
#define ORDERSCHART_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QLineEdit>
#include<QTableWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
class OrdersChart : public QWidget
{
    Q_OBJECT
public:
    explicit OrdersChart(QWidget *parent = 0);
    ~OrdersChart();
signals:
    void droporder();
private:
    int year;
    int month;
    int day;
    QLabel *label_thedate;  //显示所查询的日期
    QLabel *label_phone;    //电话：
    QLineEdit *lineedit_phone;  //电话号码输入框
    QPushButton *button_searchbyphone;  //通过电话搜索的按钮
    QTableWidget *table_orders;     //显示所查订单信息的表格
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    void init_layout(); //初始化布局
    void init_connect();    //初始化信号槽连接

public slots:
    void showDateOrder(QString);    //接受日期信号显示当天的订单
    void searchButtonClicked();     //显示搜索结果
    void modifyorder(int row,int column);  //修改选中某行的订单
    void deleteanorder();   //收到删除订单的信号，删除表格中对于的行
    void updateorder(int tid); //收到更新消息，更像表格内容
    void confirmin();   //记录预订到达
};

#endif // ORDERSCHART_H
