#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QGridLayout>
#include <QSignalMapper>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class card : public QPushButton
{
public:
    explicit card(QString name1,int level1,float score1,float money1);
    QString name;
    int level;
    float score;
    float money;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
public Q_SLOTS:
    void add_window();//弹出添加新卡的对话框
    void change_window(int position);//点击会员卡对应的按钮时，弹出修改对话框提示修改,删除和充值
    void search_mode();//查询按钮用的槽函数，用于查找对应函数
    void send_add();//发送更新信号,用于多参数传递
    void addnew(QString name,QString money);//处理更新信号添加新的卡

    void charge(int positoin);//用于充值的按钮处理
    void charge_card(int position,QString data);//修改充值信息
    void send_charge();//发送充值信息
    void change(int positoin);//修改按钮所需的信号
    void send_change();//发送修改信息
    void change_card(int position, QString name, QString score);//修改卡数据
    void card_delete(int position);//删除按钮所需的符号
signals:
    void newcard(QString name,QString money);
    void newcharge(int positoin, QString data);
    void newchange(int position, QString name, QString score);
private:
    //主界面功能区
    QVector<card*> cards;
    QScrollArea* cardlist;
    QGridLayout* show_card;
    QPushButton* add_button;
    QPushButton* search_button;
    QLineEdit* search_edit;
    QSignalMapper* cardmap;
    QWidget* cardarea;
    //添加新卡区
    QLineEdit* name_edit;
    QLineEdit* money_edit;
    QLabel* name;
    QLabel* money;
    QPushButton* add_but;
    QSignalMapper* addmap;
    //修改，充值，删除用功能区
    QDialog* ch_window;
    QLabel* c_name;
    QLabel* c_score;
    QLabel* c_money;
    QPushButton* delete_button;
    QPushButton* change_button;
    QPushButton* charge_button;
    QPushButton* charge_in;
    QPushButton* change_in;
    QLineEdit* name_ch;
    QLineEdit* score_ch;
    QLineEdit* add_money;
    int pos;
};
#endif // MAINWINDOW_H
