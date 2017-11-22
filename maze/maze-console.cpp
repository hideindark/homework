#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<time.h>
using namespace std;
int CrateMaze(int maze[][],int RowMax,int ConMax);
struct position
{
    int x,y;
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
    
}