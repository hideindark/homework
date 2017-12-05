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
struct point : public position
{
    position f;
};
bool check(vector<point> openlist,vector<point> closelist,point temp);
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
    while(!openlist.empty())//DFS
    {
        t=openlist.at(0);
        int r=t.r;
        int c=t.c;
        if(r>0)
        {
            if(maze[r][c][1]==1)
            {
                
                temp.f=temp;
                temp.r--;
                if(check(openlist,closelist,temp))openlist.push_back(temp);
                temp.r++;
            }
        }
        if(c>0)
        {
            if(maze[r][c][3]==1)
            {
                temp.f=temp;
                temp.c--;
                if(check(openlist,closelist,temp))openlist.push_back(temp);
                temp.c++;
            }
        }
        if(r<rowmax-1)
        {
            if(maze[r][c][4]==1)
            {
                temp.f=temp;
                temp.r++;
                if(check(openlist,closelist,temp))openlist.push_back(temp);
                temp.r--;
            }
        }
        if(c<conmax-1)
        {
            if(maze[r][c][3]==1)
            {
                temp.f=temp;
                temp.c++;
                if(check(openlist,closelist,temp))openlist.push_back(temp);
                temp.c--;
            }
        }
        closelist.push_back(temp);
        openlist.erase(openlist.begin());
    }
    //创建通路
    temp.r=rowmax-1;
    temp.c=conmax-1;
    for(int i=0;i<closelist.size();i++)
    {
        t=closelist[i];
        if(t.r==temp.r && t.r==temp.r)
        {
            int r=temp.r-t.r;
            int c=temp.c-t.c;
            if(r==1)
            {
                maze[temp.r][temp.c][2]=maze[temp.r][temp.c][0]=3;
                maze[t.r][t.c][4]=maze[t.r][t.c][0]=3;
            }
            else if(r=-1)
            {
                maze[temp.r][temp.c][4]=maze[temp.r][temp.c][0]=3;
                maze[t.r][t.c][2]=maze[t.r][t.c][0]=3;
            }
            if(c==1)
            {
                maze[temp.r][temp.c][1]=maze[temp.r][temp.c][0]=3;
                maze[t.r][t.c][3]=maze[t.r][t.c][0]=3;
            }
            else if(c==-1)
            {
                maze[temp.r][temp.c][3]=maze[temp.r][temp.c][0]=3;
                maze[t.r][t.c][1]=maze[t.r][t.c][0]=3;
            }
            temp.r=t.f.r;
            temp.c=t.f.c;
            i=0;
            if(t.f.r==0 && t.f.c==0)break;
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
                    if(l==1)maze[i][j][2]==1?cout<<' ':cout<<"#";
                    else cout<<"#";
                }break;
                case 1:
                for(int l=1;l<=3;l++)
                {
                    switch(l)
                    {
                        case 1:maze[i][j][1]==1?cout<<' ':cout<<"#";break;
                        case 2:maze[i][j][0]==1?cout<<' ':cout<<"#";break;
                        case 3:maze[i][j][3]==1?cout<<' ' : cout<<"#";break;
                    }
                }break;
                case 2:
                for(int l=0;l<3;l++)
                {
                    if(l==1)maze[i][j][4]==1?cout<<' ':cout<<"#";
                    else cout<<"#";
                }break;
            }
        }
        cout<<endl;
    }

}
bool check(vector<position> openlist,vector<position> closelist,point temp)
{
    if(!openlist.empty())for(int i=0;i<openlist.size();i++)if(openlist[i].r==temp.r && openlist[i].c==temp.c)return false;
    if(!closelist.empty())for(int i=0;i<closelist.size();i++)if(closelist[i].r==temp.r && closelist[i].c==temp.c)return false;
    return true;
    
}