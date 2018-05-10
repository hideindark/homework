#include<iostream>
using namespace std;
class stack
{
    public:
    void push();
    void pop();
    void list();
    stack();
    private:
    int num;
    int stack_int[300];
};
void stack::push()
{
    int temp;
    cin>>temp;
    if(num<300)stack_int[num++]=temp;
    else cout<<"full";
    list();
}
void stack::pop()
{
    if(num>0)cout<<stack_int[num--]<<"\n";
    list();
}
void list()
{
    for(int i=0;i<num;i++)cout<<stack_int[i]<<" ";
    cout<<endl;
}
stack::stack()
{
    num=0;
}
int main()
{
    stack test;
    while(1)
    {
        int choice;
        cout<<"1.add\n"<<"2.pop\n"<<"3.show\n";
        cin>>choice;
        switch(choice)
        {
            case 1:test.push();break;
            case 2:test.pop();break;
            case 3:test.list();break;
        }
    }
}