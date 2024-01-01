#include"LinkNode.h"
#include <iostream>
#include<iomanip>
using namespace std;

void CreateListF(LinkNode*& L, ElemType a[], int n)
//ͷ�巨����������
{
	LinkNode* s;
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//����ͷ���
	L->next = NULL;
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//�����½��s
		s->data = a[i];
		s->next = L->next;			            //�����s����ԭ��ʼ���֮ǰ,ͷ���֮��
		L->next = s;
	}
}
void CreateListR(LinkNode*& L, ElemType a[], int n)
//β�巨����������
{
	LinkNode* s, * r;
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//����ͷ���
	L->next = NULL;
	r = L;					                    //rʼ��ָ���ն˽��,��ʼʱָ��ͷ���
	for (int i = 0; i < n; i++)
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//�����½��s
		s->data = a[i];
		r->next = s;			                //�����s������r֮��
		r = s;
	}
	r->next = NULL;			                    //�ն˽��next����ΪNULL
}
void InitList(LinkNode*& L)
{
	L = (LinkNode*)malloc(sizeof(LinkNode));  	//����ͷ���
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
	free(pre);	                                //��ʱpΪNULL,preָ��β���,�ͷ���
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
	if (i <= 0) return false;   //i���󷵻ؼ�
	while (j < i && p != NULL)
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				//�����ڵ�i�����ݽ��
		return false;
	else						//���ڵ�i�����ݽ��
	{
		e = p->data;
		return true;
	}
}
bool FindandShow(LinkNode *L, int i) {
	ElemType e;
	GetElem(L, i, e);
	cout << "ѧ�ţ�";
	for (int i = 0; e.ID[i] != ' '; i++)
		cout << e.ID[i];
	cout << endl << "������";
	for (int i = 0; e.name[i] != ' '; i++)
		cout << e.name[i];
	cout << endl << "רҵ��";
	for (int i = 0; e.pro_number[i] != ' '; i++)
		cout << e.pro_number[i];
	cout << endl << "ͨʶ�Σ�"
		<< e.GEC1 << " " << e.GEC2 << " " << e.GEC3 << endl;
	cout << "�����Σ�" << e.PEC1 << " " << e.PEC2 << " " << e.PEC3 << endl;
	cout << "רҵ�Σ�" << e.CaIC1 << " " << e.CaIC2 << endl;
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
		return false;			    //i���󷵻ؼ�
	while (j < i - 1 && p != NULL)  //���ҵ�i-1�����p
	{
		j++;
		p = p->next;
	}
	if (p == NULL)					//δ�ҵ�λ��Ϊi-1�Ľ��
		return false;
	else							//�ҵ�λ��Ϊi-1�Ľ��*p
	{
		s = (LinkNode*)malloc(sizeof(LinkNode));//�����½��*s
		s->data = e;
		s->next = p->next;			//��s�����뵽���p֮��
		p->next = s;
		return true;
	}
}
bool ListDelete(LinkNode* L, int i, ElemType& e)
{
	int j = 0;
	LinkNode* p = L, * q;
	if (i <= 0)
		return false;		        //i���󷵻ؼ�
	while (j < i - 1 && p != NULL)	//���ҵ�i-1�����
	{
		j++;
		p = p->next;
	}
	if (p == NULL)				    //δ�ҵ�λ��Ϊi-1�Ľ��
		return false;
	else						    //�ҵ�λ��Ϊi-1�Ľ��p
	{
		q = p->next;				//qָ��Ҫɾ���Ľ��
		if (q == NULL)
			return false;			//�������ڵ�i�����,����false
		e = q->data;
		p->next = q->next;			//�ӵ�������ɾ��q���
		free(q);					//�ͷ�q���
		return true;
	}
}
bool Readf1(LinkNode *&L)			//���뺯��������������
{
	ifstream ifs;					//�����ļ���ifs
	ifs.open("f1.txt", ios::in);	//���ļ���
	char judge1;					//���忪���ַ����ж��Ƿ�����ļ�
	LinkNode *s, *r;
	L = new(LinkNode);
	r = L;
	for (long long i = 0; ifs >> judge1; i++)//ѭ������
	{
		s = new(LinkNode);
		ifs.putback(judge1);		//�Ż��ж��ַ�
		//��ȡѧ��
		char id;
		for (int i = 0; (id = ifs.get()) != ' '; i++) 
			s->data.ID[i] = id;
		//��ȡ����
		char ch;
		//ѭ����ȡ�ַ�ֱ��' '����
		for (int k = 0; (ch = ifs.get()) != ' '; k++)	//�����ȡ�����е��ַ�
			s->data.name[k] = ch;						//��ȡ�������ִ���ṹ����
		//��ȡרҵ���
		char num;
		for (int k = 0; (num = ifs.get()) != ' '; k++)
			s->data.pro_number[k] = num;
		//��ȡ�ɼ�
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
	char judge;		//����char���ͱ������ж��Ƿ��ȡ�����ļ�β
	judge = ifs.get();
	if (judge == EOF)
		return true;//��ȡ�����ļ�β������true
	else
					//δ��ȡ���ļ�β������false
		cout << "�ļ���ȡʧ��" << endl; return false;
	ifs.close();
}
void sort(LinkNode*& L)
{
	LinkNode* p,* pre,*q;
	p = L->next->next;		//pָ��L�ĵ�2�����ݽ��
	L->next->next = NULL;		//����ֻ��һ�����ݽ��������
	while (p != NULL)
	{
		q = p->next;		//q����p����̽���ָ��

		pre = L;  			//�������ͷ���бȽϣ�preָ�����p��ǰ�����
		while (pre->next != NULL && pre->next->data.weights > p->data.weights)
			pre = pre->next;	//����������Ҳ���p��ǰ�����pre

		p->next = pre->next;
		pre->next = p;
		p = q;			//ɨ��ԭ���������µĽ��
	}
}
