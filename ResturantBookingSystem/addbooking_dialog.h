#ifndef ADDBOOKING_DIALOG_H
#define ADDBOOKING_DIALOG_H
#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QComboBox>
#include<QPushButton>
#include<QDateEdit>
#include<QFormLayout>
class Addbooking_Dialog : public QDialog
{
    Q_OBJECT
public:
    Addbooking_Dialog(QWidget *parent = 0);
    ~Addbooking_Dialog();
public slots:
    void flushcombobox();
    void confirmbutton();
    void cancelbutton();
signals:
    void addAnorder();
private:
    //私有函数
    void initlayout();  //初始化布局
    void initconnect(); //连接信号和槽
    //所有控件
    QLabel *label_name;
    QLabel *label_count;
    QLabel *label_phone;
    QLabel *label_date;
    QLabel *label_table;
    QLabel *label_time;
    QLineEdit *lineedit_name;
    QLineEdit *lineedit_count;
    QLineEdit *lineedit_phone;
    QDateEdit *dateedit_date;
    QComboBox *combobox_table;
    QComboBox *combobox_time;
    QPushButton *button_confirm;
    QPushButton *button_cancel;
    QFormLayout *formlayout_form;
};

#endif // ADDBOOKING_DIALOG_H
