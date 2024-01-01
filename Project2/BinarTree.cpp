//
// Created by ������ on 2023/11/11.
//
#include "BinarTree.h"

void CreateBTree(BTNode*& b, char* str)	            //����������
{
    BTNode* St[MaxSize], * p = NULL;
    int top = -1, k, j = 0;
    char ch;
    b = NULL;				                        //�����Ķ�������ʼʱΪ��
    ch = str[j];
    while (ch != '\0')  	                        //strδɨ����ʱѭ��
    {
        switch (ch)
        {
        case '(':top++; St[top] = p; k = 1; break;	//Ϊ���ӽڵ�
        case ')':top--; break;
        case ',':k = 2; break;                      //Ϊ���ӽڵ��ҽڵ�
        default:p = (BTNode*)malloc(sizeof(BTNode));
            p->data = ch; p->lchild = p->rchild = NULL;
            if (b == NULL)                    	 	//*pΪ�������ĸ��ڵ�
                b = p;
            else  							       	//�ѽ������������ڵ�
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
            cout << "(";						//�к��ӽڵ�ʱ�����(
            DispBTree(b->lchild);				//�ݹ鴦��������
            if (b->rchild != NULL) cout << ",";	//���Һ��ӽڵ�ʱ�����,
            DispBTree(b->rchild);				//�ݹ鴦��������
            cout << ")";						//�к��ӽڵ�ʱ�����)
        }
    }
}

void TransTree(BTNode* b, BTNode*& NewTree) {
    NewTree = new BTNode;                       //Ϊ�µĶ����������ڴ�
    if (b == NULL)
        NewTree = NULL;                         //ԭ�ڵ�Ϊ���������Ľڵ�Ҳ�ÿ�
    else {
        NewTree->data = b->data;                //��������
        TransTree(b->lchild, NewTree->rchild);  //�ݹ�������
        TransTree(b->rchild, NewTree->lchild);  //�ݹ�������
    }
}

int BTHeight(BTNode* b)                     //������
{
    int lchildh, rchildh;
    if (b == NULL) return(0); 				//�����ĸ߶�Ϊ0
    else
    {
        lchildh = BTHeight(b->lchild);	    //���������ĸ߶�Ϊlchildh
        rchildh = BTHeight(b->rchild);	    //���������ĸ߶�Ϊrchildh
        return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
    }
}

void DestroyBTree(BTNode *&b)               //������
{	
	if (b!=NULL)
	{	DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}

BTNode* FindNode(BTNode* b, ElemType x)//���ҽ��
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

BTNode* FindNodeParent(BTNode* b, ElemType x)//���ҽ���˫��
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

//�������
void PreOrder(BTNode* b) {
    if (b != NULL) {
        cout << b->data;
        PreOrder(b->lchild);
        PreOrder(b->rchild);
    }
}
//�������
void InOrder(BTNode* b) {
    if (b != NULL) {
        InOrder(b->lchild);
        cout << b->data;
        InOrder(b->rchild);
    }
}
//�������
void PostOrder(BTNode* b) {
    if (b != NULL) {
        PostOrder(b->lchild);
        PostOrder(b->rchild);
        cout << b->data;
    }
}

int NodeHeight(BTNode* b,ElemType x){        //�����
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
           cout << "��·��" << endl;
           break;
       }
       else if (FindNodeParent(start, p->data)->data == x) {
           way[i] = FindNodeParent(start, p->data)->data;
           cout << "·����" << endl;
           for (; !(i < 0); i--) {
               cout << way[i]<<"->";
           }
           cout << '\b'<<'\b';
           break;
       }
       else if (FindNodeParent(start, p->data)->data==b->data) {
           cout << "��·��" << endl;
           break;
       }
       else if (FindNodeParent(start, p->data)->data != x) {
           p = FindNodeParent(start, p->data);
           way[i] = p->data;
           i++;
       }
    }

   
}