#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<time.h>
using namespace std;
int CrateMaze(int maze[][],int RowMax,int ConMax);
struct position
{
    int r,c;
};
int main()
{
    int rowmax,conmax;
    cout<<"row:"<<endl;
    cin>>rowmax;
    cout<<"Columns:"<<endl;
    cin>>conmax;
    int maze[rowmax][conmax];
    for(int i=0;i<rowmax;i++)
    for(int j=0;j<conmax;j++)maze[i][j]=0;//重置迷宫
    CrearMaze(maze,rowmax,conmax)
}
int CrateMaze(int maze[][],int RowMax,int ConMax)//生成迷宫，prim随机算法
{
    srand(clock());
    vector<position> history;
    vector <int> check;
    position temp;
    temp.r=rand()%RowMax;
    temp.c=rand()%CowMax;
    history.push_back(temp);
    //将该点周围的墙加入,主要是加入该点上下左右的墙，因为这里的迷宫不走斜角所以不加入斜对角的点
    //加入顺序为左上右下顺时针
    while(!history.empty())
    {
        int p=rand()%history.size();
        temp=history.at(p);
        int r=temp.r;
        int c=temp.c;
        int time=0;
        history.erase(history.begin()+p);
        if(c>0)//左
        {
            if(maze[r][c-1]==1)
        }
    }
}