#include<cstdio>
#include<cstdlib>
int main(){
    int x,n;
    while(scanf("%d",&n)!=0)
    {
        x=0;
        for(int i=0;i<n;i++)   
        for(int j=0;j<i;j+=2)
        for(int k=0;k<j;k+=2)x+=1;
        printf("%d\n",x);
    }
}
