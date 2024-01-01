#include"Find&Sort.h"

bool Readf1(stu list[])								//读入函数，传入数组首地址
{
	ifstream ifs;									//定义文件流ifs
	ifs.open("f1.txt", ios::in);					//打开文件流
	char judge1;									//定义开关字符，判断是否读完文件
	for (long long i = 0; ifs >> judge1; i++)		//循环读入
	{
		ifs.putback(judge1);						//放回判断字符
		//获取学号
		double id;
		ifs >> id;									//学号定义为int类型，可以直接>>
		list[i].student_id = id;
		//获取姓名
		char ch;
		ifs.get();									//跳过id与姓名中间的空格
		//循环读取字符直到' '结束
		for (int k = 0; (ch = ifs.get()) != ' '; k++)//逐个获取名字中的字符
			list[i].student_name[k] = ch;			//读取出的名字存入结构体中
		//获取专业编号
		int num;
		ifs >> num;
		list[i].major_num = num;
		//获取成绩
		for (int p = 0; p < 8; p++)					//八次循环读取所有成绩
			ifs >> list[i].score[p];
		list[i].final_score = 0.8 * (list[i].score[3] + list[i].score[4] + list[i].score[5]) + 1.2 * (list[i].score[6] + list[i].score[7]);
	}
	char judge;										//创建char类型变量来判断是否读取到了文件尾
	judge = ifs.get();
	if (judge == EOF)
		return true;								//读取到了文件尾，返回true
	else
		cout << "文件读取失败" << endl; return false;//未读取到文件尾，返回false
	ifs.close();

}
void Show(stu list[],int n)							//显示学生数据 
{
	//使用 "\33[4m" 生成下划线，配合 | 实现表格效果
	cout << "\33[4m                                                                                         " << endl;
	cout << "| 学号 |  姓名  | 专业|通识一|通识二|通识三|公共一|公共二|公共三|专业一|专业二|  总 评  |" << endl;
	for (int i = 0; i<n; i++)
	{
		//使用setfill 和 setw 实现格式化输出
		cout << "|" << setfill('0') << setw(5) << list[i].student_id << " | ";
		int name_length = sizeof(list[i].student_name) / sizeof(list[i].student_name[0]);
		for (int j = 0; j < name_length; j++)
			cout << list[i].student_name[j];
		cout << " |  ";
		cout << setfill('0') << setw(2) << list[i].major_num << " | ";
		for (int j = 0; j < 7; j++)
			cout << setfill(' ') << setw(3) << list[i].score[j] << "  | ";
		cout << setfill(' ') << setw(3) << list[i].score[7] << "  |";
		cout <<"  " << fixed << setprecision(1) << list[i].final_score << "  |";
		cout << endl;
	}
	cout << "\33[0m" << endl;
}

void CreateList(SqList*& L, ElemType a[], int n)   //建立随机顺序表
{
	srand(time(nullptr));
	int min = 1, max = 40;
	int randome= (rand() % (max - min + 1)) + min;	//范围[min,max]
	int i = 0, k = 0;
	L = new SqList;
	for (int i = 0; i < n; i++,k+= randome)
		L->data[i] = a[k];
	L->length = n;
}
void DestroyList(SqList*& L)
{
	//先释放数据空间
	free(L->data);
	//再释放顺序栈结构体空间
	free(L);
}

//快速排序算法
int partition(ElemType R[], int s, int t)	//一趟划分
{
	int i = s, j = t;
	ElemType tmp = R[i];					//以R[i]为基准
	while (i < j)  							//从两端交替向中间扫描,直至i=j为止
	{	
		while (j > i && R[j].final_score >= tmp.final_score)
			j--;							//从右向左扫描,找一个小于tmp.key的R[j]
		R[i] = R[j];						//找到这样的R[j],放入R[i]处
		while (i < j && R[i].final_score <= tmp.final_score)
			i++;							//从左向右扫描,找一个大于tmp.key的R[i]
		R[j] = R[i];						//找到这样的R[i],放入R[j]处
	}
	R[i] = tmp;
	return i;
}
void QuickSort(ElemType R[], int s, int t)	//对R[s..t]的元素进行快速排序
{
	int i;
	if (s < t) 								//区间内至少存在两个元素的情况
	{
		i = partition(R, s, t);
		QuickSort(R, s, i - 1);				//对左区间递归排序
		QuickSort(R, i + 1, t);				//对右区间递归排序
	}
}

//自顶向下的二路归并排序算法
void Merge(ElemType R[], int low, int mid, int high)
{
	ElemType* R1;
	int i = low, j = mid + 1, k = 0; //k是R1的下标,i、j分别为第1、2段的下标
	R1 = (ElemType*)malloc((high - low + 1) * sizeof(ElemType));  //动态分配空间
	while (i <= mid && j <= high)     	//在第1段和第2段均未扫描完时循环
		if (R[i].final_score <= R[j].final_score)    	//将第1段中的记录放入R1中
		{
			R1[k] = R[i];
			i++; k++;
		}
		else                       		//将第2段中的记录放入R1中
		{
			R1[k] = R[j];
			j++; k++;
		}
	while (i <= mid)          	       	//将第1段余下部分复制到R1
	{
		R1[k] = R[i];
		i++; k++;
	}
	while (j <= high)                	//将第2段余下部分复制到R1
	{
		R1[k] = R[j];
		j++; k++;
	}
	for (k = 0, i = low; i <= high; k++, i++) //将R1复制回R中
		R[i] = R1[k];
}

void MergeSortDC(ElemType R[], int low, int high)//对R[low..high]进行二路归并排序
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		MergeSortDC(R, low, mid);
		MergeSortDC(R, mid + 1, high);
		Merge(R, low, mid, high);
	}
}
void InsertHT(HashTable ha[], int& n, int p, KeyType k)  //将关键字k插入到哈希表中
{
	int adr;
	adr = k.student_id % p;		//计算哈希函数值
	NodeType* q;
	q = (NodeType*)malloc(sizeof(NodeType));
	q->key = k;					//创建一个结点q，存放关键字k
	q->next = NULL;
	if (ha[adr].firstp == NULL)	//若单链表adr为空
		ha[adr].firstp = q;
	else						//若单链表adr不空
	{
		q->next = ha[adr].firstp;	//采用头插法插入到ha[adr]的单链表中
		ha[adr].firstp = q;
	}
	n++;						//结点总个数增1
}
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int n1)  //创建哈希表
{
	for (int i = 0; i < m; i++)			//哈希表置初值
		ha[i].firstp = NULL;
	n = 0;
	for (int i = 0; i < n1; i++)
		InsertHT(ha, n, p, keys[i]);//插入n个关键字
}
void SearchHT(HashTable ha[], int p, int k)	//在哈希表中查找关键字k
{
	int i = 0, adr;
	adr = k % p;					//计算哈希函数值
	NodeType* q;
	q = ha[adr].firstp;			//q指向对应单链表的首结点
	while (q != NULL)				//扫描单链表adr的所有结点
	{
		i++;
		if (q->key.student_id == k)			//查找成功
			break;				//退出循环
		q = q->next;
	}
	if (q != NULL) {				//查找成功
		cout << "成功" << endl;
		cout <<"学号：" << setfill('0') << setw(5) << q->key.student_id << endl;
		int name_length = sizeof(q->key.student_name) / sizeof(q->key.student_name[0]);
		cout << "姓名：";
		for (int j = 0; j < name_length; j++)
			cout << q->key.student_name[j];
		cout << endl;
		cout << "专业：" << setfill('0') << setw(2) << q->key.major_num << endl;
		cout << "分数：";
		for (int j = 0; j < 8; j++)
			cout  << q->key.score[j] << "  ";
		cout << endl;
		cout << "总评：" << fixed << setprecision(1) << q->key.final_score;
		cout << endl;

	}
	else						//查找失败
		printf("失败：学号%d，比较%d次\n", k, i);
}

void DispHT(HashTable ha[], int n, int m)  //输出哈希表
{
	int succ = 0, unsucc = 0, s;
	NodeType* q;
	for (int i = 0; i < m; i++)		//扫描所有哈希表地址空间
	{
		s = 0;
		printf(" %3d:\t", i);
		q = ha[i].firstp;			//q指向单链表i的首结点
		while (q != NULL)			//扫描单链表i的所有结点
		{
			cout << setfill('0') << setw(5) << q->key.student_id<<'\t';
			q = q->next;
			s++;				//s记录当前结点是对应单链表的第几个结点
			succ += s;			//累计成功的总比较次数
		}
		unsucc += s;				//累计不成功的总比较次数
		printf("\n");
	}
	printf(" 成功情况下ASL(%d)=%g\n", n, succ * 1.0 / n);
	printf(" 不成功情况下ASL(%d)=%g\n", n, unsucc * 1.0 / m);
}

void DestroyHT(HashTable ha[], int m)	//销毁哈希表
{
	int i;
	NodeType* q, * preq;
	for (i = 0; i < m; i++)
	{
		q = ha[i].firstp;			//q指向单链表i的首结点
		while (q != NULL)			//扫描单链表i的所有结点
		{
			preq = q; q = q->next;
			free(preq);
		}
	}
}

bool InsertBST(BSTNode*& bt, KeyType k)
//在二叉排序树bt中插入一个关键字为k的结点。插入成功返回真，否则返回假
{
	if (bt == NULL)						//原树为空，新插入的结点为根结点
	{
		bt = (BSTNode*)malloc(sizeof(BSTNode));
		bt->key = k; bt->lchild = bt->rchild = NULL;
		return true;
	}
	else if (k.student_id == bt->key.student_id) 				//树中存在相同关键字的结点，返回假
		return false;
	else if (k.student_id < bt->key.student_id)
		return InsertBST(bt->lchild, k);	//插入到左子树中
	else
		return InsertBST(bt->rchild, k);	//插入到右子树中
}

BSTNode* CreateBST(KeyType A[], int n)		//创建二叉排序树
//返回BST树根结点指针
{
	BSTNode* bt = NULL;				//初始时bt为空树
	int i = 0;
	while (i < n)
	{
		InsertBST(bt, A[i]);			//将关键字A[i]插入二叉排序树bt中
		i++;
	}
	return bt;						//返回建立的二叉排序树的根指针
}

void DispBST(BSTNode* bt)		//输出一棵排序二叉树
{
	if (bt != NULL)
	{
		printf("%d", bt->key.student_id);
		if (bt->lchild != NULL || bt->rchild != NULL)
		{
			printf("(");						//有孩子结点时才输出(
			DispBST(bt->lchild);				//递归处理左子树
			if (bt->rchild != NULL) printf(",");	//有右孩子结点时才输出,
			DispBST(bt->rchild);				//递归处理右子树
			printf(")");						//有孩子结点时才输出)
		}
	}
}
BSTNode* SearchBST(BSTNode* bt, int k)
{
	if (bt == NULL)
	{
		return(NULL);
	}
	else if (bt->key.student_id == k)      	//递归终结条件
		return bt;
	if (k < bt->key.student_id)
		return SearchBST(bt->lchild, k);  //在左子树中递归查找
	else
		return SearchBST(bt->rchild, k);  //在右子树中递归查找
}

void DestroyBST(BSTNode*& bt)		//销毁二叉排序树bt
{
	if (bt != NULL)
	{
		DestroyBST(bt->lchild);
		DestroyBST(bt->rchild);
		free(bt);
	}
}
