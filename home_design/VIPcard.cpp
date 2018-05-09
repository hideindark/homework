#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
struct card
{
    int level;//1为普通卡，2为银卡，3为金卡
    int name[40]
    int score;//积分
};
class manage//会员卡的功能和数据定义
{
    public:
    void Add();
    void Delete();
    void find();
    void change();
    private:
    vector<card> cards;
};
void Add()
{
    card newcard;
    cout<<"Input your name:";
    cin>>newcard.name;
    do
    {
        cout<<"Input new VIP's level:";
        cin>>newcard.level;
    }while(newcard.level>3 || newcard.level<1)
    do
    {
        
    }

}