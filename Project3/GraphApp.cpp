#include <iostream>
#include"Graph.h"
using namespace std;

//邻接矩阵和邻接表的相互转换
static void MatToList(MatGraph g, AdjGraph*& G)		//将邻接矩阵g转换成邻接表G
{
	int i, j;
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < g.n; i++)				//将邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < g.n; i++)				//检查邻接矩阵中每个元素
	{
		for (j = g.n - 1; j >= 0; j--)
		{
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)	//存在一条边
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));	//创建一个边结点p
				p->adjvex = j; p->weight = g.edges[i][j];
				p->nextarc = G->adjlist[i].firstarc;		//采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = g.n; G->e = g.e;
}

//广度优先遍历算法
static void BFS(AdjGraph* G, int v)
{
	int w, i;
	ArcNode* p;
	SqQueue* qu;							//定义环形队列指针
	InitQueue(qu);							//初始化队列
	int visited[MAXV];            			//定义顶点访问标志数组
	for (i = 0; i < G->n; i++) visited[i] = 0;		//访问标志数组初始化
	printf("%2d", v); 						//输出被访问顶点的编号
	visited[v] = 1;              				//置已访问标记
	enQueue(qu, v);
	while (!QueueEmpty(qu))       			//队不空循环
	{
		deQueue(qu, w);						//出队一个顶点w
		p = G->adjlist[w].firstarc; 			//指向w的第一个邻接点
		while (p != NULL)						//查找w的所有邻接点
		{
			if (visited[p->adjvex] == 0) 		//若当前邻接点未被访问
			{
				printf("%2d", p->adjvex);  	//访问该邻接点
				visited[p->adjvex] = 1;		//置已访问标记
				enQueue(qu, p->adjvex);		//该顶点进队
			}
			p = p->nextarc;              		//找下一个邻接点
		}
	}
	printf("\n");
}

//深度优先遍历算法
int visited[MAXV] = { 0 };            	//定义顶点访问标志数组
static void DFS(AdjGraph *G,int v)  
{
	ArcNode *p;
	visited[v]=1;                   //置已访问标记
	printf("%2d",v); 				//输出被访问顶点的编号
	p=G->adjlist[v].firstarc;      	//p指向顶点v的第一条弧的弧头结点
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//若p->adjvex顶点未访问,递归访问它
			DFS(G,p->adjvex);    
		p=p->nextarc;              	//p指向顶点v的下一条弧的弧头结点
	}
}

//Floyd算法
static void DispathFloyd(MatGraph g, int A[][MAXV], int path[][MAXV])
{
	int i, j, k, s;
	int apath[MAXV], d;		//存放一条最短路径中间顶点(反向)及其顶点个数
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)			//若顶点i和j之间存在路径
			{
				printf("  从%d到%d的路径为:", i, j);
				k = path[i][j];
				d = 0; apath[d] = j;				//路径上添加终点
				while (k != -1 && k != i)			//路径上添加中间点
				{
					d++; apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;				//路径上添加起点
				printf("%d", apath[d]);			//输出起点
				for (s = d - 1; s >= 0; s--)			//输出路径上的中间顶点
					printf(",%d", apath[s]);
				printf("\t路径长度为:%d\n", A[i][j]);
			}
		}
}
static void Floyd(MatGraph g)							//Floyd算法
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;					//顶点i到j有边时
			else
				path[i][j] = -1;				//顶点i到j没有边时
		}
	}
	for (k = 0; k < g.n; k++)						//依次考察所有顶点
	{
		for (i = 0; i < g.n; i++)
		{
			for (j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];	//修改最短路径长度
					path[i][j] = path[k][j];		//修改最短路径
				}
			}
		}
	}
	DispathFloyd(g, A, path);							//输出最短路径
}

//Prim算法
static void Prim(MatGraph g, int v)
{
	int lowcost[MAXV];			//顶点i是否在U中
	int min;
	int closest[MAXV], i, j, k;
	for (i = 0; i < g.n; i++)          //给lowcost[]和closest[]置初值
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < g.n; i++)          //找出n-1个顶点
	{
		min = INF;
		for (j = 0; j < g.n; j++)       //在(V-U)中找出离U最近的顶点k
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;			//k记录最近顶点的编号
			}
		printf(" 边(%d,%d)权为:%d\n", closest[k], k, min);
		lowcost[k] = 0;         	//标记k已经加入U
		for (j = 0; j < g.n; j++)   	//修改数组lowcost和closest
			if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.edges[k][j];
				closest[j] = k;
			}
	}
}
//Kruskal算法
static void InsertSort(Edge E[], int n) //对E[0..n-1]按递增有序进行直接插入排序
{
	int i, j;
	Edge temp;
	for (i = 1; i < n; i++)
	{
		temp = E[i];
		j = i - 1;				//从右向左在有序区E[0..i-1]中找E[i]的插入位置
		while (j >= 0 && temp.w < E[j].w)
		{
			E[j + 1] = E[j];	//将关键字大于E[i].w的记录后移
			j--;
		}
		E[j + 1] = temp;		//在j+1处插入E[i] 
	}
}
static void Kruskal(MatGraph g)
{
	int i, j, u1, v1, sn1, sn2, k;
	int vset[MAXV];
	Edge E[MaxSize];				//存放所有边
	k = 0;							//E数组的下标从0开始计
	for (i = 0; i < g.n; i++)				//由g产生的边集E
		for (j = 0; j <= i; j++)
		{
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g.edges[i][j];
				k++;
			}
		}
	InsertSort(E, g.e);				//采用直接插入排序对E数组按权值递增排序
	for (i = 0; i < g.n; i++) 			//初始化辅助数组
		vset[i] = i;
	k = 1;                 			//k表示当前构造生成树的第几条边,初值为1
	j = 0;                 			//E中边的下标,初值为0
	while (k < g.n)       			//生成的边数小于n时循环
	{
		u1 = E[j].u; v1 = E[j].v;        //取一条边的头尾顶点
		sn1 = vset[u1];
		sn2 = vset[v1]; 				//分别得到两个顶点所属的集合编号
		if (sn1 != sn2)     	  		//两顶点属于不同的集合,该边是最小生成树的一条边
		{
			printf(" 边(%d,%d)权为:%d\n", u1, v1, E[j].w);
			k++;                    //生成边数增1
			for (i = 0; i < g.n; i++)     //两个集合统一编号
				if (vset[i] == sn2)  	//集合编号为sn2的改为sn1
					vset[i] = sn1;
		}
		j++;   						//扫描下一条边
	}
}

int main() {
	char choice;
	while (1) {
		cout << "1.图的遍历" << endl;
		cout << "2.最短路径" << endl;
		cout << "3.最小生成树" << endl;
		cout << "4.退出程序" << endl;
		cin >> choice;
		switch (choice){
		case'1': 
		{
			system("cls");
			//采用邻接矩阵储存图G1对应的数组
			int A1[MAXV][MAXV] =
			{
				{0,1,0,1,1},
				{1,0,1,1,0},
				{0,1,0,1,1},
				{1,1,1,0,1},
				{1,0,1,1,0}
			};
			cout << "无权无向图G1：" << endl;
			cout << "  1  " << endl
				 << " /|\\ " << endl
				 << "2-3-0" << endl
				 << " \\|/ " << endl
				 << "  4  " << endl;
			//图的构建
			MatGraph G1;
			AdjGraph *g1;
			CreateMat(G1, A1, 5, 8);
			cout << "G1的邻接矩阵输出：" << endl;
			DispMat(G1);
			cout << endl;
			//图的广度优先遍历
			MatToList(G1,g1);//将邻接矩阵转化为邻接表
			cout << "G1的广度优先遍历（起点为2）:" << endl;
			BFS(g1, 2);
			cout << "G1的深度优先遍历（起点为2）:" << endl;
			DFS(g1, 2);
			cout << endl;
			DestroyAdj(g1);
			break;
		}
		case'2':
		{	
			system("cls");
			//采用邻接矩阵储存有向带权图G2对应的数组
			MatGraph G2;
			int A[MAXV][MAXV]={
				{0,4,6,6,INF,INF,INF},
				{INF,0,1,INF,7,INF,INF},
				{INF,INF,0,INF,6,4,INF},
				{INF,INF,2,0,INF,5,INF},
				{INF,INF,INF,INF,0,INF,6},
				{INF,INF,INF,INF,1,0,8},
				{INF,INF,INF,INF,INF,INF,0}};
			int n=7, e=12;
			CreateMat(G2,A,n,e);			//建立《教程》中图8.35的邻接矩阵
			printf("图G2的邻接矩阵:\n");
			DispMat(G2);					//输出邻接矩阵
			printf("各顶点对的最短路径:\n");
			Floyd(G2);
			break;
		}
		case'3':
		{
			system("cls");
			//采用邻接矩阵储存无向带权图G2对应的数组
			MatGraph G3;
			int A[MAXV][MAXV]={
				{0,28,INF,INF,INF,10,INF},
				{28,0,16,INF,INF,INF,14},
				{INF,16,0,12,INF,INF,INF},
				{INF,INF,12,0,22,INF,18},
				{INF,INF,INF,22,0,25,24},
				{10,INF,INF,INF,25,0,INF},
				{INF,14,INF,18,24,INF,0}};
			int n=7, e=9;
			CreateMat(G3,A,n,e);			//建立《教程》中图8.27的邻接矩阵
			printf("图G的邻接矩阵:\n");
			DispMat(G3);					//输出邻接矩阵
			cout << endl;
			int v=0;
			printf("Prim算法结果(起始点为%d)\n",v);
			Prim(G3,v);
			cout << endl;
			printf("Kruskal算法结果\n");
			Kruskal(G3);
		}
		case'4':
			break;
		default:
			break;
		}

		if (choice == '4')
			break;
		system("pause");
		system("cls");
	}
}