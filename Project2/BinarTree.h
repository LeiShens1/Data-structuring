//
// Created by À×ÖÇÓî on 2023/11/11.
//
#ifndef BINARTREE_H
#define BINARTREE_H

#include <iostream>
using namespace std;
#define MaxSize 100
typedef char ElemType;
typedef struct node {
    ElemType data;
    struct node* lchild;
    struct node* rchild;
}BTNode;

void CreateBTree(BTNode*& b, char* str);
void DispBTree(BTNode* b);
void TransTree(BTNode* b, BTNode*& NewTree);
int BTHeight(BTNode* b);
void DestroyBTree(BTNode*& b);
BTNode* FindNodeParent(BTNode* b, ElemType x);
BTNode* FindNode(BTNode* b, ElemType x);
void PreOrder(BTNode* b);
void InOrder(BTNode* b);
void PostOrder(BTNode* b);
int NodeHeight(BTNode* b, ElemType x);
void FindWay(BTNode* b, ElemType x, ElemType y);
#endif //BINARTREE_H
