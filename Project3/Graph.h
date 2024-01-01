//图的两种存储结构
#pragma once 
#define INF 32767				//定义∞
#define	MAXV 100				//最大顶点个数
typedef char InfoType;

//以下定义邻接矩阵类型
typedef struct
{
	int no;						//顶点编号
	InfoType info;				//顶点其他信息
} VertexType;					//顶点类型
typedef struct
{
	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n, e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MatGraph;						//完整的图邻接矩阵类型

//以下定义邻接表类型
typedef struct ANode
{
	int adjvex;					//该边的邻接点编号
	struct ANode* nextarc;		//指向下一条边的指针
	int weight;					//该边的相关信息，如权值（用整型表示）
} ArcNode;						//边结点类型
typedef struct Vnode
{
	InfoType info;				//顶点其他信息
	int count;					//存放顶点入度,仅仅用于拓扑排序
	ArcNode* firstarc;			//指向第一条边
} VNode;						//邻接表头结点类型
typedef struct
{
	VNode adjlist[MAXV];		//邻接表头结点数组
	int n, e;					//图中顶点数n和边数e
} AdjGraph;						//完整的图邻接表类型

//------------------------------------------------------------
//----邻接矩阵的基本运算算法----------------------------------
//------------------------------------------------------------
void CreateMat(MatGraph& g, int A[MAXV][MAXV], int n, int e);   //创建图的邻接矩阵
void DispMat(MatGraph g);	                                 //输出邻接矩阵g
//------------------------------------------------------------

//------------------------------------------------------------
//----邻接表的基本运算算法------------------------------------
//------------------------------------------------------------
void CreateAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e);  //创建图的邻接表
void DispAdj(AdjGraph* G);	                                 //输出邻接表G
void DestroyAdj(AdjGraph*& G);		                         //销毁图的邻接表

//【例8.9】的算法:求不带权无向连通图G中从顶点u到顶点v的一条最短路径。
typedef struct
{
	int data;						//顶点编号
	int parent;						//前一个顶点的位置
} QUERE;							//非环形队列类型

//广度优先遍历算法
#define MaxSize 100
//---------------------------------------------------------
//--广度优先遍历中使用队列的基本运算算法-------------------
//---------------------------------------------------------
typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];
	int front, rear;		//队首和队尾指针
} SqQueue;
void InitQueue(SqQueue*& q);
void DestroyQueue(SqQueue*& q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue*& q, ElemType e);
bool deQueue(SqQueue*& q, ElemType& e);

//Kruskal算法
//#define MaxSize 100
typedef struct
{
	int u;			//边的起始顶点
	int v;			//边的终止顶点
	int w;			//边的权值
} Edge;


//改进的Kruskal算法
//#define MaxSize 100
//-----并查集算法开始---------------------------------------
//typedef struct 
//{
//	int u;			//边的起始顶点
//    int v;			//边的终止顶点
//    int w;			//边的权值
//} Edge;
typedef struct node
{
	int rank;						//结点对应秩
	int parent;						//结点对应双亲下标
} UFSTree;