#include "class.hpp"
#include "function.hpp"
#include<cstdio>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
int main()
{
    Texture back;
    back.loadFromFile("picture\\back.png");
    Sprite background(back);//背景资源获取
    RenderWindow window(VideoMode(713,601), "Gobang!");
    window.setFramerateLimit(60);//窗口设定
    while (window.isOpen())
    {   
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.draw(background);
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            int x=Mouse::getPosition(window).x;
            int y=Mouse::getPosition(window).y;
            if(x>=238 && x<=424 && y<=288 && y>=237 )//PVP
            {
                window.close();
                mode(1);
            }
            else if(x>=236 && x<=423 && y<=404 && y>=347 )//pve
            {
                window.close();
                mode(2);
            }
        }
        window.clear();
        window.draw(background);
        window.display();
    }
    return 0;
} 