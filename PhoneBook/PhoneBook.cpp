#include<iostream>
#include<cstdio>
#include<cstring>
#include<math.h>
using namespace std;
struct Phone{
    char Number[20];
    char name[50];
    int hash_name,hash_num;
    Phone *next;
}
int Start();
void Insert(Phone *PhoneBook);
void Delete(Phone *PhoneBook);
void Change(Phone *PhoneBook);
int main()
{
    Phone *PhoneBook=NULL;
    while(int mode=Start()!=6)
    {
        switch(mode)
        {
            case 1:Insert(PhoneBook);break;
            case 2:Delete(PhoneBook);break;
            case 3:Search(PhoneBook);break;
            case 4:Change(PhoneBook);break;
        }
    }
    
}
int Start()
{
    puts("What You want to do?");
    puts("1.Add a new phone number");
    puts("2.Delte a number");
    puts("3.Find a Phone number information");
    puts("4.Change a phone imformation");
    puts("Choose one and input a number");
    int d;
    while(1)
    {
        if(scanf("%d",&d)==1)
        {
            if(d < 1 || d>4 )
            {
                Tryagain: puts("Please input a integer type number");
                continue;
            }
            else return d;
        }
        else goto Tryagain;
    }

}
void Insert(Phont *PhoneBook)
{
    char ch[20];
    Phone *NewPhone=new Phone;
    Phont *temp;
    Printf("Please input the Phone number:");
    while(1)
    {
        bool error=FALSE;
        if(scanf("%s",&ch)!=0)
        {
            int length=strlen(ch);
            for(int i=0;i<length;i++)
            {
                if(ch[i]<48||ch[i]>57)
                {
                    puts("Please input a number, not other things");
                    error=true;
                    break;
                }
            }
            if(error)continue;
        }
        else puts("Please input a series number");
    }
    strcat(NewPhone->Number,ch);
    for(int i=0;i<=4;i++)
    {
        NewPhone->hash_num+=(ch[strlen(ch)-1-i]-48)*(int)pow(10,i);
    }
    for(int i=0;i<=3;i++)
    {
        NewPhone->hash_num+=(ch[i]-48)*(int)pow(10,i+5);
    }
    Printf("Please input a name,only can use English")
    cin.get(ch,50);
    strcat(NewPhone->name,ch);
    int blank=0;
    for(int i=0;i<strlen(ch)-1;i++)
    {
        if(ch[i]==' ')blank++;
    }//姓名哈希值未完成
    PhoneBook->next=NULL;
    for(temp=PhoneBook;temp!=NULL;temp=temp->next);
    temp=NewPhone;
}
void Search()
{
    puts("How do you want to search");
    puts("1.Phone number");
    puts("2.name");
    int mode;
    if(scan("%d",&mode)==1)
    {
        if(mode!=1 || mode!=2 )puts("Please input a useful number");
    }
    else puts("Please input 1 or 2");
    if(mode==1)
    {

    }
}