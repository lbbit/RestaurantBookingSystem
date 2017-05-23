#ifndef MODIFYORDER_DIALOG_H
#define MODIFYORDER_DIALOG_H


#include<QDialog>
#include<QLabel>
#include<QComboBox>
#include<QPushButton>
#include<QFormLayout>
class ModifyOrder_Dialog : public QDialog
{
    Q_OBJECT
public:
    ModifyOrder_Dialog(int oID);
    ~ModifyOrder_Dialog();
private:
    int oID;    //记录订单号
    int tid,count;
    QString name,phone,date,time,state;
    bool isinorder; //区分是预订还是正在就餐的订单
    QLabel *label_textoid;
    QLabel *label_readoid;
    QLabel *label_texttid;
    QLabel *label_readtid;
    QLabel *label_textname;
    QLabel *label_readname;
    QLabel *label_textcount;
    QLabel *label_readcount;
    QLabel *label_textphone;
    QLabel *label_readphone;
    QLabel *label_textdate;
    QLabel *label_readdate;
    QLabel *label_texttime;
    QLabel *label_readtime;
    QLabel *label_textstate;
    QLabel *label_readstate;
    QLabel *label_texttotable;
    QPushButton *button_modify;
    QPushButton *button_delete;
    QPushButton *button_checkout;
    QPushButton *button_cancel;
    QComboBox *combobox_table;
    QFormLayout *formlayout;

    void init_layout();
    void init_connect();
    void init_data();
signals:
    void droporder();
    void updateorder(int);
    void confirmIn();
public slots:
    void click_button_modify();
    void click_button_delete();
    void click_button_checkout();
    void click_button_cancel();
};
//修改订单 调换餐桌、删除订单、结账
#endif // MODIFYORDER_DIALOG_H
