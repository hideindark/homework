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
    unsigned char ch[80];
    int mode,t=0,blank=0,p;
    if(mode==1)//以号码查询
    {

        cout<<"Please input the Phone number"<<endl;
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
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_num;t++)
        {
            p=rand()%100;
            if(Phonebook_num[p].crash==false)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_num[p].Number))
            {
                cout<<"Name:"<<Phonebook_num[p].Number<<endl<<"Number:"<<Phonebook_num[p].name<<endl;
                return p;
            }
            
        }
        cout<<"Not Find"<<endl;
        return -1;
    }
    if(mode==2)//以姓名查询
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
            if(Phonebook_name[p].crash==false)
            {
                t--;
                continue;
            }
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
    int s_mode,blank=0,t=0;
    int p1,p2;
    unsigned char ch[80];
    cout<<"First search what you want to delete"<<endl;
    cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
    do
    {
        cin>>s_mode
    }
    while(s_mode<1 && s_mode2>2)
    p1=Search(Phonebook_name,Phonebook_num,n_name,n_num,s_mode);
    if(p1==-1)//寻找失败，导致删除失败
    {
        cout<<"Delete failed"<<endl;
        return ;
    }
    if(s_mode==1)
    {
        strcpy(ch,Phonebook_num[p1].name);
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_name;t++)
        {
            p2=rand()%100;
            if(!Phonebook_name[p].crash)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_name[p2].name))break;
        }
        Phonebook_name[p2].crash==false;
        Phonebook_num[p1].crash==false;
        *n_num--;*n_name--;
        cout<<"Delete Success"<<endl;
    }
    else if(s_mode==2)//以名字搜索后，再以数字搜索其在数字表中的位置
    {
        strcpy(ch,Phonebook_name[p1].Number);
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_num;t++)
        {
            p2=rand()%100;
            if(!Phonebook_num[p2].crash)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_num[p2].Number))break;
        }
        Phonebook_name[p1].crash==false;
        Phonebook_num[p2].crash==false;
        *n_num--;*n_name--;
        cout<<"Delete Success"<<endl;
    }
}
void Change(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num)
{
    int s_mode,blank=0,t=0;
    int mode;
    int p1,p2;
    unsigned char ch[80];
    cout<<"First search what you want to Change"<<endl;
    cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
    do
    {
        cin>>s_mode
    }
    while(s_mode<1 && s_mode2>2)
    p1=Search(Phonebook_name,Phonebook_num,n_name,n_num,s_mode);
    if(p1==-1)//寻找失败，导致无法继续进行更改
    {
        cout<<"Change failed"<<endl;
        return ;
    }
    Phone New;
    if(s_mode==1)//以号码搜索后，再以名字搜索其在姓名表的位置
    {
        strcpy(ch,Phonebook_num[p1].name);
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_name;t++)
        {
            p2=rand()%100;
            if(!Phonebook_name[p].crash)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_name[p2].name))break;
        }
        strcpy(New.name,Phonebook_num[p1].name);
        strcpy(New.Number,Phonebook_num[p1].Number);
        cout<<"What's you want to change"<<endl<<"1.Phone Number"<<endl<<"2.name"<<endl<<"3.Phongnumber and name"<<endl;
        do
        {
            cin>>mode
        }
        while(mode<1 && mode2>3)
        switch(mode)
        {
            case 3:
            case 2:
                cout<<"Please input new name"<<endl;
                unsigned char ch[80];
                cin>>ch;
                strcpy(New.name,ch);
                if(mode==2)break;
            case 1:
                cout<<"Please input new Phong number"<<endl;
                unsigned char ch[80];
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
                strcpy(New.Number,ch);break;
        }
        Phonebook_name[p2]=New;
        Phonebook_num[p1]=New;
    }
    else if(s_mode==2)//以名字搜索后，再以数字搜索其在数字表中的位置
    {
        strcpy(ch,Phonebook_name[p1].Number);
        for(int i=0;i<strlen(ch);i++)
        {
            blank+=ch[i];
        }
        srand(blank);
        for(;t<*n_num;t++)
        {
            p2=rand()%100;
            if(!Phonebook_num[p2].crash)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_num[p2].Number))break;
        }
        strcpy(New.name,Phonebook_name[p1].name);
        strcpy(New.Number,Phonebook_name[p1].Number);
        cout<<"What's you want to change"<<endl<<"1.Phone Number"<<endl<<"2.name"<<endl<<"3.Phongnumber and name"<<endl;
        do
        {
            cin>>mode
        }
        while(mode<1 && mode2>3)
        switch(mode)
        {
            case 3:
            case 2:
                cout<<"Please input new name"<<endl;
                unsigned char ch[80];
                cin>>ch;
                strcpy(New.name,ch);
                if(mode==2)break;
            case 1:
                cout<<"Please input new Phong number"<<endl;
                unsigned char ch[80];
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
                strcpy(New.Number,ch);break;
        }
        Phonebook_num[p2]=New;
        Phonebook_name[p1]=New;
    }
    
}