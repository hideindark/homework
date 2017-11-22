#ifndef CLASS
#define CLASS

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
class Point
{
    public:
        int x;
        int y;
        void set(int x1,int y1);
};
class PLAYER :public Point, public Mouse
{
    public:
        void set(int code);
        void set(int x1,int y1);
        int code;
        int Undotime;        
}; 
class Checkerboard:public Sprite
{
    public:
        void TextureSet(int x,int y);//获取棋盘三种情况的组成图片，并调整位置
        void Reset();//重置当前位置
        void set(int t);//改变该位置状态
        int type;
        Checkerboard();
    private:
        Texture piece[3];
        
};
#endif