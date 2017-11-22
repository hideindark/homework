#include<iostream>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<time.h>
using namespace std;
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
    int maze[rowmax][conmax][5];
    for(int i=0;i<rowmax;i++)
    for(int j=0;j<conmax;j++)
    for(int k=0;k<5;k++)maze[i][j][k]=0;//重置迷宫
    //生成迷宫，prim随机算法
    vector<position> history;
    vector <int> check;
    position temp;
    temp.x=0;
    temp.y=0;
    history.push_back(temp);
    while(!history.empty())
    {
        srand(clock());
        int p=rand()%history.gsize();
        temp=history.at(p);
        int x=temp.x;
        int y=temp.y;
        maze[x][y][0]=1;
        history.erase(history.begin()+p);
        check.clear();
        if(y>0)//左
        {
            if(maze[x][y-1][0]==1)check.push_back(1);
            else if(maze[x][y-1][0]==0)
            {
                temp.y-=1;
                history.push_back(temp);
                maze[x][y-1][0]=2;
            }
        }
        
        if(x>0)//上
        {
            if(maze[x-1][y][0]==1)check.push_back(2);
            else if(maze[x-1][y][0]==0)
            {
                temp.x-=1;
                history.push_back(temp);
                maze[x-1][y][0]=2;
            }
        }
        
        if(y < conmax-1)//右
        {
            if(maze[x][y+1][0]==1)check.push_back(3);
            else if(maze[x][y+1][0]==0)
            {
                temp.y+=1;
                history.push_back(temp);
                maze[x][y+1][0]=2;
            }
        }
        
        if(x < rowmax-1)//下
        {
            if(maze[x+1][y][0]==1)check.push_back(4);
            else if(maze[x+1][y][0]==0)
            {
                temp.x+=1;
                history.push_back(temp);
                maze[x+1][y][0]=2;
            }
        }
        
        //选择位置挖墙
        if(!check.empty())
        {
            srand(clock());
            int dir=check.at(rand()%check.size());
            switch(dir)
            {
                case 1:maze[x][y][1]=1;y-=1;maze[x][y][3]=1;break;
                case 2:maze[x][y][2]=1;x-=1;maze[x][y][4]=1;break;
                case 3:maze[x][y][3]=1;y+=1;maze[x][y][1]=1;break;
                case 4:maze[x][y][4]=1;x+=1;maze[x][y][2]=1;break;
            }
        }
    }
    maze[0][0][1]=1;
    maze[rowmax-1][conmax-1][3]=1;
    for(int i=0;i<rowmax;i++)
    {
        for(int j=0;j<conmax;j++)
        {
            if(maze[i][j][0]==0)cout<<"#";
            else if(maze[i][j][0]==1)cout<<" ";
            
        }
        cout<<endl;
    }
}
