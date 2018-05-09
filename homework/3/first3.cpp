#include<iostream>
struct sport{
    int time;//以毫秒为单位
    int name[30];
}
void quicksort(sport* athlete,int l,int r);
int main()
{
    int n;
    cout<<"How much athlete";
    cin>>n;
    sport athlete[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Name:";
        cin>>athlete[i].name;
        cout<<"Time(ms):";
        cin>>athlete[i].time;
    }
    quicksort(athlete,0,n-1);
    cout<<"The best 3 athletes is ";
    for(int i=0;i<3;i++)cout<<athlete[i].name<<endl;
}
void quicksort(sport* athlete,int l,int r)//一个简单的快速排序，由大到小排列
{
    if(l<r)
    {
        int i=l,j=r;
        sport temp=athlete[l];
        while(i<j)
        {
            while(i<j && athlete[j].time>temp.time)j--;
            if(i<j)athlete[i++]=athlete[j];
            while(i<j && athlete[i].time<temp.time)i++;
            if(i<j)athlete[j--]=athlete[i];
        }
        athlete[i]=temp;
        quicksort(athlete,l,j-1);
        quicksort(athlete,i+1,r);
    }
}