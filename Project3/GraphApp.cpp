#include <iostream>
#include"Graph.h"
using namespace std;

//�ڽӾ�����ڽӱ���໥ת��
static void MatToList(MatGraph g, AdjGraph*& G)		//���ڽӾ���gת�����ڽӱ�G
{
	int i, j;
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < g.n; i++)				//���ڽӱ�������ͷ����ָ�����ó�ֵ
		G->adjlist[i].firstarc = NULL;
	for (i = 0; i < g.n; i++)				//����ڽӾ�����ÿ��Ԫ��
	{
		for (j = g.n - 1; j >= 0; j--)
		{
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)	//����һ����
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));	//����һ���߽��p
				p->adjvex = j; p->weight = g.edges[i][j];
				p->nextarc = G->adjlist[i].firstarc;		//����ͷ�巨������p
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = g.n; G->e = g.e;
}

//������ȱ����㷨
static void BFS(AdjGraph* G, int v)
{
	int w, i;
	ArcNode* p;
	SqQueue* qu;							//���廷�ζ���ָ��
	InitQueue(qu);							//��ʼ������
	int visited[MAXV];            			//���嶥����ʱ�־����
	for (i = 0; i < G->n; i++) visited[i] = 0;		//���ʱ�־�����ʼ��
	printf("%2d", v); 						//��������ʶ���ı��
	visited[v] = 1;              				//���ѷ��ʱ��
	enQueue(qu, v);
	while (!QueueEmpty(qu))       			//�Ӳ���ѭ��
	{
		deQueue(qu, w);						//����һ������w
		p = G->adjlist[w].firstarc; 			//ָ��w�ĵ�һ���ڽӵ�
		while (p != NULL)						//����w�������ڽӵ�
		{
			if (visited[p->adjvex] == 0) 		//����ǰ�ڽӵ�δ������
			{
				printf("%2d", p->adjvex);  	//���ʸ��ڽӵ�
				visited[p->adjvex] = 1;		//���ѷ��ʱ��
				enQueue(qu, p->adjvex);		//�ö������
			}
			p = p->nextarc;              		//����һ���ڽӵ�
		}
	}
	printf("\n");
}

//������ȱ����㷨
int visited[MAXV] = { 0 };            	//���嶥����ʱ�־����
static void DFS(AdjGraph *G,int v)  
{
	ArcNode *p;
	visited[v]=1;                   //���ѷ��ʱ��
	printf("%2d",v); 				//��������ʶ���ı��
	p=G->adjlist[v].firstarc;      	//pָ�򶥵�v�ĵ�һ�����Ļ�ͷ���
	while (p!=NULL) 
	{
		if (visited[p->adjvex]==0)	//��p->adjvex����δ����,�ݹ������
			DFS(G,p->adjvex);    
		p=p->nextarc;              	//pָ�򶥵�v����һ�����Ļ�ͷ���
	}
}

//Floyd�㷨
static void DispathFloyd(MatGraph g, int A[][MAXV], int path[][MAXV])
{
	int i, j, k, s;
	int apath[MAXV], d;		//���һ�����·���м䶥��(����)���䶥�����
	for (i = 0; i < g.n; i++)
		for (j = 0; j < g.n; j++)
		{
			if (A[i][j] != INF && i != j)			//������i��j֮�����·��
			{
				printf("  ��%d��%d��·��Ϊ:", i, j);
				k = path[i][j];
				d = 0; apath[d] = j;				//·��������յ�
				while (k != -1 && k != i)			//·��������м��
				{
					d++; apath[d] = k;
					k = path[i][k];
				}
				d++; apath[d] = i;				//·����������
				printf("%d", apath[d]);			//������
				for (s = d - 1; s >= 0; s--)			//���·���ϵ��м䶥��
					printf(",%d", apath[s]);
				printf("\t·������Ϊ:%d\n", A[i][j]);
			}
		}
}
static void Floyd(MatGraph g)							//Floyd�㷨
{
	int A[MAXV][MAXV], path[MAXV][MAXV];
	int i, j, k;
	for (i = 0; i < g.n; i++)
	{
		for (j = 0; j < g.n; j++)
		{
			A[i][j] = g.edges[i][j];
			if (i != j && g.edges[i][j] < INF)
				path[i][j] = i;					//����i��j�б�ʱ
			else
				path[i][j] = -1;				//����i��jû�б�ʱ
		}
	}
	for (k = 0; k < g.n; k++)						//���ο������ж���
	{
		for (i = 0; i < g.n; i++)
		{
			for (j = 0; j < g.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])
				{
					A[i][j] = A[i][k] + A[k][j];	//�޸����·������
					path[i][j] = path[k][j];		//�޸����·��
				}
			}
		}
	}
	DispathFloyd(g, A, path);							//������·��
}

//Prim�㷨
static void Prim(MatGraph g, int v)
{
	int lowcost[MAXV];			//����i�Ƿ���U��
	int min;
	int closest[MAXV], i, j, k;
	for (i = 0; i < g.n; i++)          //��lowcost[]��closest[]�ó�ֵ
	{
		lowcost[i] = g.edges[v][i];
		closest[i] = v;
	}
	for (i = 1; i < g.n; i++)          //�ҳ�n-1������
	{
		min = INF;
		for (j = 0; j < g.n; j++)       //��(V-U)���ҳ���U����Ķ���k
			if (lowcost[j] != 0 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;			//k��¼�������ı��
			}
		printf(" ��(%d,%d)ȨΪ:%d\n", closest[k], k, min);
		lowcost[k] = 0;         	//���k�Ѿ�����U
		for (j = 0; j < g.n; j++)   	//�޸�����lowcost��closest
			if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.edges[k][j];
				closest[j] = k;
			}
	}
}
//Kruskal�㷨
static void InsertSort(Edge E[], int n) //��E[0..n-1]�������������ֱ�Ӳ�������
{
	int i, j;
	Edge temp;
	for (i = 1; i < n; i++)
	{
		temp = E[i];
		j = i - 1;				//����������������E[0..i-1]����E[i]�Ĳ���λ��
		while (j >= 0 && temp.w < E[j].w)
		{
			E[j + 1] = E[j];	//���ؼ��ִ���E[i].w�ļ�¼����
			j--;
		}
		E[j + 1] = temp;		//��j+1������E[i] 
	}
}
static void Kruskal(MatGraph g)
{
	int i, j, u1, v1, sn1, sn2, k;
	int vset[MAXV];
	Edge E[MaxSize];				//������б�
	k = 0;							//E������±��0��ʼ��
	for (i = 0; i < g.n; i++)				//��g�����ı߼�E
		for (j = 0; j <= i; j++)
		{
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF)
			{
				E[k].u = i; E[k].v = j; E[k].w = g.edges[i][j];
				k++;
			}
		}
	InsertSort(E, g.e);				//����ֱ�Ӳ��������E���鰴Ȩֵ��������
	for (i = 0; i < g.n; i++) 			//��ʼ����������
		vset[i] = i;
	k = 1;                 			//k��ʾ��ǰ�����������ĵڼ�����,��ֵΪ1
	j = 0;                 			//E�бߵ��±�,��ֵΪ0
	while (k < g.n)       			//���ɵı���С��nʱѭ��
	{
		u1 = E[j].u; v1 = E[j].v;        //ȡһ���ߵ�ͷβ����
		sn1 = vset[u1];
		sn2 = vset[v1]; 				//�ֱ�õ��������������ļ��ϱ��
		if (sn1 != sn2)     	  		//���������ڲ�ͬ�ļ���,�ñ�����С��������һ����
		{
			printf(" ��(%d,%d)ȨΪ:%d\n", u1, v1, E[j].w);
			k++;                    //���ɱ�����1
			for (i = 0; i < g.n; i++)     //��������ͳһ���
				if (vset[i] == sn2)  	//���ϱ��Ϊsn2�ĸ�Ϊsn1
					vset[i] = sn1;
		}
		j++;   						//ɨ����һ����
	}
}

int main() {
	char choice;
	while (1) {
		cout << "1.ͼ�ı���" << endl;
		cout << "2.���·��" << endl;
		cout << "3.��С������" << endl;
		cout << "4.�˳�����" << endl;
		cin >> choice;
		switch (choice){
		case'1': 
		{
			system("cls");
			//�����ڽӾ��󴢴�ͼG1��Ӧ������
			int A1[MAXV][MAXV] =
			{
				{0,1,0,1,1},
				{1,0,1,1,0},
				{0,1,0,1,1},
				{1,1,1,0,1},
				{1,0,1,1,0}
			};
			cout << "��Ȩ����ͼG1��" << endl;
			cout << "  1  " << endl
				 << " /|\\ " << endl
				 << "2-3-0" << endl
				 << " \\|/ " << endl
				 << "  4  " << endl;
			//ͼ�Ĺ���
			MatGraph G1;
			AdjGraph *g1;
			CreateMat(G1, A1, 5, 8);
			cout << "G1���ڽӾ��������" << endl;
			DispMat(G1);
			cout << endl;
			//ͼ�Ĺ�����ȱ���
			MatToList(G1,g1);//���ڽӾ���ת��Ϊ�ڽӱ�
			cout << "G1�Ĺ�����ȱ��������Ϊ2��:" << endl;
			BFS(g1, 2);
			cout << "G1��������ȱ��������Ϊ2��:" << endl;
			DFS(g1, 2);
			cout << endl;
			DestroyAdj(g1);
			break;
		}
		case'2':
		{	
			system("cls");
			//�����ڽӾ��󴢴������ȨͼG2��Ӧ������
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
			CreateMat(G2,A,n,e);			//�������̡̳���ͼ8.35���ڽӾ���
			printf("ͼG2���ڽӾ���:\n");
			DispMat(G2);					//����ڽӾ���
			printf("������Ե����·��:\n");
			Floyd(G2);
			break;
		}
		case'3':
		{
			system("cls");
			//�����ڽӾ��󴢴������ȨͼG2��Ӧ������
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
			CreateMat(G3,A,n,e);			//�������̡̳���ͼ8.27���ڽӾ���
			printf("ͼG���ڽӾ���:\n");
			DispMat(G3);					//����ڽӾ���
			cout << endl;
			int v=0;
			printf("Prim�㷨���(��ʼ��Ϊ%d)\n",v);
			Prim(G3,v);
			cout << endl;
			printf("Kruskal�㷨���\n");
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