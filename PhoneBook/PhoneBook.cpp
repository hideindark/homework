#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<math.h>
using namespace std;
struct Phone{
    char Number[80];
    char name[80];
    bool crash;//用于判断是否已存在记录
    Phone()
    {
        crash=false;
    }
};
int Start(int *mode);
void Insert(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
void Delete(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
void Change(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num);
int Search(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num,int mode);
int main()
{
    Phone Phonebook_name[100],Phonebook_num[100];
    int n_name,n_num;
    n_name=n_num=0;
    int s_mode,mode;
    while(Start(&mode)!=6)
    {
        switch(mode)
        {
            case 1:Insert(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
            case 2:Delete(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
            case 3:
                cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
                do
                {
                    cin>>s_mode;
                    getchar();
                }
                while(s_mode<1 && s_mode>2);
                Search(Phonebook_name,Phonebook_num,&n_name,&n_num,s_mode);break;
            case 4:Change(Phonebook_name,Phonebook_num,&n_name,&n_num);break;
        }
    }
    
}
int Start(int *mode)
{
    puts("What You want to do?");
    puts("1.Add a new phone number");
    puts("2.Delte a number");
    puts("3.Find a Phone number information");
    puts("4.Change a phone imformation");
    puts("Choose one and input a number");
    while(1)
    {
        if(scanf("%d",mode)==1)
        {
            if(*mode < 1 || *mode>4 )
            {
                puts("Please input a integer type number");
                continue;
            }
            else return *mode;
        }
        else continue;
    }

}
void Insert(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num)
{
    if(*n_num==100||*n_name==100)
    {
        cout<<"You Only can have 100 records, if you want record more, please delete some"<<endl;
        return ;
    }
    char ch[20];
    Phone NewPhone;
    int name,num;
    printf("Please input the Phone number:");
    while(1)
    {
        bool error=false;
        cin>>ch;
        getchar();
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
            else break;
        }
    }
    strcpy(NewPhone.Number,ch);
    printf("Please input a name:");
    cin.get(ch,80);
    getchar();
    strcpy(NewPhone.name,ch);
    NewPhone.crash=true;
    int blank=0;
    //以姓名进行哈希插入
    for(int i=0;i<strlen(ch);i++)
    {
        blank+=ch[i];
    }
    srand(blank);
    do
    {
        name=rand()%100;
    }
    while(Phonebook_name[name].crash==true);
    strcpy(Phonebook_name[name].name,NewPhone.name);
    strcpy(Phonebook_name[name].Number,NewPhone.Number);
    Phonebook_name[name].crash=true;
    *n_name+=1;;
    //以号码进行哈希插入
    blank=0;
    for(int i=0;i<strlen(NewPhone.Number);i++)
    {
        blank+=ch[i];
    }
    srand(blank);
    do
    {
        num=rand()%100;
    }
    while(Phonebook_name[num].crash==true);
    strcpy(Phonebook_num[num].name,NewPhone.name);
    strcpy(Phonebook_num[num].Number,NewPhone.Number);
    Phonebook_num[num].crash=true;
    *n_num+=1;
    
}
int Search(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num,int mode)
{
    char ch[80];
    int t=0,blank=0,p;
    if(mode==1)//以号码查询
    {

        cout<<"Please input the Phone number"<<endl;
        while(1)
        {
            bool error=false;
            cin.get(ch,80);
            getchar();
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
                else break;
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
        getchar();
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
    char ch[80];
    cout<<"First search what you want to delete"<<endl;
    cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
    do
    {
        cin>>s_mode;
        getchar();
    }
    while(s_mode<1 && s_mode>2);
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
            if(!Phonebook_name[p2].crash)
            {
                t--;
                continue;
            }
            else if(!strcmp(ch,Phonebook_name[p2].name))break;
        }
        Phonebook_name[p2].crash==false;
        Phonebook_num[p1].crash==false;
        *n_num-=1;*n_name-=1;
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
        *n_num-=1;*n_name-=1;
        cout<<"Delete Success"<<endl;
    }
}
void Change(Phone Phonebook_name[100],Phone Phonebook_num[100],int* n_name,int* n_num)
{
    int s_mode,blank=0,t=0,p;
    int mode;
    int p1,p2;
    char ch[80];
    cout<<"First search what you want to Change"<<endl;
    cout<<"Chose a search mode"<<endl<<"1.Phone number"<<endl<<"2.name"<<endl;
    do
    {
        cin>>s_mode;
        getchar();
    }
    while(s_mode<1 && s_mode>2);
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
            if(!Phonebook_name[p2].crash)
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
            cin>>mode;
            getchar();
        }
        while(mode<1 && mode>3);
        switch(mode)
        {
            case 3:
            case 2:
                cout<<"Please input new name"<<endl;
                memset(ch,'\0',sizeof(ch));
                cin>>ch;
                getchar();
                strcpy(New.name,ch);
                strcpy(Phonebook_num[p1].name,New.name);
                Phonebook_name[p2].crash=false;
                blank=0;
                for(int i=0;i<strlen(New.name);i++)
                {
                    blank+=New.name[i];
                }
                srand(blank);
                do
                {
                    p=rand()%100;
                }
                while(Phonebook_name[p].crash==true);
                Phonebook_name[p].crash=true;
                strcpy(Phonebook_name[p].name,New.name);
                strcpy(Phonebook_name[p].Number,New.Number);
                if(mode==2)break;
            case 1:
                cout<<"Please input new Phong number"<<endl;
                memset(ch,'\0',sizeof(ch));
                while(1)
                {
                    bool error=false;
                    cin.get(ch,80);
                    getchar();
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
                        else break;
                    }
                }
                strcpy(New.Number,ch);
                Phonebook_num[p1].crash=false;
                blank=0;
                for(int i=0;i<strlen(New.Number);i++)
                {
                    blank+=New.Number[i];
                }
                srand(blank);
                do
                {
                    p=rand()%100;
                }
                while(Phonebook_num[p].crash==true);
                Phonebook_num[p].crash=true;
                strcpy(Phonebook_num[p].name,New.name);
                strcpy(Phonebook_num[p].Number,New.Number);
                strcpy(Phonebook_name[p2].Number,New.Number);
                break;
        }
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
            cin>>mode;
            getchar();
        }
        while(mode<1 && mode>3);
        switch(mode)
        {
            case 3:
            case 2:
                cout<<"Please input new name"<<endl;
                memset(ch,'\0',sizeof(ch));
                cin>>ch;
                getchar();
                strcpy(New.name,ch);
                strcpy(Phonebook_num[p2].name,New.name);
                Phonebook_name[p1].crash=false;
                blank=0;
                for(int i=0;i<strlen(New.name);i++)
                {
                    blank+=New.name[i];
                }
                srand(blank);
                do
                {
                    p=rand()%100;
                }
                while(Phonebook_name[p].crash==true);
                Phonebook_name[p].crash=true;
                strcpy(Phonebook_name[p].name,New.name);
                strcpy(Phonebook_name[p].Number,New.Number);
                if(mode==2)break;
            case 1:
                cout<<"Please input new Phong number"<<endl;
                char ch[80];
                while(1)
                {
                    bool error=false;
                    cin.get(ch,80);
                    getchar();
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
                        else break;
                    }
                }
                strcpy(New.Number,ch);
                Phonebook_num[p2].crash=false;
                blank=0;
                for(int i=0;i<strlen(New.Number);i++)
                {
                    blank+=New.Number[i];
                }
                srand(blank);
                do
                {
                    p=rand()%100;
                }
                while(Phonebook_num[p].crash==true);
                Phonebook_num[p].crash=true;
                strcpy(Phonebook_num[p].name,New.name);
                strcpy(Phonebook_num[p].Number,New.Number);
                strcpy(Phonebook_name[p1].Number,New.Number);
                break;
        }
    }
    
}