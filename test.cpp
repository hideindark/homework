#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;
int main(){
    int n;
    while(scanf("%d",&n)!=0)
    {
        srand(n);
        cout<<rand()<<endl<<rand()<<endl;
    }
}
