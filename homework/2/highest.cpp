#include<iostream>
using namespace std;
struct stu
{
    char name[30];
    int score;
};
int main()
{
    stu student[10];
    int highest=0;
    int p;
    for(int i=0;i<10;i++)
    {
        cout<<"Input name:";
        cin>>student[i].name;
        cout<<"Input score:";
        cin>>student[i].score;
        if(student[i].score>highest)p=i;
    }
    cout<<student[p].name<<"has highest score:"<<student[p].score<<endl;
}