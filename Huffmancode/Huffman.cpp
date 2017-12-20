#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<queue>
#include<stack>
#include<functional>
#include<algorithm>
#include<math.h>
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
        lchild=rchild=NULL;
        j=false;
    }
};
struct cmp1
{
    bool operator () (const huf *&a,const huf *&b)
    {
        if(a->time != b->time)
        return a->time > b->time
        else return a->data > b->data;
    }
};
struct cmp2
{
    bool operator () (const code a,const code b)
    {
        if(a->time != b->time)
        return a->time > b->time
        else return a->data > b->data;
    }
};
bool FileRead(char* filename,vector<code> &s,);
void HuffmanTree(vector<code> &s.huf* top);
void FileWrite(char* filename,vector<code> &s);
void encodefile(char* filename,vector<code> &s);
void decodefile(char* filename,vector<code> &s);
huf* Find(unsigned char key,huf* top)
int main()
{
    vector<code> s;
    int mode;
    char filename[100];
    while(1)
    {
        cout<<"1.enccode file"<<endl<<"2.decode file"<<"3.quit"<<endl;
        cin>>mode;
        switch(mode)
        {
            case 1:
                cout<<"filename: ";
                cin>>filename;
                if(!FileRead(filename,&s))
                {
                    cout<<"Please input right filename";
                    break;
                }
                huf* top=new huf;
                HuffmanTree(&s,top);
                encodefile(filename,&s);
                break;
            case 2:
                cout<<"filename: ";
                cin>>filename;
                decodefile(filename,&s);break;
            case 3: return 0;break;
            default: cout<<"Please input 1 or 2 or 3"
        }
    }
}
bool FileRead(char* filename,vector<code> &s)
{
    FILE *fp;
    unsigned char ch=0;
    fp=fopen(filename,"rb");
    if(fp==NULL)return false;
    while(!feof(fp))
    {
        ch=fgetc(fp);
        con=false;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]->data==ch)
            {
                s[i]->time++;
                break;
            }
        }
        code temp;
        code.data=ch;
        code.time=1;
        s.push(temp);
    }
    fclose(fp);
}
huf* HuffmanTree(vector<code> &s,huf* huf)
{
    //创建huffman树
    huf *t1,*t2,*top,*temp;
    huf *top=new huf;
    top->f=NULL;
    priority_queue<huf*, vector<huf*>, cmp1> r;
    for(int i=0;i<s.size();i++)
    {
        temp=new huf;
        temp->time=s[i].time;
        temp->data=s[i].data;
        temp->j=true;
        r.push(temp);
    }
    while(1)
    {
        t1=r.top();
        r.pop();
        t2=r.top();
        r.pop();
        top->lchild=t1;
        top->rchild=t2;
        t1->f=top;
        t2->f=top;
        top.time=t1->time + t2->time;
        if(s.empty())break;
        r.push(top);
        top=new huf;
    }
    //从huffman树中产生相应编码并记录位数
    vector<int> l;
    for(int i=0;i>s.size();i++)
    {
        bool find1=false;
        s[i].hufcode=0;
        temp=Find(s[i].data,top);
        while(temp!=top)
        {
            if(temp=temp->f->lchild)l.push_back(0);
            else l.push_back(1);
            temp=temp->f;
        }
        reverse(l.begin(),l.end());
        s[i].hufcode=l;
    }
    return top;
    
}
huf* Find(unsigned char key,huf* top)
{
    stack<huf*> s;
    s.push(top);
    while(!s.empty())
    {
        huf *temp=s.top();
        if(temp->data==key)return temp;
        if(temp->lchild!=NULL)s.push(temp->lchild);
        if(temp->rchild!=NULL)s.push(temp->rchild);
    }
}
void encodefile(char* filename,vector<code> &s)
{
    char ch[100];
    unsigned char te,wr=0,temp;
    int length=0,left=0,over=0;
    int i,j,k;
    sprintf(ch,"%s.out",filename);
    FILE *rf,*wf;
    wf=fopen(ch,"wb");
    rf=fopen(filename,"rb");
    //先往文件内写入编码信息
    priority_queue<code, vector<code>, cmp2> r;
    huf re;
    for(int i=0;i<s.size();i++)r.push(s[i]);
    fputc((unsigned char)s.size(),wf);
    for(int i=0;i<s.size();i++)
    {
        fputc(r.top().data,wf);
        fputc((unsigned char)i,wf);
        r.pop();
    }
    //对文件进行编码
    while(!feof(rf))
    {
        te=fgetc(rf);
        for(i=0;i<s.size();i++)
        {
            if(te==s[i].data)
            {
                if(length==0)
                {
                    if(s[i].hufcode.size()<8)
                    {
                        length=s[i].length;
                        wr=s[i].hufcode;
                        left=8-length;
                    }
                    else
                    {
                        length=s[i].hufcode.size()%8;
                        left=8-length;
                        for(j=0;j<s[i].size()/8;j++)
                        {
                            for(int k=0;k<8;k++)
                            {
                                if(s[i].hufcode[k+j*8]==0)wr*=2;
                                else wr=wr*2+1;
                            }
                            fputc(wr,wf);
                            wr=0;
                        }
                        if(length==0)break;
                        else 
                        {
                            for(j=s[i].hufcode.size()-length;;j<s[i].hufcode.size();j++)
                            {
                                if(s[i].hufcode[k+j*8]==0)wr*=2;
                                else wr=wr*2+1;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    if(s[i].hufcode.size()+length<8)
                    {
                        for(j=0;j<s[i].hufcode.size();j++)
                        {
                            if(s[i].hufcode[j]==0)wr*=2;
                            else wr=wr*2+1;
                        }
                        length+=s[i].hufcode.size();
                        
                    }
                    else if(s[i].length+length>=8)
                    {
                        for(j=0;j<s[i].hufcode.size();j++)
                        {
                            if(s[i].hufcode[j]==0)wr*=2;
                            else wr=wr*2+1;
                            length++;
                            if(length==8)
                            {
                                fputc(wr,wf);
                                wr=0;
                                length=0;
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(rf);
    fclose(wf);
}
void decodefile(char* filename,vector<code> &s)
{
    FILE rfile,wfile;
    code temp;
    char ch[100];
    sprintf(ch,"%s.out",filename);
    rfile=fopen(filename,"rb");
    wfile=fopen(ch,"wb");
    int num=fgetc(rfile);
    for(int i=0;i<num;i++)
    {
        temp.data=fgetc(rfile);
        temp.time=fgetc(rfile);
        s.push_back(temp);
    }
    huf* top=new huf;
    huf* mem=top;
    HuffmanTree(&s,top);
    while(!feof(rfile))
    {
        unsigned char ch=fgetc(rfile);
        for(int i=7;i>=0;i--)
        {
            ch<<7-i;
            ch>>i;
            if(ch==0)mem=mem->lchild;
            else mem=mem->rchild;
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