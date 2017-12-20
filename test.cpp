#include <iostream>
#include <queue>
#include <cstdio>
using namespace std;


struct Info
{
    string name;
    float score;
    //重载"<"操作符，指定优先级；
    bool operator < (const Info &a) const
    {
        //按score由小到大排列，如果要由大到小排列，使用“>”即可；
        return a.score < score;
    }
};

int main(int argc, char *argv[])
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    //定义优先队列对象，元素类型为Info结构体型;
    priority_queue <Info> pq;
    Info info;  //定义结构体变量;

    //入队；
    info.name = "Jack";
    info.score = 68.5;
    pq.push(info);

    info.name = "Bomi";
    info.score = 18.5;
    pq.push(info);

    info.name = "Peti";
    info.score = 90;
    pq.push(info);
    //元素出队；
    while(!pq.empty()) {
        //返回队首元素；
        cout << pq.top().name << " " << pq.top().score << endl;
        //将队头元素弹出;
        pq.pop();
    }
    return 0;
}