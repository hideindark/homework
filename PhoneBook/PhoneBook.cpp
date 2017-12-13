#include<iostream>
#include<cstdio>
#include<cstring>
#include<math.h>
using namespace std;
struct Phone{
    unsigned char Number[80];
    unsigned char name[80];
    bool crash;//用于判断是否已存在记录
    Phone()
    {
        crash=false;
    }
}
int Start();
void Insert(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
void Delete(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
void Change(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
int Search(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num,int mode);
int main()
{
    Phone Phonebook_name[100],Phonebook_num[100];
    int n_name,n_num;
    n_name=n_num=0;
    int s_mode;
    while(int mode=Start()!=6)
    {
        switch(mode)
        {
            case 1:Insert(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
            case 2:Delete(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
            case 3:
                cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
                do
                {
                    cin>>s_mode
                }
                while(s_mode<1 && s_mode2>2)
                Search(Phonebook_name,Phonebook_num,&n_name,&n_num,s_mode);break;
            case 4:Change(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
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
void Insert(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num)
{
    if(*n_num==100||*n_name==100)
    {
        cout<<"You Only can have 100 records, if you want record more, please delete some"<<endl;
        return 0;
    }
    unsigned char ch[20];
    Phone NewPhone;
    int name,num;
    Printf("Please input the Phone number:");
    while(1)
    {
        bool error=FALSE;
        cin.get(ch,80);
        if(strlen(ch)!=0)
        {
            int length=strlen(ch);
            for(int i=0;i<length;i++)
            {
                if(ch[i]<48||ch[i]>57)
                {
                    puts("Please input a series number, not other things");
                    error=true;
                    break;
                }
            }
            if(error)continue;
        }
    }
    strcpy(NewPhone.Number,ch);
    Printf("Please input a name")
    cin.get(ch,80);
    strcpy(NewPhone.name,ch);
    NewPhone.crash=true;
    int blank=0;
    //以姓名进行哈希插入
    for(int i=0;i<strlen(ch);i++)
    {
        blank+=ch[i];
    }
    do
    {
        srand(blank);
        name=rand()%100;
    }
    while(Phonebook_name[name].crash==true)
    Phonebook_name[name]=NewPhone;
    *n_name++;
    //以号码进行哈希插入
    blank=0;
    for(int i=0;i<strlen(NewPhone.Number);i++)
    {
        blank+=ch[i];
    }
    do
    {
        srand(blank);
        num=rand()%100;
    }
    while(Phonebook_name[num].crash==true)
    Phonebook_num[num]=NewPhone;
    *sn_num++;
    
}
int Search(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num,int mode)
{
    puts("How do you want to search");
    puts("1.Phone number");
    puts("2.name");
    unsigned char ch[80];
    int mode,t=0,blank=0,p;
    if(cin>>mode)
    {
        if(mode!=1 || mode!=2 )puts("Please input a useful number");
    }
    else puts("Please input 1 or 2");
    if(mode==1)//以号码查询
    {

        cout<<"Please input the Phone number"<<endl;
        cin>>ch;
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_num;t++)
        {
            p=rand()%100;
            if(Phonebook_num[p].crash==false)continue;
            else if(!strcmp(ch,Phonebook_num[p].Number))
            {
                cout<<"Name:"<<Phonebook_num[p].Number<<endl<<"Number:"<<Phonebook_num[p].name<<endl;
                return p;
            }
            
        }
        cout<<"Not Find"<<endl;
        return -1;
    }
    if(mode==2)
    {
        cout<<"Please input the name"<<endl;
        cin>>ch;
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_name;t++)
        {
            p=rand()%100;
            if(Phonebook_name[p].crash==false)continue;
            else if(!strcmp(ch,Phonebook_name[p].Number))
            {
                cout<<"Name:"<<Phonebook_name[p].Number<<endl<<"Number:"<<Phonebook_name[p].name<<endl;
                return p;
            }
            
        }
        cout<<"Not Find"<<endl;
        return -1;
    }
}
void Delete(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num)
{
    cout<<"First search what you want to delete"<<endl;
    int p_num=Search(Phonebook_name,Phonebook_num,n_name,n_num);
    if(p==-1)return ;
    

}
