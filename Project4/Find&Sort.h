#pragma once
#define MAX_majors 50  
#define MAX_stus 6000
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<string.h>
#include <ctime>
using namespace std;
#define MaxSize 100

struct stu//定义学生结构体
{
	int student_id = 0;//学号
	char student_name[10];//姓名
	int major_num;//专业编号
	int score[8];//分数
	float final_score;//最终成绩
	int ranking;//排名
};

typedef stu ElemType;

typedef struct {
	ElemType data[MaxSize];
	int length;
}SqList;

typedef stu KeyType;	//关键字类型

typedef struct node
{
	KeyType key;				//关键字域
	struct node* next;			//下一个结点指针
} NodeType;						//单链表结点类型

typedef struct
{
	NodeType* firstp;			//首结点指针
} HashTable;					//哈希表类型

typedef struct bnode
{
	KeyType key;              		//关键字项
	struct bnode* lchild, * rchild;	//左右孩子指针
} BSTNode;           				//二叉排序树结点类型

bool Readf1(stu list[]);
void Show(stu list[],int n);
void CreateList(SqList*& L, ElemType a[], int n);
void DestroyList(SqList*& L);
int partition(ElemType R[], int s, int t);
void QuickSort(ElemType R[], int s, int t);
void Merge(ElemType R[], int low, int mid, int high);
void MergeSortDC(ElemType R[], int low, int high);
void InsertHT(HashTable ha[], int& n, int p, KeyType k);                     //将关键字k插入到哈希表中
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int n1);   //创建哈希表
void SearchHT(HashTable ha[], int p, int k);	                          //在哈希表中查找关键字k
void DispHT(HashTable ha[], int n, int m);
void DestroyHT(HashTable ha[], int m);
bool InsertBST(BSTNode*& bt, KeyType k);
BSTNode* CreateBST(KeyType A[], int n);		//创建二叉排序树
void DispBST(BSTNode* bt);		           //输出一棵排序二叉树
BSTNode* SearchBST(BSTNode* bt, int k);
void DestroyBST(BSTNode*& bt);