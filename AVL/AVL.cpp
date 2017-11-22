#include<cstdio>
#include<cstdlib>
using namespace std;
typedef struct tree{
    int data;
    int bf;
    tree *left,*right;
}AVLTree;
bool Insert(AVLtree *avl,int data)
{
    AVLTree *A,*B,*C,*FA;
    AVLTree *in,;
    AVLTree *temp=new AVLTree;
    temp->bf=0;
    temp->data=data;
    temp->left=temp->right=NULL;
    if(!avl)avl=temp;
    else 
    {
        p=avl;
        while(p!=NULL)
        {
            if(data > p->data)
            {
                if(p->right==NULL)p=p->right=temp;
                else p=p->right;
            }
            else if(data < p->data)
            {
                if(p->left==NULL)p=p->left=temp;
                else p=p->left;
            }
            else if 
            {
                delete(temp);
                return 0;
            }
        }
    }
}