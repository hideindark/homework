#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
class card
{
    public:
    card();
    int level;//1为普通卡，2为银卡，3为金卡
    char name[40];//姓名
    int score;//积分
    bool use;//确认该位置是否被使用
};
class manage//会员卡的功能和数据定义
{
    public:
    void Add();//添加
    void Delete();//删除
    int Find();//查询
    void change();//修改
    void hash(int total,card newcard);//哈希插入
    void list();//列出所有的数据
    manage();
    private:
    vector<card> cards;
};
card::card()
{
    use=false;
}
void manage::Add()
{
    card newcard;
    newcard.use=true;
    newcard.score=0;
    cout<<"Input your name:";
    cin>>newcard.name;
    do
    {
        cout<<"Input new VIP's level:";
        cin>>newcard.level;
    }while(newcard.level>3 || newcard.level<1);
    int total=0;
    for(int i=0;i<strlen(newcard.name);i++)total+=newcard.name[i];
    hash(total,newcard);
}
void manage::Delete()
{
    int p=Find();
    if(p!=-1)cards[p].use=false;
    else cout<<"Dont't find";
    return ;
}
void manage::change()
{
    int p=Find();
    if(p==-1)
    {
        cout<<"Don't find";
        return ;
    }
    card temp=cards[p];
    cards[p].use=false;
    do
    {
        cout<<"What's you want to change\n"<<"1.integral\n"<<"2.name\n"<<"3.level\n"<<"4.quit"<<endl;
        int choice;
        cin>>choice;
        switch(choice)
        {
            case 1:
            int score;
            cout<<"new intergral:";
            do cin>>score;
            while(score<0);
            temp.score=score;break;
            case 2:
            char name[40];
            cout<<"Input new name:";
            cin>>name;
            for(int i=0;i<strlen(name);i++)temp.name[i]=name[i];break;
            case 3:
            int level;
            cout<<"input new level:";
            do cin>>level;
            while(level<1 || level>3);
            temp.level=level;break;
        };
        }while(choice!=4);
        int total=0;
        for(int i=0;i<strlen(temp.name);i++)total+=temp.name[i];
        hash(total,temp);
}
int manage::Find()
{
    char name[20];
    int total=0;
    int time=0;
    cout<<"Who is you want to find:";
    cin>>name;
    for(int i=0;i<strlen(name);i++)total+=name[i];
    do
    {
        srand(total);
        total=rand()%300;
    }while(!strcmp(name,cards[total].name) && time++<300 );
    if(!strcmp(name,cards[total].name))return total;
    else return -1;
}
void manage::hash(int total,card newcard)
{
    int p=total;
    do
    {
        srand(total);
        p=rand()%300;
    }while(cards[p].use);
    cards[p]=newcard;
    return ;
}
void manage::list()
{
    for(int i=0;i<300;i++)
    if(cards[i].use)
    {
        cout<<"name:"<<cards[i].name<<endl;
        cout<<"level:"<<cards[i].level<<endl;
        cout<<"integral:"<<cards[i].score<<"pts"<<endl;
    }
}