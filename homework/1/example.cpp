#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    char num[1000],f;
    cout<<"Input a series number, please"<<endl;
    cin>>num;
    cout<<"What's num do you want to find"<<endl;
    cin>>f;
    int l=0;
    for(int i=0;i<strlen(num);i++)
    if(num[i]==f)l++;
    cout<<"Have Find"<<l<<endl;
}