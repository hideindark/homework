#include"class.hpp"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
void Point::set(int x1,int y1)
{
    x=x1;
    y=y1;
}
void PLAYER::set(int code)
{
    this->code=code;
}
void PLAYER::set(int x1,int y1)
{
    x=x1;y=y1;
}
Checkerboard::Checkerboard()
{
    int type=0;
    for(int i=0;i<3;i++)
    {
        char ch[20];
        sprintf(ch,"picture\\chess%d.png",i);
        piece[i].loadFromFile(ch);
    }
    setTexture(piece[0]);
}
void Checkerboard::TextureSet(int x,int y)
{
    setPosition(50*x,50*y);
    type=0;
}
void Checkerboard::Reset()
{
    type=0;
    setTexture(piece[0]);
}
void Checkerboard::set(int t)
{
    type=t;
    setTexture(piece[t]);
}