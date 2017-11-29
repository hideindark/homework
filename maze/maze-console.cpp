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
    vector<position> history;
    vector <int> check;
    position temp;
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
                temp.c-=1;
                history.push_back(temp);
                maze[r][c-1][0]=2;
            }
        }
        if(r>0)//上
        {
            if(maze[r-1][c][0]==1)check.push_back(2);
            else if(maze[r-1][c][0]==0)
            {
                temp.r-=1;
                history.push_back(temp);
                maze[r-1][c][0]=2;
            }
        }
        
        if(c < conmax-1)//右
        {
            if(maze[r][c+1][0]==1)check.push_back(3);
            else if(maze[r][c+1][0]==0)
            {
                temp.c+=1;
                history.push_back(temp);
                maze[r][c+1][0]=2;
            }
        }
        
        if(r < rowmax-1)//下
        {
            if(maze[r+1][c][0]==1)check.push_back(4);
            else if(maze[r+1][c][0]==0)
            {
                temp.r+=1;
                history.push_back(temp);
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
    //绘制地图，先判断判断该点
    /*
    for(int i=0;i<rowmax;i++)
    {
        for(int k=0;k<2;k++)
        {
            for(int j=0;j<conmax;j++)
            {
                if(!k)
                {
                    for(int l=0;l<3;l++)
                    {
                        if(l==1 && maze[i][j][2]==1 )cout<<" ";
                        else cout<<"■";
                    }
                }
                else
                {
                    for(int l=1;l>=0;l--)
                    {
                        if(maze[i][j][l]!=0)cout<<" ";
                        else if(maze[i][j][l]==0)cout<<"■";
                    }
                    if(j==conmax-1 && k==1)
                    switch(maze[i][j][3])
                    {
                        case 0:cout<<"■";
                        case 1:cout<<" ";
                    }
                }
            }
            cout<<endl;
        }
    }
    for(int j=0;j<conmax;j++)
    for(int l=0;l<3;l++)
    {
        if(l==1 && maze[rowmax-1][j][4]==1 )cout<<" ";
        else cout<<"■";
    }
    Sleep(30000);
    */
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
                    if(l==1)maze[i][j][2]==1?cout<<" ":cout<<"■";
                    else cout<<"■";
                }break;
                case 1:
                for(int l=1;l<=3;l++)
                {
                    switch(l)
                    {
                        case 1:maze[i][j][1]==1?cout<<" ":cout<<"■";
                        case 2:maze[i][j][0]==1?cout<<" ":cout<<"■";
                        case 3:maze[i][j][3]==1?cout<<" " : cout<<"■";
                    }
                }break;
                case 2:
                for(int l=0;l<3;l++)
                {
                    if(l==1)maze[i][j][4]==1?cout<<" ":cout<<"■";
                    else cout<<"■";
                }break;
            }
        }
        cout<<endl;
    }
}
