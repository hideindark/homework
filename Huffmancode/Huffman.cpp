#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<functional>
//目前这个还有bug，修不修就看心情了orz
using namespace std;
struct code
{
    unsigned char data;
    int time;
    vector<int> hufcode;
};
struct huf
{
    int data;
    int time;
    bool j;
    struct huf *lchild,*rchild,*f;
    huf()
    {
        lchild=rchild=f=NULL;
        j=false;
    }
};
struct cmp1
{
    bool operator () (const huf *a,const huf *b)
    {
        if(a->time != b->time)
        return a->time > b->time;
        else return a->data > b->data;
    }
};
struct cmp2
{
    bool operator () (const code a,const code b)
    {
        if(a.time != b.time)
        return a.time > b.time;
        else return a.data > b.data;
    }
};
bool FileRead(char* filename,vector<code> &s);
huf* HuffmanTree(vector<code> &s,huf* top);
void FileWrite(char* filename,vector<code> &s);
void encodefile(char* filename,vector<code> &s);
void decodefile(char* filename,vector<code> &s);
huf* Find(unsigned char key,huf* top);
int main()
{
    vector<code> s;
    int mode;
    char filename[100];
    while(1)
    {
        cout<<"1.enccode file"<<endl<<"2.decode file"<<endl<<"3.quit"<<endl;
        cin>>mode;
        getchar();
        switch(mode)
        {
            case 1:
            {
                cout<<"filename: ";
                cin>>filename;
                getchar();
                if(!FileRead(filename,s))
                {
                    cout<<"Please input right filename"<<endl;
                    break;
                }
                huf* top=new huf;
                HuffmanTree(s,top);
                encodefile(filename,s);
                s.clear();
                break;
            }
            case 2:
            {
                cout<<"filename: ";
                cin>>filename;
                getchar();
                decodefile(filename,s);break;
            }
            case 3: 
            {
                return 0;
                break;
            }
            default: cout<<"Please input 1 or 2 or 3";
        }
    }
}
bool FileRead(char* filename,vector<code> &s)
{
    FILE *fp;
    unsigned char ch=0;
    fp=fopen(filename,"rb+");
    if(fp==NULL)return false;
    while(!feof(fp))
    {
        ch=fgetc(fp);
        bool con=false;
        for(int i=0;i<s.size();i++)
        {
            if(s[i].data==ch)
            {
                s[i].time++;
                con=true;
                break;
            }
        }
        if(con)continue;
        code temp;
        temp.data=ch;
        temp.time=1;
        s.push_back(temp);
    }
    fclose(fp);
    return true;
}
huf* HuffmanTree(vector<code> &s,huf* top)//建立huffman树并产生相应编码
{
    //创建huffman树
    huf *t1,*t2,*temp;
    priority_queue<huf*, vector<huf*>, cmp1> r;
    for(int i=0;i<s.size();i++)
    {
        temp=new huf;
        temp->time=s[i].time;
        temp->data=s[i].data;
        temp->j=true;
        r.push(temp);
    }
    temp=new huf;
    while(1)
    {
        t1=r.top();
        r.pop();
        t2=r.top();
        r.pop();
        temp->lchild=t1;
        temp->rchild=t2;
        t1->f=temp;
        t2->f=temp;
        temp->time=t1->time + t2->time;
        if(r.empty())break;
        r.push(temp);
        temp=new huf;
    }
    top=temp;
    //从huffman树中产生相应编码
    stack<int> l;
    for(int i=0;i<s.size();i++)
    {
        bool find1=false;
        temp=Find(s[i].data,top);
        while(temp!=top)
        {
            if(temp==temp->f->lchild)l.push(0);
            else l.push(1);
            temp=temp->f;
        }
        while(!l.empty())
        {
            s[i].hufcode.push_back(l.top());
            l.pop();
        }
    }
    return top;
}
huf* Find(unsigned char key,huf* top)
{
    stack<huf*> s;
    huf *temp=top;
    int time=0;
    while(!s.empty() || temp!=NULL)
    {
       while(temp!=NULL)
       {
           if(temp->data==key)return temp;
           s.push(temp);
           temp=temp->lchild;
       }
       if(!s.empty())
       {
           temp=s.top();
           s.pop();
           if(temp->data==key)return temp;
           temp=temp->rchild;
       }
    }
}
void encodefile(char* filename,vector<code> &s)
{
    char ch[100];
    unsigned char te,wr=0,temp;
    int length=0,left=0,over=0,size;
    int i,j,k;
    sprintf(ch,"%s.out",filename);
    FILE *rf,*wf;
    wf=fopen(ch,"wb+");
    rf=fopen(filename,"rb+");
    //先往文件内写入编码信息
    temp=s.size();
    fputc(temp,wf);
    for(int i=0;i<s.size();i++)
    {
        fwrite(&s[i].data,sizeof(unsigned char),1,wf);
        fwrite(&s[i].time,sizeof(int),1,wf);
    }
    //对文件进行编码
    while(!feof(rf))
    {
        temp=fgetc(rf);
        for(int i=0;i<s.size();i++)
        {
            if(temp==s[i].data)
            {
                size=s[i].hufcode.size();
                for(int j=0;j<size;j++)
                {
                    if(length!=8)
                    {
                        if(s[i].hufcode[j]==0)wr*=2;
                        else wr=wr*2+1;
                        length++;
                    }
                    else 
                    {
                        fputc(wr,wf);
                        length=0;
                        wr=0;
                    }
                }
            }
        }
    }
    if(length!=0)fputc(wr<<8-length,wf);
    fclose(rf);
    fclose(wf);
}
void decodefile(char* filename,vector<code> &s)
{
    FILE *rfile,*wfile;
    code temp;
    char ch[100];
    unsigned char p;
    sprintf(ch,"%s.out",filename);
    rfile=fopen(filename,"rb");
    wfile=fopen(ch,"wb");
    int num=fgetc(rfile);
    for(int i=0;i<num;i++)
    {
        fread(&temp.data,sizeof(unsigned char),1,rfile);
        fread(&temp.time,sizeof(int),1,rfile);
        s.push_back(temp);
    }
    huf* top=new huf;
    top=HuffmanTree(s,top);
    huf* mem=top;
    while(!feof(rfile))
    {
        unsigned char ch=fgetc(rfile);
        for(int i=7;i>=0;i--)
        {
            p=ch<<7-i;
            p=p>>7;
            if(p==0)
            mem=mem->lchild;
            else if(p==1)
            mem=mem->rchild;
            if(mem->j==true)
            {
                fputc(mem->data,wfile);
                mem=top;
            }
        }
    }
    fclose(rfile);
    fclose(wfile);
}