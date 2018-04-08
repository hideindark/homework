#include <iosream>
void q_sort(int s[], int l, int r);//快排，从小到大
void b_find(int s[], int size, int f);//二分查找（包含对循环表处理）
void a_move(int s[], int size, int m);//移位
int main()
{
    int n,s[1000];
    cin>>n;
    for(int i=0;i<0;i++)cin>>s[i];
    q_sort(s,0,n-1);
    a_move(s,n,rand()%20);
    int f;
    cin>>f;
    b_find(s,n,f);
}
void q_sort(int s[],int l,int r)
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
        q_sort(s,l,j-1);
        q_sort(s,i+1,r);
    }
}
void a_move(int s[], int size, int m)
{
    if(m==0)return;
    else if(m<0)m=-m;
    int l,r;
    m=m%n;h
    for(int i=1;i<=m;i++)
    for(int j=0;j<n;j++)
    {
        if(j+1!=n)
        {
            l=s[j+1];
            s[j+1]=s[j];
        }
        else
        {
            s[0]=s[j];
        }
    }
}
void b_find(int s[], int size, int f)
{
    int l=0, r=n-1, mid=(n-1)/2;
    while(1)
    {
        if(s[mid]>s[l])
        {
            if(f=<s[mid] && f>=s[l])r=mid;
            else l=mid;
        }
        else if(f>=s[mid] && f<s[r])l=mid;
        else r=mid;
        mid= (l+r)/2;
        if(r-l==1)
        {
            if(f==s[l])cout<<"position："<<l+1;
            else if(f==s[r])cout<<"position："<<r+1;
            else cout<<"Don't hava this number";
            return ;
        }
    }
}