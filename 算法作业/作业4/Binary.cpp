#include <iostream>
#include <ctime>
using namespace std;
void binary_s(int s[],int n)//二分查找;
void quick_s(int s[],int l,int r);//快排
void find_a(int s[],int n);//遍历
int main()
{
    int n,s[1000];
    cout<<"How much number want to add: ";
    cin>>n;
    for(int i=0;i<n;i++)cin>>s[i];
    quick_s(s,0,n-1);
    find_a(s,n);
    binary_s(s,n);
}
void quick_s(int s[],int l,int r)
{
    if(l<r)
    {
        int i=l;j=r;
        int temp=s[l];
        while(i<j)
        {
            while(i<j && s[j]>temp)j--;
            if(i<j)s[i++]=s[j];
            while(i<j && s[i]<temp)i++;
            if(i<j)s[j--]=s[i];
        }
        s[i]=temp;
        quick_s(s,l,j-1);
        quick_s(s,i+1,r);
    }
}
void binary_s(int s[],int n)
{
    int m=n/2,l=0,r=n-1,t=0;
    for(int i=0;i<n;i++)
    {
        t++;
        while(s[m]!=s[i])
        {
            t++;
            if(s[m]>s[i])r=m;
            else l=m;
            m=(l+r)/2;
        }
    }
    cout<<"avarage: "<<static_cast<double>(t)/static_cast<double>(n);
}
void fina_a(int s[],int n);
{
    int t=0;
    for(int i=0;i<n;i++)
    {
        t++;
        for(int j=0;s[i]!=s[j];j++)t++;
    }
    cout<<"avarage: "<<static_cast<double>(t)/static_cast<double>(n);
}
