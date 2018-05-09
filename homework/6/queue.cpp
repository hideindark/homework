#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace stdl;
class queue
{
    public:
    int pop();
    bool push(int p);
    void top();
    queue();//队列初始化
    ~queue();
    private:
    int *queue_int;
    int num;
    int max;
};
bool queue::pop()
{
    if(num>0)
    {
        int temp=queue_int[0];
        for(int i=num-1;i>0;i--)queue_int[i-1]=queue_int[i];
        num--;
        cout<<temp<<"\n";
        return true;
    }
    else cout<<"Don't have number";
    return false;
}
bool queue::push(int p)
{
    if(num+1<=max)
    {
        queue_int[num++]=p;
        return true;
    }
    else cout<<"Can't get more number"
}
bool queue::list()
{
    if(num)for(int i=0;i<num;i++)cout<<queue_int[i];
    else cout<<"Don't have number";
}
queue::queue()
{
    max=300;
    num=0;
    queue_int = new int[max];
}
queue::~queue()
{
    delete queue_int ;
}
void queue::top()
{
    if(num>0)cout<<queue_int[0]<<endl;
    else cout<<"queue is empty";
    return ;
}
int main()
{
    queue test;
    do
    {
        int temp;
        cout<<"What's you want to do\n"<<"1.add\n"<<"2.pop\n"<<"3.get top\n";
        cin>>temp;
        switch(temp)
        {
            case 1:
            int p;
            cin>>p;
            test.push(p);break;
            case 2:
            test.pop();break;
            case 3:
            test.top();break;
            default:break
        }
    }while(1)
}