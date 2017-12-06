#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<cstdio>
#include<windows.h>
using namespace std;
struct position
{
    int r,c;
};
struct point
{
    int r,c;
    position f;
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
    temp.r=temp.c=0;
    vector<point> openlist,closelist;
    openlist.push_back(temp);
    point t;
    while(!openlist.empty())//BFS
    {
        cout<<openlist.size()<<" "<<closelist.size()<<"||";
        t=openlist.at(0);
        int r=t.r;
        int c=t.c;
        t.f.r=t.r;
        t.f.c=t.c;
        if(r>0)//向上
        {
            if(maze[r][c][2]==1)
            {
                
                t.r--;
                if(check_move(openlist,closelist,t))
                {
                    openlist.push_back(t);
                }
                t.r++;
            }
        }
        if(c>0)//向左
        {
            if(maze[r][c][1]==1)
            {
                t.c--;
                if(check_move(openlist,closelist,t))
                {
                    openlist.push_back(t);
                }
                t.c++;
            }
        }
        if(r<rowmax-1)//向下
        {
            if(maze[r][c][4]==1)
            {
                t.r++;
                if(check_move(openlist,closelist,t))
                {
                    openlist.push_back(t);
                }
                t.r--;
            }
        }
        if(c<conmax-1)//向右
        {
            if(maze[r][c][3]==1)
            {
                t.c++;
                if(check_move(openlist,closelist,t))
                {
                    openlist.push_back(t);
                }
                t.c--;
            }
        }
        closelist.push_back(t);
        openlist.erase(openlist.begin());  
        cout<<openlist.size()<<" "<<closelist.size()<<endl;
    }
    //创建通路
    temp.r=rowmax-1;
    temp.c=conmax-1;
    for(int i=0;i<closelist.size();i++)
    {
        t=closelist.at(i);
        if(t.r==temp.r && t.r==temp.r)
        {
            int r=temp.r-t.r;
            int c=temp.c-t.c;
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
    //绘制迷宫
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
bool check_move(vector<point> openlist,vector<point> closelist,point temp)
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