#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<cstdio>
#include<windows.h>
using namespace std;
//直接取自上学期的迷宫作业，小bug就不修了
struct position
{
    int r,c;
};
struct point
{
    int r,c;
    position f;//记录上一点的位置
};
bool check_move(vector<point> openlist,vector<point> closelist,point temp);
int main()
{
    int rowmax,conmax;
    cout<<"row:"<<endl;
    scanf("%d",&rowmax);
    cout<<"Columns:"<<endl;
    scanf("%d",&conmax);
    int maze[rowmax][conmax][5];
    for(int i=0;i<rowmax;i++)
    for(int j=0;j<conmax;j++)
    for(int k=0;k<5;k++)maze[i][j][k]=0;//重置迷宫
    //生成迷宫，prim随机算法
    /*
    prim随机算法原理：
    1.让迷宫全是墙.  
    2.选一个单元格作为迷宫的通路，然后把它的邻墙放入列表  
    3.当列表里还有墙时  
    1.从列表里随机选一个墙，如果这面墙分隔的两个单元格只有一个单元格被访问过  
        1.那就从列表里移除这面墙，即把墙打通，让未访问的单元格成为迷宫的通路  
        2.把这个格子的墙加入列表  
        2.如果墙两面的单元格都已经被访问过，那就从列表里移除这面墙  
    */
    vector<point> history;
    vector <int> check;
    point temp;
    temp.r=0;
    temp.c=0;
    history.push_back(temp);
    while(!history.empty())
    {
        srand(clock());
        int p=rand()%history.size();
        temp=history.at(p);
        int r=temp.r;
        int c=temp.c;
        maze[r][c][0]=1;
        history.erase(history.begin()+p);
        check.clear();
        if(c>0)//左
        {
            if(maze[r][c-1][0]==1)check.push_back(1);
            else if(maze[r][c-1][0]==0)
            {
                temp.c--;
                history.push_back(temp);
                temp.c++;
                maze[r][c-1][0]=2;
            }
        }
        if(r>0)//上
        {
            if(maze[r-1][c][0]==1)check.push_back(2);
            else if(maze[r-1][c][0]==0)
            {
                temp.r--;
                history.push_back(temp);
                temp.r++;
                maze[r-1][c][0]=2;
            }
        }
        
        if(c < conmax-1)//右
        {
            if(maze[r][c+1][0]==1)check.push_back(3);
            else if(maze[r][c+1][0]==0)
            {
                temp.c++;
                history.push_back(temp);
                temp.c--;
                maze[r][c+1][0]=2;
            }
        }
        
        if(r < rowmax-1)//下
        {
            if(maze[r+1][c][0]==1)check.push_back(4);
            else if(maze[r+1][c][0]==0)
            {
                temp.r++;
                history.push_back(temp);
                temp.r--;
                maze[r+1][c][0]=2;
            }
        }
        
        //选择位置挖墙
        if(!check.empty())
        {
            int dir=check.at(rand()%check.size());
            switch(dir)
            {
                case 1:maze[r][c][1]=1;c-=1;maze[r][c][3]=1;break;
                case 2:maze[r][c][2]=1;r-=1;maze[r][c][4]=1;break;
                case 3:maze[r][c][3]=1;c+=1;maze[r][c][1]=1;break;
                case 4:maze[r][c][4]=1;r+=1;maze[r][c][2]=1;break;
            }
        }
    }
    maze[0][0][1]=1;
    maze[rowmax-1][conmax-1][3]=1;
    //寻路
    temp.r=temp.c=temp.f.r=temp.f.c=0;
    vector<point> openlist,closelist;//openlist用于存储等待移动的点，closelist存储已经走过的点最后用于寻找路线
    openlist.push_back(temp);
    point t;
    while(!openlist.empty())//BFS，走过每一个点
    {
        t=openlist.at(0);
        int r=t.r;
        int c=t.c;
        temp.r=temp.f.r=t.r;
        temp.c=temp.f.c=t.c;
        if(r>0)//向上
        {
            if(maze[r][c][2]==1)
            {
                temp.r--;
                if(check_move(openlist,closelist,temp))
                {
                    openlist.push_back(temp);
                }
                temp.r++;
            }
        }
        if(c>0)//向左
        {
            if(maze[r][c][1]==1)
            {
                temp.c--;
                if(check_move(openlist,closelist,temp))
                {
                    openlist.push_back(temp);
                }
                temp.c++;
            }
        }
        if(r<rowmax-1)//向下
        {
            if(maze[r][c][4]==1)
            {
                temp.r++;
                if(check_move(openlist,closelist,temp))
                {
                    openlist.push_back(temp);
                }
                temp.r--;
            }
        }
        if(c<conmax-1)//向右
        {
            if(maze[r][c][3]==1)
            {
                temp.c++;
                if(check_move(openlist,closelist,temp))
                {
                    openlist.push_back(temp);
                }
                temp.c--;
            }
        }
        closelist.push_back(t);
        openlist.erase(openlist.begin());
    }
    //创建通路，通过从终点逐渐回溯到起点
    temp.r=rowmax-1;
    temp.c=conmax-1;
    for(int i=0;i<closelist.size();i++)
    {
        t=closelist.at(i);
        if(t.r==temp.r && t.c==temp.c)
        {
            int r=temp.r-t.f.r;
            int c=temp.c-t.f.c;
            if(r==1)
            {
                maze[temp.r][temp.c][2]=maze[temp.r][temp.c][0]=3;
                maze[t.f.r][t.f.c][4]=maze[t.f.r][t.f.c][0]=3;
            }
            else if(r=-1)
            {
                maze[temp.r][temp.c][4]=maze[temp.r][temp.c][0]=3;
                maze[t.f.r][t.f.c][2]=maze[t.f.r][t.f.c][0]=3;
            }
            if(c==1)
            {
                maze[temp.r][temp.c][1]=maze[temp.r][temp.c][0]=3;
                maze[t.f.r][t.f.c][3]=maze[t.f.r][t.f.c][0]=3;
            }
            else if(c==-1)
            {
                maze[temp.r][temp.c][3]=maze[temp.r][temp.c][0]=3;
                maze[t.f.r][t.f.c][1]=maze[t.f.r][t.f.c][0]=3;
            }
            if(t.f.r==0 && t.f.c==0)break;
            temp.r=t.f.r;
            temp.c=t.f.c;
            i=0;
        }
    }
    //绘制迷宫与路线，0为路线，空格为通路，#为墙
    for(int i=0;i<rowmax;i++)
    for(int k=0;k<3;k++)
    {
        for(int j=0;j<conmax;j++)
        {
            switch(k)
            {
                case 0:
                for(int l=0;l<3;l++)
                {
                    if(l==1)maze[i][j][2]==1?cout<<' ':(maze[i][j][2]==3?cout<<"0":cout<<"#");
                    else cout<<"#";
                }break;
                case 1:
                for(int l=1;l<=3;l++)
                {
                    switch(l)
                    {
                        case 1:maze[i][j][1]==1?cout<<' ':(maze[i][j][1]==3?cout<<"0":cout<<"#");break;
                        case 2:maze[i][j][0]==1?cout<<' ':(maze[i][j][0]==3?cout<<"0":cout<<"#");break;
                        case 3:maze[i][j][3]==1?cout<<' ' :(maze[i][j][3]==3?cout<<"0":cout<<"#");break;
                    }
                }break;
                case 2:
                for(int l=0;l<3;l++)
                {
                    if(l==1)maze[i][j][4]==1?cout<<' ':(maze[i][j][4]==3?cout<<"0":cout<<"#");
                    else cout<<"#";
                }break;
            }
        }
        cout<<endl;
    }

}
bool check_move(vector<point> openlist,vector<point> closelist,point temp)//用于在BFS处判断该点是否已经被检查了
{
    if(!openlist.empty())
    {
        for(int i=0;i<openlist.size();i++)
        {
            if(openlist.at(i).r==temp.r && openlist.at(i).c==temp.c)return false;
        }
    }
    if(!closelist.empty())
    {
        for(int i=0;i<closelist.size();i++)
        {
            if(closelist.at(i).r==temp.r && closelist.at(i).c==temp.c)return false;
        }
    }
    return true;
    
}