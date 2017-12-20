#include<cstdio>
#include<cstdlib>
using namespace std;
typedef struct tree{
    int key;//关键字的值
    int bf;
    tree *lchild,*rchild;
}*AVLTree,BSTNode;
bool PrintBST_1(BSTNode *bt)
{
    if(bt==NULL)return false;
    vector<BSTnode> Record[N];
    BSTNode temp=bt;
    while(temp!=NULL || !Record.empy())
    {
        while(temp!=0)
        {
            if(Record.size()<N)Record.push_back(p);
            else return true;
            p=p->lchild;
        }
        if(Record.empty())return true;
        else 
        {
            p=Record.back();
            cout<<p->key<<" ";
            Record.pop_back();
            p=p->rchild;
        }
    }
}
void PrintBST_2(BSTNode *bt)
{
    if(bt!=NULL)
    {
        PrintBST_2(bt->lchild)//转向左子树
        cout<<bt->key<<" ";
        printBST_2(b2->rchild)//转向右子树
    }
}
BSTNode* SearchBST(BSTNode *bt,int k)
{
    BSTNode* p=bt;
    if(bt==NULL || k==bt->key)
    {
        if(bt==NULL)cout<<"Not Found ";
        return bt;
    }
    while(k!=p->key && p!=NULL)
    {
        if(k>p->key)p=p->rchild;
        else if(k<p->key)p=p->lchild;
    }
    if(p==NULL)cout<<"Not Found";
    else return p;
}
void CreateArray(int *Array,int n)
{
    Array=new int[n];
}
void InputArray(int * &Array,int n)
{
    int data;
    for(int i=0;i<n;i++)cin>>&Array[i];
}
void Swap(int *a,int *b)
{
    int *temp=a;
    a=b;
    b=temp;
}
BSTNode* R_Rotate(BSTNode *&p)
{
    BSTNode* temp=p->lchild;
    p->lchild=temp->rchild;
    temp->rchild=p;
    return temp;
}
BSTNode* L_Rotate(BSTNode *&p)
{
    BSTNode* temp=p->rchild;
    p->rchild=temp->lchild;
    temp->lchild=p;
    return temp;
}
BSTNode* LeftBalance(BSTNode *&p)
{
    BSTNode *lm=p->lchild;
    BSTNode *rd=lm->rchld;
    lm->rchild=rd->lchild;
    p->lchild=rd->rchild;
    rd->lchild=lm;
    rd->rchild=p;
    return rd;
}
BSTNode* RightBalance(BSTNode *&p)
{
    BSTNode *rm=p->rchild;
    BSTNode *ld=rm->lchild;
    rm->lchild=ld->rchild;
    p->rchild=ld->lchild;
    ld->lchild=p;
    ld->rchild=rm;
    return ld;
}
int InsertAVL(BSTNode *&T,int e)
{
    BSTNode *l=new BSTNode;
    BSTNode *p=T,*fp,*u,*fu,;
    BSTNode *temp=NULL;
    l->lchild=l->rchild=NULL;
    l->bf=0;
    l->key=e;
    if(T==NULL)T=l;
    else
    {
        u=T;fu=NULL;fp==NULL;
        while(p!=NULL)
        {
            if(p->bf!=EH)
            {
                u=p;
                fu=fp;
            }
            fp=p;
            if(e>p->key)p=p->rchild;
            else if(e<p->key)p=p->lchild;
            else 
            {
                delete l;
                return 0;
            }
        }
        if(e>fp->key)fp->rchild=l;
        else fp->lchild=l;
        if(e>u->key)
        {
            temp=p=u->rchild;
            u->bf-=1;
        }
        else 
        {
            temp=p=u->lchild;
            u->bf+=1;
        }
        while(p!=l)
        {
            if(e>p->key)
            {
                p->bf-=1;
                p=p->rchild;
            }
            else 
            {
                p->bf+=1;
                p=p->lchild;
            }
        }
        if(u->bf=2 && temp->bf==1)//LL型失衡，做右旋
        {
            u->bf=0;
            temp->bf=0;
            if(fu=NULL)T=R_Rotate(u);
            else if(u==fu->lchild)fu->lchild=R_Rotate(u);
            else fu->rchild=R_Rotate(u);

        }
        if()
    }
}