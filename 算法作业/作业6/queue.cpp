#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace stdl;
class queue
{
    public:
    int pop();
    bool push(int p);
    void empty();
    void 
    private:
    int *queue;
    int num;
}
int queue::pop()
{
    if(num>0)return queue[--num];
    else printf("fault:Don't have number")
}
bool push()
{
    
}