//ͼ�����ִ洢�ṹ
#pragma once 
#define INF 32767				//�����
#define	MAXV 100				//��󶥵����
typedef char InfoType;

//���¶����ڽӾ�������
typedef struct
{
	int no;						//������
	InfoType info;				//����������Ϣ
} VertexType;					//��������
typedef struct
{
	int edges[MAXV][MAXV];		//�ڽӾ�������
	int n, e;					//������������
	VertexType vexs[MAXV];		//��Ŷ�����Ϣ
} MatGraph;						//������ͼ�ڽӾ�������

//���¶����ڽӱ�����
typedef struct ANode
{
	int adjvex;					//�ñߵ��ڽӵ���
	struct ANode* nextarc;		//ָ����һ���ߵ�ָ��
	int weight;					//�ñߵ������Ϣ����Ȩֵ�������ͱ�ʾ��
} ArcNode;						//�߽������
typedef struct Vnode
{
	InfoType info;				//����������Ϣ
	int count;					//��Ŷ������,����������������
	ArcNode* firstarc;			//ָ���һ����
} VNode;						//�ڽӱ�ͷ�������
typedef struct
{
	VNode adjlist[MAXV];		//�ڽӱ�ͷ�������
	int n, e;					//ͼ�ж�����n�ͱ���e
} AdjGraph;						//������ͼ�ڽӱ�����

//------------------------------------------------------------
//----�ڽӾ���Ļ��������㷨----------------------------------
//------------------------------------------------------------
void CreateMat(MatGraph& g, int A[MAXV][MAXV], int n, int e);   //����ͼ���ڽӾ���
void DispMat(MatGraph g);	                                 //����ڽӾ���g
//------------------------------------------------------------

//------------------------------------------------------------
//----�ڽӱ�Ļ��������㷨------------------------------------
//------------------------------------------------------------
void CreateAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e);  //����ͼ���ڽӱ�
void DispAdj(AdjGraph* G);	                                 //����ڽӱ�G
void DestroyAdj(AdjGraph*& G);		                         //����ͼ���ڽӱ�

//����8.9�����㷨:�󲻴�Ȩ������ͨͼG�дӶ���u������v��һ�����·����
typedef struct
{
	int data;						//������
	int parent;						//ǰһ�������λ��
} QUERE;							//�ǻ��ζ�������

//������ȱ����㷨
#define MaxSize 100
//---------------------------------------------------------
//--������ȱ�����ʹ�ö��еĻ��������㷨-------------------
//---------------------------------------------------------
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front, rear;		//���׺Ͷ�βָ��
} SqQueue;
void InitQueue(SqQueue*& q);
void DestroyQueue(SqQueue*& q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue*& q, ElemType e);
bool deQueue(SqQueue*& q, ElemType& e);

//Kruskal�㷨
//#define MaxSize 100
typedef struct
{
	int u;			//�ߵ���ʼ����
	int v;			//�ߵ���ֹ����
	int w;			//�ߵ�Ȩֵ
} Edge;


//�Ľ���Kruskal�㷨
//#define MaxSize 100
//-----���鼯�㷨��ʼ---------------------------------------
//typedef struct 
//{
//	int u;			//�ߵ���ʼ����
//    int v;			//�ߵ���ֹ����
//    int w;			//�ߵ�Ȩֵ
//} Edge;
typedef struct node
{
	int rank;						//����Ӧ��
	int parent;						//����Ӧ˫���±�
} UFSTree;