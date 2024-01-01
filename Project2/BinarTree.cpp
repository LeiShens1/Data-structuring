//
// Created by 雷智宇 on 2023/11/11.
//
#include "BinarTree.h"

void CreateBTree(BTNode*& b, char* str)	            //创建二叉树
{
    BTNode* St[MaxSize], * p = NULL;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;				                        //建立的二叉树初始时为空
    ch = str[j];
    while (ch != '\0')  	                        //str未扫描完时循环
    {
        switch (ch)
        {
        case '(':top++; St[top] = p; k = 1; break;	//为左孩子节点
        case ')':top--; break;
        case ',':k = 2; break;                      //为孩子节点右节点
        default:p = (BTNode*)malloc(sizeof(BTNode));
            p->data = ch; p->lchild = p->rchild = NULL;
            if (b == NULL)                    	 	//*p为二叉树的根节点
                b = p;
            else  							       	//已建立二叉树根节点
            {
                switch (k)
                {
                case 1:St[top]->lchild = p; break;
                case 2:St[top]->rchild = p; break;
                }
            }
        }
        j++;
        ch = str[j];
    }
}

void DispBTree(BTNode* b)
{
    if (b != NULL)
    {
        cout << b->data;
        if (b->lchild != NULL || b->rchild != NULL)
        {
            cout << "(";						//有孩子节点时才输出(
            DispBTree(b->lchild);				//递归处理左子树
            if (b->rchild != NULL) cout << ",";	//有右孩子节点时才输出,
            DispBTree(b->rchild);				//递归处理右子树
            cout << ")";						//有孩子节点时才输出)
        }
    }
}

void TransTree(BTNode* b, BTNode*& NewTree) {
    NewTree = new BTNode;                       //为新的二叉树开辟内存
    if (b == NULL)
        NewTree = NULL;                         //原节点为空则将新树的节点也置空
    else {
        NewTree->data = b->data;                //交换数据
        TransTree(b->lchild, NewTree->rchild);  //递归左子树
        TransTree(b->rchild, NewTree->lchild);  //递归右子树
    }
}

int BTHeight(BTNode* b)                     //求树高
{
    int lchildh, rchildh;
    if (b == NULL) return(0); 				//空树的高度为0
    else
    {
        lchildh = BTHeight(b->lchild);	    //求左子树的高度为lchildh
        rchildh = BTHeight(b->rchild);	    //求右子树的高度为rchildh
        return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
    }
}

void DestroyBTree(BTNode *&b)               //销毁树
{	
	if (b!=NULL)
	{	DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}

BTNode* FindNode(BTNode* b, ElemType x)//查找结点
{
    BTNode* p;
    if (b == NULL)
        return NULL;
    else if (b->data == x)
        return b;
    else
    {
        p = FindNode(b->lchild, x);
        if (p != NULL)
            return p;
        else
            return FindNode(b->rchild, x);
    }
}

BTNode* FindNodeParent(BTNode* b, ElemType x)//查找结点的双亲
{
    BTNode* p;
    if (b == NULL || (b->lchild == NULL && b->rchild == NULL))
        return NULL;
    else if (b->data == x)
        return NULL;
    else if ((b->lchild != NULL && b->lchild->data == x) || (b->rchild != NULL && b->rchild->data == x))
        return b;
    else
    {
        p = FindNodeParent(b->lchild, x);
        if (p != NULL)
            return p;
        else
            return FindNodeParent(b->rchild, x);
    }
}

//先序遍历
void PreOrder(BTNode* b) {
    if (b != NULL) {
        cout << b->data;
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}
//中序遍历
void InOrder(BTNode* b) {
    if (b != NULL) {
        InOrder(b->lchild);
        cout << b->data;
        InOrder(b->rchild);
    }
}
//后序遍历
void PostOrder(BTNode* b) {
    if (b != NULL) {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        cout << b->data;
    }
}

int NodeHeight(BTNode* b,ElemType x){        //求结点高
    BTNode* p;
    p = FindNode(b, x);
    int height = BTHeight(p);
    return height;
}

void FindWay(BTNode* b, ElemType x, ElemType y) {
   BTNode* start, * end; 
   ElemType *way;
   way = new ElemType;
   start=FindNode(b,x);
   end = FindNode(b,y);
   way[0] = y;
   BTNode* p = end;
   int i = 1;
   while(p->data != start->data) {
       if (FindNodeParent(start, p->data) == NULL) {
           cout << "无路径" << endl;
           break;
       }
       else if (FindNodeParent(start, p->data)->data == x) {
           way[i] = FindNodeParent(start, p->data)->data;
           cout << "路径：" << endl;
           for (; !(i < 0); i--) {
               cout << way[i]<<"->";
           }
           cout << '\b'<<'\b';
           break;
       }
       else if (FindNodeParent(start, p->data)->data==b->data) {
           cout << "无路径" << endl;
           break;
       }
       else if (FindNodeParent(start, p->data)->data != x) {
           p = FindNodeParent(start, p->data);
           way[i] = p->data;
           i++;
       }
    }

   
}