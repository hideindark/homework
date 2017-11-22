#include"function.hpp"
#include"class.hpp"
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include<time.h>
#include<string.h>
using namespace std;
using namespace sf;
void mode(int mode)
{
    PLAYER player[2];
    for(int i=0;i<2;i++)
    {
        player[i].Undotime=1;
        player[i].set(i+1);
    }//玩家初始化
    Texture func[2];
    for(int i=0;i<2;i++)
    {
        char ch[20];
        sprintf(ch,"picture\\decide%d.png",i+1);
        func[i].loadFromFile(ch);
    }
    Sprite decide[2];
    for(int i=0;i<2;i++)
    {
        decide[i].setTexture(func[i]);
        decide[i].setPosition(200,100);
    }//用于做出是否继续游戏的判断 
    Checkerboard chess[15][15];
    for(int i=0;i<15;i++)
    for(int j=0;j<15;j++)
    {
        chess[i][j].TextureSet(i,j);
    }//棋盘初始化
    RenderWindow window(VideoMode(1000,750),"Gobang!");
    window.setFramerateLimit(60);//窗口设定,最高60帧
    Font font;
    font.loadFromFile("picture\\msyh.ttf");//字体读取
    //srand(clock());
    int t=0;
    for(int i=1;window.isOpen();i++)
    {
        if(t>0)//判断是否开始判断胜负
        {
            int play=checkboard(chess,player[(i-1)%2]);//判断是否存在胜负
            if(play)
            {
                window.draw(decide[play-1]);
                window.display();
                while(1)
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                            window.close();
                    }
                    if(player[0].isButtonPressed(Mouse::Left))
                    {
                        int x=player[0].getPosition(window).x;
                        int y=player[0].getPosition(window).y;
                        if(x>=451 && x<=651 && y<=391 && y>=319 )//再来一局
                        {
                            for(int j=0;j<15;j++)
                            for(int k=0;k<15;k++)chess[j][k].Reset();
                            break;
                        }
                        else if(x>=527 && x<=657 && y<=509 && y>=362 )return;//退出至标题
                        
                    }
                }
            }
        }
        window.clear();
        for(int j=0;j<15;j++)
        for(int k=0;k<15;k++)window.draw(chess[j][k]);
        char ch[10];
        sprintf(ch,"Undo:%d",player[i%2].Undotime);
        Text time(ch,font);
        time.setPosition(750,300);
        window.draw(time);
        window.display();
        if(mode==1 || i%2==0)
        {
            while(1)//下子部分
            {
                if(player[i%2].isButtonPressed(Mouse::Left))
                {
                    int x = player[0].getPosition(window).x;
                    int y = player[0].getPosition(window).y;
                    int x1 = x/50;
                    int y1 = y/50;
                    if(x>=750 && x<=1000 && y>=300 && y<=500 )//悔棋
                    {
                        if(!player[i%2].Undotime || t<2 )continue;
                        chess[player[0].x][player[0].y].Reset();
                        chess[player[1].x][player[1].y].Reset();
                        t--;
                        continue;
                    }
                    else if(x1 >= 15 || y1 >= 15 || x1<0 || y1<0)continue;
                    if(chess[x1][y1].type!=0)continue;
                    t++;
                    player[i%2].set(x1,y1);
                    chess[x1][y1].set(i%2+1);
                    window.draw(chess[x1][y1]);
                    window.display();
                    break;
                }
            }
            Sleep(100);
        }
        else if(mode==2 && i%2==1)
        {
            ScanBest(chess,&player[1]);
            window.draw(chess[player[1].x][player[1].y]);
            window.display();
            t++;
        }
    }
}

int checkboard(Checkerboard chess[15][15],PLAYER play)
{
    int l;
    for(int i=1;i<=4;i++)
    {
        l=1;
        for(int j=1;getLine(chess,play,i,j)==play.code;j++)l++;
        for(int j=1;getLine(chess,play,i,-j)==play.code;j++)l++;
        if(l>=5)return play.code;
    }   
    return 0;
}
int getLine(Checkerboard chess[15][15],Point p, int i, int j)
{ // i:方向 j:相对p的顺序值（以p为0） p:当前点
    int x = p.x, y = p.y;
    switch (i) {
        case 1 :
            x = x + j;
            break;
        case 2 :
            x = x + j;
            y = y + j;
            break;
        case 3 :
            y = y + j;
            break;
        case 4 :
            x = x - j;
            y = y + j;
            break;
        case 5 :
            x = x - j;
            break;
        case 6 :
            x = x - j;
            y = y - j;
            break;
        case 7 :
            y = y - j;
            break;
        case 8 :
            x = x + j;
            y = y - j;
    }
    if (x < 0 || y < 0 || x > 14 || y > 14) { // 越界处理
        return -1;
    }
    return chess[x][y].type;
}
int ScanBest(Checkerboard chess[15][15],PLAYER *play)
{
    int orscore[15][15] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
        { 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 6, 5, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 5, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
        { 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
        { 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
    int highest=0,temp=0;
    int num=0;
    Point p,same[60];
    for(int i=0;i<15;i++)
    for(int j=0;j<15;j++)
    {
        temp=0;
        bool con=false;
        p.set(i,j);
        if(chess[j][j].type!=0)continue;
        for(int k=-1;k<2;k++)
        for(int l=-1;l<2;l++)
        {
            if(i+k<1 || i+k>14 || j+l<0 || j+l>14)continue;
            else if( chess[i+k][j+l].type==0 )continue;
            else if(chess[i+k][j+l].type)con=true;
        }
        if(con) 
        {
            temp=Score(chess,p,1)+Score(chess,p,2)+orscore[i][j];
            if(temp>highest)
            {
                highest=temp;
                num=0;
                same[num++]=p;
            }
            else if(temp==highest)
            {
                same[num++]=p;
            }
        }

    }
    if(num)
    {
        srand(clock());
        int t=rand();
        play->x=same[t%num].x;
        play->y=same[t%num].y;
        if(chess[play->x][play->y]!=0)
        {
            t=rand();
            play->x=same[t%num].x;
            play->y=same[t%num].y;
        }
        chess[play->x][play->y].set(2);
    }
    else 
    {
        chess[7][7].set(play->code);
        play->x=7;
        play->y=7;
    }
}
int Score(Checkerboard chess[15][15],Point p,int player)
{
    int value=0;
    int dir=4,t;
    bool con=true;
    bool chessboard[9]={true,true,true,true,true,true,true,true,true};

    for(int i=1;i<=8;i++)//进行4个方向的判断
    {
        if(!chessboard[i])continue;
        if(i>4)dir=-4;
        for(int l=5;l>=2;l--)//下子后成5，活432判断
        {
            for(int j=0;j<l;j++)
            {
                t=1;
                for(int k=1;k<l-j;k++)
                if(getLine(chess,p,i,k)==player)t++;
                else break;
                for(int k=1;k<=j;k++)
                if(getLine(chess,p,i+dir,k)==player)t++;
                else break;
                if(t>=l)
                {
                    if(t>=5)
                    {
                        chessboard[i]=chessboard[i+4]=false;
                        value+=100000;
                        con=false;
                    }
                    else if(t>=4)value+=10000;
                    else if(t>=3)value+=1000;
                    else if(t>=2)value+=100;
                    if(player!=2)value-=500;
                    break;
                }
                else if(t!=l && l==2)
                {
                    if(getLine(chess,p,i,3)==player && getLine(chess,p,i,2)==0 &&
                     getLine(chess,p,i,1)==0 &&getLine(chess,p,i,-1)==0 &&getLine(chess,p,i,4)==0)
                    {
                        value+=650;
                    }
                    else if((getLine(chess,p,i,2)==player && getLine(chess,p,i,1)==0)||(getLine(chess,p,i+dir,2)==player && getLine(chess,p,i+dir,1)==0))
                    {
                        value+=650;
                    }
                }
            }
        }
        if(!con)continue;
        for(int l=5;l>1;l--)//先判断死四和死三和死二
        {
            for(int j=1;j<=l;j++)
            {
                t=1;
                for(int k=1;k<=l-j;k++)
                if(k==l-j)
                {
                    if(getLine(chess,p,i,k)==3-player || getLine(chess,p,i,k)==-1)t++;
                }
                else if(getLine(chess,p,i,k)==player)t++;
                else break;
                for(int k=1;k<=j;k++)
                if(k==j)
                {
                    if(getLine(chess,p,i+dir,k)==3-player || getLine(chess,p,i+dir,k)==-1)t++;
                }
                else if(getLine(chess,p,i+dir,k)==player)t++;
                else break;
                if(t==l+1)
                {
                    con=false;
                    if(l==5)value+=1000;
                    else if(l==4)value+=100;
                    else if(l==3)value+=10;
                    if(player!=2)value-=500;
                    chessboard[i]=chessboard[i+4]=false;
                    break;
                }
            }
            if(!con)break;
        }
        if(!con)continue;
        else if(con)//如果之前该方向已判断出为死棋型则不进行，冲四，眠三，眠二的判断
        {
            for(int j=1;j<=4;j++)//第一种连续的冲4，一端为墙或者对方
            {
                t=1;
                for(int k=1;k<=5-j;k++)
                {
                    if(k==j)
                    {
                        if(getLine(chess,p,i,k)==3-player || getLine(chess,p,i,k)==-1 )t++;
                    }
                    else if(getLine(chess,p,i,k)==player)t++;
                }
                for(int k=1;k<=j;k++)
                {
                    if(k==j)
                    {
                        if(getLine(chess,p,i+dir,k)==3-player || getLine(chess,p,i+dir,k)==-1 )t++;
                    }
                    else if(getLine(chess,p,i,k)==player)t++;
                }
                if(t==5)
                {
                    bool con=false;
                    value+=2500;
                    if(player!=2)value-=500;
                    break;
                }
            }
            if(!con)continue;
            for(int n=0;n<=1;n++)//判断两种冲4 0222020 0220220
            {
                con=true;
                for(int j=1;j<=5;j++)
                {
                    t=1;
                    if(j==3-n)continue;
                    if(j<3-n)
                    {
                        for(int k=1;k<=6-j;k++)
                        {
                            if(k==j || k==4-j-n)
                            {
                                if(getLine(chess,p,i,k)==0 )t++;
                            }
                            else if(getLine(chess,p,i,k)==player)t++;
                        }
                        for(int k=1;k<=j;k++)
                        {
                            if(k==j)
                            {
                                if(getLine(chess,p,i+dir,k)==0)t++;
                            }
                            else if(getLine(chess,p,i+dir,k)==player)t++;
                        }
                    }
                    else if(j>3-n)
                    {
                        for(int k=1;k<=6-j;k++)
                        {
                            if(k==6-j)
                            {
                                if(getLine(chess,p,i,1)==0)t++;
                            }
                            else if(getLine(chess,p,i,1)==player)t++;
                        }
                        for(int k=1;k<=j;k++)
                        {
                            if((k==1 || k==j ) && getLine(chess,p,i+dir,k)==0)
                            {
                                t++;
                            }
                            else if(getLine(chess,p,i+dir,k)==player)t++;
                        }
                    }
                    if(t==7)
                    {
                        bool con=false;
                        value+=3000-n*400;
                        if(player!=2)value-=500;
                        break;
                    }
                }
                if(!con)break;
            }
            if(!con)continue;
            for(int j=1;j<=3;j++)//判断一种眠3 12220
            {
                t=1;
                for(int k=1;k<=4-j;k++)
                {
                    if(k==4-j&& getLine(chess,p,i,k)==0)t++;
                    else if(getLine(chess,p,i,k)==player)t++;
                }
                for(int k=1;k<=4;k++)
                {
                    if(k==j && (getLine(chess,p,i,k)==-1 || getLine(chess,p,i,k)==3-player ) )t++;
                    else if(getLine(chess,p,i,k)==player)t++;
                }
                if(t==5)
                {
                    bool con=false;
                    value+=500;
                    if(player!=2)value-=500;
                    break;
                }
            }
            if(!con)continue;
            for(int n=0;n<=1;n++)//判断两种眠3 122020 120220
            {
                con=true;
                for(int j=1;j<=4;j++)
                {
                    t=1;
                    if(j==3-n)continue;
                    if(j<3-n)
                    {
                        for(int k=1;k<=5-j;k++)
                        {
                            if( (k==5-j || k==3-j-n ) && getLine(chess,p,i,k)==0 )t++;
                            else if(getLine(chess,p,i,k)==player)t++;
                        }
                        for(int k=1;k<=j;k++)
                        {
                            if(getLine(chess,p,i+dir,k)==-1 || getLine(chess,p,i+dir,k)==3-player )t++;
                            else if( getLine(chess,p,i+dir,k)==player )t++;
                        }
                    }
                    else if(j>3-n)
                    {
                        for(int k=1;k<=5-j;k++)
                        {
                            if( k==5-j && getLine(chess,p,i,k)==0 )t++;
                            else if(getLine(chess,p,i,k)==player)t++;
                        }
                        for(int k=1;k<=j;k++)
                        {
                            if(k==-3+j+n)
                            {
                                if(getLine(chess,p,i+dir,k)==0)t++;
                            }
                            else if(k==j && ( getLine(chess,p,i+dir,k)==3-player|| getLine(chess,p,i+dir,k)==-1 ) )t++;
                            else if(getLine(chess,p,i+dir,k)==player)t++;
                        }
                    }
                    if(t==6)
                    {
                        bool con=false;
                        value+=800-n*200;
                        if(player!=2)value-=500;
                        break;
                    }
                }
                if(!con)break;
            }
            if(!con)continue;
            for(int j=1;j<=4;j++)//判断眠3 022020
            {
                t=1;
                if(j==3)continue;
                if(j<3)
                {
                    for(int k=1;k<=5-j;k++)
                    {
                        if(k==3-j || k==5-j)
                        {
                            if(getLine(chess,p,i,k)==0)t++;
                        }
                        else if(getLine(chess,p,i,k)==player)t++;
                    }
                    for(int k=1;k<=j;k++)
                    {
                        if(k==j)
                        {
                            if(getLine(chess,p,i+dir,k)==0)t++;
                        } 
                        else if(getLine(chess,p,i+dir,k)==player)t++;
                    }
                }
                else if(j>3)
                {
                    for(int k=1;k<=5-j;k++)
                    {
                        if(k==5-j)
                        {
                            if(getLine(chess,p,i,k)==0)t++;
                        }
                        else if(getLine(chess,p,i,k)==player)t++;
                    }
                    for(int k=1;k<=j;k++)
                    {
                        if(k==j || k==1 )
                        {
                            if(getLine(chess,p,i+dir,k)==0)t++;
                        }
                        else if(getLine(chess,p,i+dir,k)==player)t++;
                    }
                }
                if(t==6)
                {
                    bool con=false;
                    value+=800;
                    if(player!=2)value-=500;
                    break;
                }
            }
            if(!con)continue;
            for(int j=1;j<=5;j++)//判断眠3 0202020
            {
                con=true;
                int t1=1,t2=0,t=0;
                
                if(j%2==0)continue;
                int time=(j+1)/2;
                for(int k=1;k<=6-j;k++)
                {
                    if(t1<=4-time && getLine(chess,p,i,k)==2 && (k+j)%2==1)t1++;
                    else if(t2<=4-time && getLine(chess,p,i,k)==2 && (k+j)%2==0 )t2++;
                }
                t=t1+t2;
                t1=1;t2=0;
                for(int k=1;k<=j;k++)
                {
                    if(t1<=time && getLine(chess,p,i+dir,k)==2 && (j-k)%2==1)t1++;
                    else if (t2<=time && getLine(chess,p,i+dir,k)==2 && (j-k)%2==0 )t2++;
                }
                t+=(t1+t2);
                if(t==7)
                {
                    bool con=false;
                    value+=550;
                    if(player!=2)value-=500;
                    break;
                }
            }
            if(!con)continue;
            if(dir==4)
            for(int j=1;j<=3;j++)//判断眠3 1022201
            {
                con=true;t=1;
                for(int k=1;k<=5-j;j++)
                {
                    if(k==5-j)
                    {
                        if( getLine(chess,p,i,k)==3-player )t++;
                    }
                    else if(k==4-j)
                    {
                        if( getLine(chess,p,i,k)==0 )t++;
                    }
                    else if( getLine(chess,p,i,j)==player )t++;
                }
                for(int k=1;k<=j+1;k++)
                {
                    if(k==j+1)
                    {
                        if( getLine(chess,p,i+dir,k)==3-player )t++;
                    }
                    else if(k==j)
                    {
                        if( getLine(chess,p,i+dir,k)==0 )t++;
                    }
                    else if( getLine(chess,p,i+dir,j)==player )t++;
                }
                if(t==7)
                {
                    con=false;
                    value+=400;
                    if(player!=2)value-=500;
                    break;
                }
            }
            if(!con)continue;
            //判断眠2 020020
            if(getLine(chess,p,i,1)==0 && getLine(chess,p,i,2)==0 && getLine(chess,p,i,3)==0 && 
            getLine(chess,p,i,4)==player && getLine(chess,p,i,5)==0 &&getLine(chess,p,i,-1)==0 )
            {
                value+=200;
                if(player!=2)value-=500;
                con=false;
            }
            //眠2 1220
            if(!con)continue;
            for(int j=1;j<=2;j++)
            {
                for(int k=1;k<=3-j;k++)
                {
                    if(k==3-j)
                    {
                        if(getLine(chess,p,i,k)==0)t++;
                    }
                    else if(getLine(chess,p,i,k)==player)t++;
                }
                for(int k=1;k<=j;k++)
                {
                    if(k==j)
                    {
                        if(getLine(chess,p,i+dir,k)==3-player || getLine(chess,p,i,k)==-1 )t++;
                    }
                    else if(getLine(chess,p,i+dir,k)==player)t++;
                }
                if(t==4)
                {
                    value+=150;
                    if(player!=2)value-=500;
                    con=false;
                }
            }
            //眠2 0120200
            if(!con)continue;
            if(getLine(chess,p,i,1)==0 && getLine(chess,p,i,2)==player && getLine(chess,p,i,3)==0 && 
            getLine(chess,p,i,4)==0 && (getLine(chess,p,i,-1)==0 || getLine(chess,p,i,-1)==-1 ) )
            {
                value+=150;
                if(player!=2)value-=500;
                con=false;
            }
            if(!con)continue;
            if(getLine(chess,p,i,-1)==0 && getLine(chess,p,i,-2)==player && getLine(chess,p,i,1)==0 && 
            getLine(chess,p,i,2)==0 && (getLine(chess,p,i,-3)==0 || getLine(chess,p,i,-3)==-1 ) )
            {
                value+=150;
                if(player!=2)value-=500;
                con=false;
            }
            
        }
    }

}