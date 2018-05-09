#include <queue>
#include <stack>
#include <iostream>
#include <cstdio>
using namespace std;

void BFS(int map[7][7],int start,int end);
int main()
{
    int map[7][7]=
    {
        {0,1,0,1,0,0,0},
        {0,0,0,1,1,0,0},
        {1,0,0,0,0,1,0},
        {0,0,1,0,1,1,1},
        {0,0,0,0,0,0,1},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0}
    };
    int end;
    cin>>end;
    BFS(map,3,end);
}
void BFS(int map[7][7],int start,int end)
{
    queue<int> checking;
    checking.push(start-1);
    stack<int> path;
    int check;
    bool find=false;
    int before[7];
    while(!checking.empty())
    {
        check=checking.front();
        checking.pop();
        if(map[check][end-1]==1)
        {
            before[end-1]=check;
            find=true;
            break;
        }
        for(int i=0;i<7;i++)
        if(map[check][i]==1)
        {
            checking.push(i);
            for(int j=0;j<7;j++)map[j][i]=2;
            before[i]=check;
        }
        for(int i=0;i<7;i++)map[i][check]=2;
    }
    if(!find)cout<<"Not find a way from "<<start<<" to "<<end<<endl;
    else
    {
        int now=end-1;
        do
        {
            path.push(now+1);
            now=before[now];
        }while(now!=start-1);
        cout<<start<<"->";
        while(!path.empty())
        {
            cout<<path.top()<<"->";
            path.pop();
        }
    }
}