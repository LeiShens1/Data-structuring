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

struct stu//����ѧ���ṹ��
{
	int student_id = 0;//ѧ��
	char student_name[10];//����
	int major_num;//רҵ���
	int score[8];//����
	float final_score;//���ճɼ�
	int ranking;//����
};

typedef stu ElemType;

typedef struct {
	ElemType data[MaxSize];
	int length;
}SqList;

typedef stu KeyType;	//�ؼ�������

typedef struct node
{
	KeyType key;				//�ؼ�����
	struct node* next;			//��һ�����ָ��
} NodeType;						//������������

typedef struct
{
	NodeType* firstp;			//�׽��ָ��
} HashTable;					//��ϣ������

typedef struct bnode
{
	KeyType key;              		//�ؼ�����
	struct bnode* lchild, * rchild;	//���Һ���ָ��
} BSTNode;           				//�����������������

bool Readf1(stu list[]);
void Show(stu list[],int n);
void CreateList(SqList*& L, ElemType a[], int n);
void DestroyList(SqList*& L);
int partition(ElemType R[], int s, int t);
void QuickSort(ElemType R[], int s, int t);
void Merge(ElemType R[], int low, int mid, int high);
void MergeSortDC(ElemType R[], int low, int high);
void InsertHT(HashTable ha[], int& n, int p, KeyType k);                     //���ؼ���k���뵽��ϣ����
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int n1);   //������ϣ��
void SearchHT(HashTable ha[], int p, int k);	                          //�ڹ�ϣ���в��ҹؼ���k
void DispHT(HashTable ha[], int n, int m);
void DestroyHT(HashTable ha[], int m);
bool InsertBST(BSTNode*& bt, KeyType k);
BSTNode* CreateBST(KeyType A[], int n);		//��������������
void DispBST(BSTNode* bt);		           //���һ�����������
BSTNode* SearchBST(BSTNode* bt, int k);
void DestroyBST(BSTNode*& bt);