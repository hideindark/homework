#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <time.h>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QRectF>
#include <QChar>
#include <unistd.h>
//block define
//block type
bool block1[4][4]=
{
    {false,false,false,false},
    {false,true,true,false},
    {false,false,false,false},
    {false,false,false,false}
};
//left L type
bool block2[4][4]=
{
    {false,true,false,false},
    {false,true,false,false},
    {false,true,true,false},
    {false,false,false,false}
};
//right L type
bool block3[4][4]=
{
    {false,false,true,false},
    {false,false,true,false},
    {false,true,true,false},
    {false,false,false,false}
};
//W type
bool block4[4][4]
{
    {false,false,,false,false},
    {false,true,false,false},
    {true,true,true,false},
    {false,false,false,false}
};
//left S
bool block5[4][4]=
{
    {false,true,false,false},
    {false,true,true,false},
    {false,false,true,false},
    {false,false,false,false}
};
//right s
bool block6[4][4]=
{
    {false,false,true,false},
    {false,true,true,false},
    {false,true,false,false},
    {false,false,false,false}
};
//line
bool block7[4][4]=
{
    {false,true,false,false},
    {false,true,false,false},
    {false,true,false,false},
    {false,true,false,false}
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(AREA_COL*BLOCK_SIZE+MARGIN*4+BLOCK_SIZE*5,AREA_ROW*BLOCK_SIZE+MARGIN*2+BLOCK_SIZE+5);
    InitGame();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (player!=NULL)
        free(player);
    if (game_over_player!=NULL)
        free(game_over_player);
    if (playlist!=NULL)
        free(playlist);
}
void BlockCp(int dblock[4][4],int sblock[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dblock[i][j]=sblock[i][j];
}

void MainWindow::paintEvent(QPaintEvent *Event)
{
    QPainter pen(this);
    //paint game border
    pen.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    pen.drawRect(MARGIN,MARGIN,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE);

    //draw nextblock
    pen.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(NextBlock[i][j])
                pen.drawRect(MARGIN*3+AREA_COL*BLOCK_SIZE+j*BLOCK_SIZE,MARGIN+(i+1)*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
    //draw score, level, record score, time
    pen.setPen(Qt::black);
    pen.setFont(QFont("Arial",14));
    pen.drawText(QRect(MARGIN*3+AREA_COL*BLOCK_SIZE,MARGIN+5*BLOCK_SIZE,BLOCK_SIZE*5,BLOCK_SIZE*10),
                 Qt::AlignCenter,"Score:"+QString::number(score)+"\n level:"+QString::number(level)+"\n record:"+QString::number(HighScore)+"\n time:"+QString::number(time-clock()));

    //draw move block and stable block
    for(int i=0;i<AREA_ROW;i++)
        for(int j=0;j<AREA_COL;j++)
            if(GameArea[i][j]==1)
            {
                pen.setBrush(QBrush(Qt::Red,Qt::SolidPattern));
                pen.drawRect(MARGIN*2+J*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);

            }
            else(GameArea[i][j]==2)
            {
                pen.setBrush(QBrush(Qt::Blue,Qt::SolidPattern));
                pen.drawRect(MARGIN*2+J*BLOCK_SIZE,MARGIN+i*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);
            }
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    //block down
    if(event->timerId()==game_timer)
        BlockMove(DOWN);
    //game flash
    if(event->timerId()==paint_timer)
        update();
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key)
    {
        case Qt::Key_Up:
            BlockMove(UP);break;
        case Qt::Key_Down:
            BlockMove(DOWN);break;
        case Qt::Key_Left:
            BlockMove(LEFT);break;
        case Qt::Key_Right:
            BlockMove(RIGHT);break;
        case Qt::Key_Space:
            BlockMove(SPACE);break;
        default:
            break;

    }
}
void MainWindow::InitGame()
{

}
