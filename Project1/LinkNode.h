#pragma once
#include<fstream>
//定义保存学生信息的结构体 studen
typedef struct student        //Define the struct
{
	char ID[6] = {' ',' ',' ',' ',' ',' '};               
	                          //学生的学号 student ID
	char name[11] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};	          
	                          //学生的姓名 student name
	char pro_number[3] = { ' ',' ',' ' };       
	                          //学生专业编号 Major ID
	short GEC1;               //通识教育1
	short GEC2;               //通识教育2
	short GEC3;               //通识教育3    GEC is the abbreviation of General Education Courses
	short PEC1;               //公共基础课1
	short PEC2;               //公共基础课2              
	short PEC3;               //公共基础课3  PEC is the abbreviation of Public Elementary Courses
	short CaIC1;              //专业主干课1
	short CaIC2;              //专业主干课2  CaIC is the abbreviation of Colloid and Interface Chenistry
	float weights;            //加权分数，以后排序的依据
} ElemType;
typedef struct LNode
{
	ElemType data;
	struct LNode* next;		//指向后继结点
} LinkNode;					//声明单链表结点类型
void CreateListF(LinkNode*& L, ElemType a[], int n); //头插法建立单链表
void CreateListR(LinkNode*& L, ElemType a[], int n); //尾插法建立单链表
void InitList(LinkNode*& L);                         //创建头结点
void DestroyList(LinkNode*& L);                      //删除链表
bool ListEmpty(LinkNode* L);                         //判断链表是否为空
int ListLength(LinkNode* L);                         //输出链表的长度
void DispList(LinkNode* L);                          //显示链表
bool GetElem(LinkNode* L, int i, ElemType& e);       //获得链表某个位置的数值
bool FindandShow(LinkNode* L, int i);			     //找到并显示单个数据
//int LocateElem(LinkNode* L, ElemType e);             //查找数据在链表的位置
bool ListInsert(LinkNode* L, int i, ElemType e);     //在指定的位置插入指定的数据
bool ListDelete(LinkNode* L, int i, ElemType& e);    //删除指定位置的节点
bool Readf1(LinkNode*& L);							 //读取f1中数据并保存至顺序表
void sort(LinkNode*& L);                             //按总评排序