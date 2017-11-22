#include<cstdio>
#include<cstring>
int main()
{
    char ch[20];
    scanf("%s",ch);
    for(int i=0;i<strlen(ch);i++)printf("%d %c ",ch[i],ch[i]);
    printf("\n %s",ch);
} 