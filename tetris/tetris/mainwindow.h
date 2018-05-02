#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPixmap>


#define AREA_COL 15
#define AREA_ROW 10
#define MARGIN 5
#define BLOCK_SIZE 25


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};

namespace Ui {
class MainWindow;
}

class position//用于记录相对坐标位置
{
    int PosX;
    int PoxY;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitGame();//游戏初始化
    void StartGame();//游戏开始
    void GameOver();//游戏结束

    void BlockMove(Direction dir);//方块移动
    void BlockReset();//方块重设
    void BlockRotate(int Block[4][4]);//方块选装
    void NewBlock(int Block[4][4],int BlockId);//创造新的方块
    void BorderCheck(int Block[4][4]);//确认方块边界
    void IsCollide(int x,int y, Direction dir);//检测方块移动后是否碰撞
    void MusicOn();
    void MusicOff();

    virtual void paintEvent(QPaintEvent *Event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void on_actionNew_Game_triggered();
    void on_actionQuit_triggered();
    void on_actionMusic_On_triggered();
    void on_actionMusic_Off_triggered();

private:
    Ui::MainWindow *ui;
    position BlockPositon;//记录方块左上角的点
    int border[4];//记录方块边界，顺序为上下左右
    int GameArea[AREA_ROW][AREA_COL];//游戏区域，0为空，1为活动方块，2为稳定方块
    bool IsStable;//标记方块当前是否为稳定方块
    bool Block[4][4];//当前方块形状
    bool NextBlock[4][4];//下一个方块的形状
    int GameTimer;//方块下落计时器
    int PaintTimer;//画面刷新计时器
    int SpeedMs;//方块下落间隔
    int RefreshMs;//刷新时间间隔
    int level;//当前游戏难度等级1-5
    int HighScore;//过去达到的最高分
    int score;//当前分数
    int time;//记录起始时间用于时间显示

    QMediaPlayer* StartMusic;
    QMediaPlayer* GameoverMusic;
    QMediaPlaylist* playlist;
};

#endif // MAINWINDOW_H
