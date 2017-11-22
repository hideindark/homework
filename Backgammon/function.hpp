#ifndef FUNTION
#define FUNTION
 
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include"class.hpp"
void mode(int mode);//PVP和PVE模式，对应分别为1和2
int checkboard(Checkerboard chess[15][15],PLAYER play);//检查是否获胜
int getLine(Checkerboard chess[15][15],Point p, int i, int j);//获取棋盘上一点
int ScanBest(Checkerboard chess[15][15],PLAYER *play);//寻找可以加入计算的点进行估值
int Score(Checkerboard chess[15][15],Point p,int player);//计算出相应分数

#endif