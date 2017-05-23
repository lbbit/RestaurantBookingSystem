#ifndef WALKIN_DIALOG_H
#define WALKIN_DIALOG_H

#include <QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QComboBox>
#include<QFormLayout>   //表单布局
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class WalkIn_Dialog : public QDialog
{
    Q_OBJECT
private:
    //所用控件
    QLabel *label_peoplenum;
    QLabel *label_tablenum;
    QLabel *label_time;
    QLineEdit *lineedit_peoplenum;
    QComboBox *combobox_tablenum;
    QComboBox *combobox_time;
    QPushButton *button_confirm;
    QPushButton *button_cancel;
    QFormLayout *formlayout_all;
    QDate todaydate;
    //私有函数
    void initlayout();  //初始化布局
    void initconnect(); //连接信号和槽
signals:
    void addAnorder();

public slots:
    void flushcombobox();   //刷新下拉框
    void confirmbutton();   //确认按钮
    void cancelbutton();    //取消按钮
    void showIndex();

public:
    WalkIn_Dialog(QDate today,QWidget *parent = 0);
    ~WalkIn_Dialog();
};

#endif // WALKIN_DIALOG_H
