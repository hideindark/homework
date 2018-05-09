#include<iostream>
class stack
{
    public:
    void push();
    void pop();
    void list();
    private:
    int num;
    int stack_int[300];
};
void stack::push()
{
    int temp;
    cin>>temp;
    if(num<300)stack_int[num++]=temp;
}
void stack::pop()
{
    
}