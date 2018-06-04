#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDialog>
#include <QTextStream>
#include <QLabel>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget* mainarea=new QWidget;
    cardlist=new QScrollArea;
    add_button=new QPushButton(tr("add card"),parent);
    search_button=new QPushButton(tr("search"),parent);
    search_edit=new QLineEdit(tr("input who you want to find"),parent);
    show_card=new QGridLayout;
    cardmap=new QSignalMapper(this);
    cardarea=new QWidget;
    QHBoxLayout* tools=new QHBoxLayout;
    QVBoxLayout* mainlayout=new QVBoxLayout;

    //功能区设置
    add_button->setMinimumSize(100,40);
    search_button->setMinimumSize(100,40);
    search_edit->setMinimumSize(400,40);
    tools->addWidget(add_button,2);
    tools->addWidget(search_button,2);
    tools->addWidget(search_edit,5);
    connect(add_button,SIGNAL(clicked(bool)),this,SLOT(add_window()));
    connect(search_button,SIGNAL(clicked(bool)),this,SLOT(search_mode()));

    //会员卡展示界面初始化,并进行管道设置
    connect(cardmap,SIGNAL(mapped(int)),this,SLOT(change_window(int)));
    QFile data(tr("F:\\CC++\\home_design\\cards.txt"));
    if(data.open(QFile::ReadOnly | QIODevice::ReadOnly))
    {
        QTextStream in(&data);
        int i=0;
        while(!in.atEnd())
        {
            QString name;
            int level,score,money;
            in>>name>>level>>score>>money;
            cards.append(new card(name,level,score,money));
            connect(cards[i],SIGNAL(clicked(bool)),cardmap,SLOT(map()));
            cardmap->setMapping(cards[i],i);
            show_card->addWidget(cards[i++],(i/3)*5,(i%3)*5,4,4);
        }
    }
    data.close();
    //设置界面
    setCentralWidget(mainarea);
    mainlayout->addLayout(tools,1);
    mainlayout->addWidget(cardlist,6);
    mainarea->setLayout(mainlayout);
    cardarea->setLayout(show_card);
    cardlist->setWidget(cardarea);
}
void MainWindow::search_mode()
{
    QString str=search_edit->text();
    if(str.isEmpty())
    {
        delete show_card;
        show_card=new QGridLayout;
        for(int i=0;i<cards.size();i++)
        {
            show_card->addWidget(cards[i],(i/3)*5,(i%3)*5,4,4);
        }
        cardarea->setLayout(show_card);
    }
    else
    {
        delete show_card;
        show_card=new QGridLayout;
        int t=0;
        for(int i=0;i<cards.size();i++)
        if(str==cards[i]->name)show_card->addWidget(cards[t],(t/3)*5,(t%3)*5,4,4);
        cardarea->setLayout(show_card);
    }
}
void MainWindow::add_window()
{
    addmap=new QSignalMapper(this);
    add_but=new QPushButton(this);
    QDialog dialog(this);
    QGridLayout* addwindow=new QGridLayout;
    dialog.setWindowTitle(tr("enter what's you want to add"));

    add_but->setText(tr("add new card"));
    name_edit=new QLineEdit;
    money_edit=new QLineEdit;
    name=new QLabel(tr("name:"));
    money=new QLabel(tr("money:"));
    money_edit->setValidator(new QDoubleValidator(-100000.00,100000.00,4));

    addwindow->addWidget(name,0,0,2,2);
    addwindow->addWidget(name_edit,0,2,2,4);
    addwindow->addWidget(money,2,0,2,2);
    addwindow->addWidget(money_edit,2,2,2,4);
    addwindow->addWidget(add_but,4,0,2,6);

    connect(add_but,SIGNAL(clicked(bool)),this,SLOT(send_add()));
    connect(this,SIGNAL(newcard(QString,QString)),this,SLOT(addnew(QString,QString)));

    dialog.setLayout(addwindow);
    dialog.exec();
}
void MainWindow::send_add()
{
    emit newcard(name_edit->text(),money_edit->text());
}
void MainWindow::addnew(QString name, QString money)
{
    QMessageBox addbox;
    if(name.isEmpty() || money.isEmpty())
    {
        addbox.about(this,tr("Fail"),tr("The name or money is empty, Please try again"));
    }
    else
    {
        addbox.about(this,tr("success"),tr("You can add more or quit"));
        float money1=money.toFloat();
        float score=money1/100;
        int level=score/100;
        if(level<=0)level=1;
        if(level>3)level=3;
        cards.append(new card(name,level,score,money1));
    }
    addbox.exec();
}
void MainWindow::change_window(int position)
{
    pos=position;
    ch_window=new QDialog(this);
    QGridLayout change_layout;
    delete_button=new QPushButton();
    charge_button=new QPushButton();
    change_button=new QPushButton();
    //label设置
    QLabel score;
    QLabel name_add;
    QLabel level;
    QLabel money_add;
    score.setText(tr("score:%1").arg(cards[position]->score));
    name_add.setText(tr("name:%1").arg(cards[position]->name));
    switch(cards[position]->level)
    {
        case 1:
            level.setText(tr("level:cooper"));break;
        case 2:
            level.setText(tr("level:silver"));break;
        case 3:
            level.setText(tr("level:gold"));break;
    }
    money_add.setText(tr("money:%1").arg(cards[position]->money));
    //按钮设置
    delete_button->setText(tr("delete"));
    charge_button->setText(tr("charge"));
    change_button->setText(tr("change"));
    //布局设置
    change_layout.addWidget(&name_add,0,0,2,6);
    change_layout.addWidget(&score,2,0,2,6);
    change_layout.addWidget(&level,4,0,2,6);
    change_layout.addWidget(&money_add,6,0,2,6);
    change_layout.addWidget(delete_button,8,0,2,2);
    change_layout.addWidget(charge_button,8,2,2,2);
    change_layout.addWidget(change_button,8,4,2,2);

    //信号槽设置
    QSignalMapper delete_map(this);
    QSignalMapper change_map(this);
    QSignalMapper charge_map(this);

    connect(&delete_map,SIGNAL(map(int)),this,SLOT(card_delete(int)));
    connect(&change_map,SIGNAL(map(int)),this,SLOT(change(int)));
    connect(&charge_map,SIGNAL(map(int)),this,SLOT(charge(int)));

    connect(delete_button,SIGNAL(clicked()),&delete_map,SLOT(map()));
    connect(charge_button,SIGNAL(clicked()),&charge_map,SLOT(map()));
    connect(change_button,SIGNAL(clicked()),&change_map,SLOT(map()));

    delete_map.setMapping(delete_button,position);
    change_map.setMapping(change_button,position);
    charge_map.setMapping(charge_button,position);

    ch_window->setLayout(&change_layout);
    ch_window->exec();
}
void MainWindow::charge(int position)
{
    c_money=new QLabel;
    QDialog charge_window;
    QGridLayout charge_layout;
    add_money=new QLineEdit;
    charge_in=new QPushButton;

    charge_in->setText(tr("charge"));

    c_money->setText(tr("How much you want to charge"));

    add_money->setValidator(new QDoubleValidator(-100000.00,100000.00,4));

    charge_layout.addWidget(c_money,0,0,2,2);
    charge_layout.addWidget(add_money,0,2,2,4);
    charge_layout.addWidget(charge_in,2,0,2,6);

    connect(charge_in,SIGNAL(clicked(bool)),this,SLOT(send_charge()));
    connect(this,SIGNAL(newcharge(int,QString)),this,SLOT(charge_card(int,QString)));

    charge_window.setLayout(&charge_layout);
    charge_window.exec();
}
void MainWindow::send_charge()
{
    emit newcharge(pos,add_money->text());
}
void MainWindow::charge_card(int position,QString data)
{
    float add=data.toFloat();
    cards[position]->money+=add;
    if(add>0.0)
    {
        cards[position]->score+=add/100.0;
        QMessageBox charge_box;
        charge_box.about(this,"result",tr("Need %1").arg(add*(0.9-0.1*cards[position]->level)));
        charge_box.exec();
    }
}
void MainWindow::change(int positoin)
{
    pos=positoin;
    c_name=new QLabel;
    c_score=new QLabel;
    name_ch=new QLineEdit;
    score_ch=new QLineEdit;
    change_in=new QPushButton;
    QDialog change_box;
    QGridLayout change_layout;

    c_name->setText(tr("Name:"));
    c_score->setText(tr("score:"));
    name_ch->setText(tr("%1").arg(cards[positoin]->name));
    score_ch->setText(tr("%1").arg(cards[positoin]->score));
    score_ch->setValidator(new QDoubleValidator(-100000.0,100000.0,4));
    change_in->setText(tr("change"));

    change_layout.addWidget(c_name,0,0,2,2);
    change_layout.addWidget(name_ch,0,2,2,4);
    change_layout.addWidget(c_score,2,0,2,2);
    change_layout.addWidget(score_ch,2,2,2,4);
    change_layout.addWidget(change_in,4,0,2,6);

    connect(change_in,SIGNAL(clicked(bool)),this,SLOT(send_change()));
    connect(this,SIGNAL(newchange(int,QString,QString)),this,SLOT(change_card(int,QString,QString)));

    change_box.setLayout(&change_layout);
    change_box.exec();
}
void MainWindow::send_change()
{
    emit newchange(pos,name_ch->text(),score_ch->text());
}
void MainWindow::change_card(int position, QString name, QString score)
{
    cards[position]->name=name;
    cards[position]->score=score.toFloat();
    cards[position]->level=cards[position]->score/100.0;
    if(cards[position]->level>3)cards[position]->level=3;
}
void MainWindow::card_delete(int position)
{
    cards.remove(position);
    QMessageBox result;
    result.about(this,tr("delte result"),tr("suceess"));
    result.exec();
}
MainWindow::~MainWindow()
{
    //将结果覆盖写入文件
    QFile file(tr("F:\\CC++\\home_design\\cards.txt"));
    file.open( QFile::WriteOnly | QIODevice::Truncate);
    QTextStream out(&file);
    for(int i=0;i<cards.size();i++)out<<' '<<cards[i]->name<<' '<<cards[i]->level<<' '<<cards[i]->score<<' '<<cards[i]->money;
    file.close();
    //删除所有指针
    for(int i=0;i<cards.size();i++)delete cards[i];
    cards.clear();
    delete cardlist;
    delete add_button;
    delete search_button;
    delete search_edit;
    delete cardmap;
    delete cardarea;

    delete name_edit;
    delete money_edit;
    delete name;
    delete money;
    delete add_but;
    delete addmap;

    delete ch_window;
    delete c_name;
    delete c_score;
    delete c_money;
    delete delete_button;
    delete change_button;
    delete charge_button;
    delete charge_in;
    delete change_in;
    delete name_ch;
    delete score_ch;
    delete add_money;
}
card::card(QString name1, int level1, float score1, float money1)
{
    name=name1;
    level=level1;
    score=score1;
    money=money1;
    setText(tr("name:%1\nlevel:%2\nscore:%3\nmoney:%4\n").arg(name).arg(level).arg(score).arg(money));
}
