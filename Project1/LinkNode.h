#pragma once
#include<fstream>
//���屣��ѧ����Ϣ�Ľṹ�� studen
typedef struct student        //Define the struct
{
	char ID[6] = {' ',' ',' ',' ',' ',' '};               
	                          //ѧ����ѧ�� student ID
	char name[11] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};	          
	                          //ѧ�������� student name
	char pro_number[3] = { ' ',' ',' ' };       
	                          //ѧ��רҵ��� Major ID
	short GEC1;               //ͨʶ����1
	short GEC2;               //ͨʶ����2
	short GEC3;               //ͨʶ����3    GEC is the abbreviation of General Education Courses
	short PEC1;               //����������1
	short PEC2;               //����������2              
	short PEC3;               //����������3  PEC is the abbreviation of Public Elementary Courses
	short CaIC1;              //רҵ���ɿ�1
	short CaIC2;              //רҵ���ɿ�2  CaIC is the abbreviation of Colloid and Interface Chenistry
	float weights;            //��Ȩ�������Ժ����������
} ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;		//ָ���̽��
} LinkNode;					//����������������
void CreateListF(LinkNode*& L, ElemType a[], int n); //ͷ�巨����������
void CreateListR(LinkNode*& L, ElemType a[], int n); //β�巨����������
void InitList(LinkNode*& L);                         //����ͷ���
void DestroyList(LinkNode*& L);                      //ɾ������
bool ListEmpty(LinkNode* L);                         //�ж������Ƿ�Ϊ��
int ListLength(LinkNode* L);                         //�������ĳ���
void DispList(LinkNode* L);                          //��ʾ����
bool GetElem(LinkNode* L, int i, ElemType& e);       //�������ĳ��λ�õ���ֵ
bool FindandShow(LinkNode* L, int i);			     //�ҵ�����ʾ��������
//int LocateElem(LinkNode* L, ElemType e);             //���������������λ��
bool ListInsert(LinkNode* L, int i, ElemType e);     //��ָ����λ�ò���ָ��������
bool ListDelete(LinkNode* L, int i, ElemType& e);    //ɾ��ָ��λ�õĽڵ�
bool Readf1(LinkNode*& L);							 //��ȡf1�����ݲ�������˳���
void sort(LinkNode*& L);                             //����������