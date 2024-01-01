#include"LinkNode.h"
#include <iostream>
#include<iomanip>
using namespace std;

void CreateListF(LinkNode*& L, ElemType a[], int n)
//头插法建立单链表
{
	LinkNode* s;
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//创建头结点
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//创建新结点s
		s->data = a[i];
		s->next = L->next;			            //将结点s插在原开始结点之前,头结点之后
		L->next = s;
	}
}
void CreateListR(LinkNode*& L, ElemType a[], int n)
//尾插法建立单链表
{
	LinkNode* s, * r;
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//创建头结点
	L->next = NULL;
	r = L;					                    //r始终指向终端结点,开始时指向头结点
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//创建新结点s
		s->data = a[i];
		r->next = s;			                //将结点s插入结点r之后
		r = s;
	}
	r->next = NULL;			                    //终端结点next域置为NULL
}
void InitList(LinkNode*& L)
{
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//创建头结点
	L->next = NULL;
}
void DestroyList(LinkNode*& L)
{
	if (L == NULL)
		return;
	LinkNode* pre = L, * p = pre->next;
	while (p != NULL)
	{
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);	                                //此时p为NULL,pre指向尾结点,释放它
	L = NULL;
}
bool ListEmpty(LinkNode* L)
{
	return(L->next == NULL);
}
int ListLength(LinkNode* L)
{
	LinkNode* p = L;
	int i = 0;
	while (p->next != NULL)
	{
		i++;
		p = p->next;
	}
	return(i);
}
void DispList(LinkNode* L)
{
	if (L == NULL)
		return;
	LinkNode* p = L->next;
	cout << "ID\tName\tPro\tGEC1\tGEC2\tGEC3\tPEC1\tPEC2\tPEC3\tCaIC1\tCaIC2\tWeights" << endl;
	while (p != NULL)
	{
		for (int i = 0; p->data.ID[i] != ' '; i++) 
			cout << p->data.ID[i];
		cout << '\t';
		for (int i = 0; p->data.name[i] != ' '; i++) 
			cout << p->data.name[i] ;
		cout << '\t';
		for (int i = 0; p->data.pro_number[i] != ' '; i++)
			cout << p->data.pro_number[i] ;
		cout << '\t';
		cout << setfill(' ') << setw(3) << p->data.GEC1 << '\t';
		cout << setfill(' ') << setw(3) << p->data.GEC2 << '\t';
		cout << setfill(' ') << setw(3) << p->data.GEC3 << '\t';
		cout << setfill(' ') << setw(3) << p->data.PEC1 << '\t';
		cout << setfill(' ') << setw(3) << p->data.PEC2 << '\t';
		cout << setfill(' ') << setw(3) << p->data.PEC3 << '\t';
		cout << setfill(' ') << setw(3) << p->data.CaIC1 << '\t';
		cout << setfill(' ') << setw(3) << p->data.CaIC2 << '\t';
		cout << setfill(' ') << setw(3) << p->data.weights << endl;
		p = p->next;
	}
	printf("\n");
}
bool GetElem(LinkNode* L, int i, ElemType& e)
{
	int j = 0;
	LinkNode* p = L;
	if (i <= 0) return false;   //i错误返回假
	while (j < i && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//不存在第i个数据结点
		return false;
	else						//存在第i个数据结点
	{
		e = p->data;
		return true;
	}
}
bool FindandShow(LinkNode *L, int i) {
	ElemType e;
	GetElem(L, i, e);
	cout << "学号：";
	for (int i = 0; e.ID[i] != ' '; i++)
		cout << e.ID[i];
	cout << endl << "姓名：";
	for (int i = 0; e.name[i] != ' '; i++)
		cout << e.name[i];
	cout << endl << "专业：";
	for (int i = 0; e.pro_number[i] != ' '; i++)
		cout << e.pro_number[i];
	cout << endl << "通识课："
		<< e.GEC1 << " " << e.GEC2 << " " << e.GEC3 << endl;
	cout << "公共课：" << e.PEC1 << " " << e.PEC2 << " " << e.PEC3 << endl;
	cout << "专业课：" << e.CaIC1 << " " << e.CaIC2 << endl;
	return true;
}
/*int LocateElem(LinkNode* L, ElemType e)
{
	LinkNode* p = L->next;
	int n = 1;
	while (p != NULL && p->data != e)
	{
		p = p->next;
		n++;
	}
	if (p == NULL)
		return(0);
	else
		return(n);
}*/
bool ListInsert(LinkNode* L, int i, ElemType e)
{
	int j = 0;
	LinkNode* p = L, * s;
	if (i <= 0)
		return false;			    //i错误返回假
	while (j < i - 1 && p != NULL)  //查找第i-1个结点p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)					//未找到位序为i-1的结点
		return false;
	else							//找到位序为i-1的结点*p
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//创建新结点*s
		s->data = e;
		s->next = p->next;			//将s结点插入到结点p之后
		p->next = s;
		return true;
	}
}
bool ListDelete(LinkNode* L, int i, ElemType& e)
{
	int j = 0;
	LinkNode* p = L, * q;
	if (i <= 0)
		return false;		        //i错误返回假
	while (j < i - 1 && p != NULL)	//查找第i-1个结点
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				    //未找到位序为i-1的结点
		return false;
	else						    //找到位序为i-1的结点p
	{
		q = p->next;				//q指向要删除的结点
		if (q == NULL)
			return false;			//若不存在第i个结点,返回false
		e = q->data;
		p->next = q->next;			//从单链表中删除q结点
		free(q);					//释放q结点
		return true;
	}
}
bool Readf1(LinkNode *&L)			//读入函数，传引用链表
{
	ifstream ifs;					//定义文件流ifs
	ifs.open("f1.txt", ios::in);	//打开文件流
	char judge1;					//定义开关字符，判断是否读完文件
	LinkNode *s, *r;
	L = new(LinkNode);
	r = L;
	for (long long i = 0; ifs >> judge1; i++)//循环读入
	{
		s = new(LinkNode);
		ifs.putback(judge1);		//放回判断字符
		//获取学号
		char id;
		for (int i = 0; (id = ifs.get()) != ' '; i++) 
			s->data.ID[i] = id;
		//获取姓名
		char ch;
		//循环读取字符直到' '结束
		for (int k = 0; (ch = ifs.get()) != ' '; k++)	//逐个获取名字中的字符
			s->data.name[k] = ch;						//读取出的名字存入结构体中
		//获取专业编号
		char num;
		for (int k = 0; (num = ifs.get()) != ' '; k++)
			s->data.pro_number[k] = num;
		//获取成绩
		short score;
		ifs >> score;
		s->data.GEC1 = score;
		ifs >> score;
		s->data.GEC2 = score;
		ifs >> score;
		s->data.GEC3 = score;
		ifs >> score;
		s->data.PEC1 = score;
		ifs >> score;
		s->data.PEC2 = score;
		ifs >> score;
		s->data.PEC3 = score;
		ifs >> score;
		s->data.CaIC1 = score;
		ifs >> score;
		s->data.CaIC2 = score;
		s->data.weights = 0.8 * (s->data.PEC1 + s->data.PEC2 + s->data.PEC3)
			+ 1.2 * (s->data.CaIC1 + s->data.CaIC2);
		r->next = s;
		r = s;
	}
	r->next = NULL;
	char judge;		//创建char类型变量来判断是否读取到了文件尾
	judge = ifs.get();
	if (judge == EOF)
		return true;//读取到了文件尾，返回true
	else
					//未读取到文件尾，返回false
		cout << "文件读取失败" << endl; return false;
	ifs.close();
}
void sort(LinkNode*& L)
{
	LinkNode* p,* pre,*q;
	p = L->next->next;		//p指向L的第2个数据结点
	L->next->next = NULL;		//构造只含一个数据结点的有序表
	while (p != NULL)
	{
		q = p->next;		//q保存p结点后继结点的指针

		pre = L;  			//从有序表开头进行比较，pre指向插入p的前驱结点
		while (pre->next != NULL && pre->next->data.weights > p->data.weights)
			pre = pre->next;	//在有序表中找插入p的前驱结点pre

		p->next = pre->next;
		pre->next = p;
		p = q;			//扫描原单链表余下的结点
	}
}
