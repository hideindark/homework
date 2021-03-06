#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
void q_sort(int s[], int l, int r);//快排，从小到大
void b_find(int s[], int size, int f);//二分查找（包含对循环表处理）
void a_move(int s[],int size);//数组右移一位
int main()
{
    int n,s[1000];
    cin>>n;
    for(int i=0;i<n;i++)cin>>s[i];
    q_sort(s,0,n-1);
    srand(rand());
    int t=rand()%n;
    for(int i=0;i<t;i++)a_move(s,n);
    for(int i=0;i<n;i++)cout<<s[i]<<" ";
    cout<<endl;
    int f;
    cin>>f;
    b_find(s,n,f);
}
void q_sort(int s[],int l,int r)
{
    if(l<r)
    {
        int i=l,j=r;
        int temp=s[l];
        while(i<j)
        {
            while(i<j && s[j]>temp)j--;
            if(i<j)s[i++]=s[j];
            while(i<j && s[i]<temp)i++;
            if(i<j)s[j--]=s[i];
        }
        s[i]=temp;
        q_sort(s,l,j-1);
        q_sort(s,i+1,r);
    }
}
void a_move(int s[],int size)
{
    int temp;
    int i;
    temp = s[size-1];
    for (i = size-1; i > 0; i--)
    {
        s[i] = s[i-1];
    }
    s[i] = temp;
    
}
void b_find(int s[], int size, int f)
{
    int l=0, r=size-1, mid=(l+r)/2;
    while(l<=r)
    {
        if(s[mid]==f)
        {
            cout<<"Position:"<<mid+1<<endl;
            return ;
        }
        if(s[mid]>s[l])
        {
            if(f<s[mid] && f>=s[l])r=mid-1;
            else l=mid+1;
        }
        else if(f>=s[mid] && f<s[r])l=mid+1;else r=mid-1;
        mid=l+(r-l)/2;
    }
}