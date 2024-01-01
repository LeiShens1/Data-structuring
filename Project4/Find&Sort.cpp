#include"Find&Sort.h"

bool Readf1(stu list[])								//���뺯�������������׵�ַ
{
	ifstream ifs;									//�����ļ���ifs
	ifs.open("f1.txt", ios::in);					//���ļ���
	char judge1;									//���忪���ַ����ж��Ƿ�����ļ�
	for (long long i = 0; ifs >> judge1; i++)		//ѭ������
	{
		ifs.putback(judge1);						//�Ż��ж��ַ�
		//��ȡѧ��
		double id;
		ifs >> id;									//ѧ�Ŷ���Ϊint���ͣ�����ֱ��>>
		list[i].student_id = id;
		//��ȡ����
		char ch;
		ifs.get();									//����id�������м�Ŀո�
		//ѭ����ȡ�ַ�ֱ��' '����
		for (int k = 0; (ch = ifs.get()) != ' '; k++)//�����ȡ�����е��ַ�
			list[i].student_name[k] = ch;			//��ȡ�������ִ���ṹ����
		//��ȡרҵ���
		int num;
		ifs >> num;
		list[i].major_num = num;
		//��ȡ�ɼ�
		for (int p = 0; p < 8; p++)					//�˴�ѭ����ȡ���гɼ�
			ifs >> list[i].score[p];
		list[i].final_score = 0.8 * (list[i].score[3] + list[i].score[4] + list[i].score[5]) + 1.2 * (list[i].score[6] + list[i].score[7]);
	}
	char judge;										//����char���ͱ������ж��Ƿ��ȡ�����ļ�β
	judge = ifs.get();
	if (judge == EOF)
		return true;								//��ȡ�����ļ�β������true
	else
		cout << "�ļ���ȡʧ��" << endl; return false;//δ��ȡ���ļ�β������false
	ifs.close();

}
void Show(stu list[],int n)							//��ʾѧ������ 
{
	//ʹ�� "\33[4m" �����»��ߣ���� | ʵ�ֱ��Ч��
	cout << "\33[4m                                                                                         " << endl;
	cout << "| ѧ�� |  ����  | רҵ|ͨʶһ|ͨʶ��|ͨʶ��|����һ|������|������|רҵһ|רҵ��|  �� ��  |" << endl;
	for (int i = 0; i<n; i++)
	{
		//ʹ��setfill �� setw ʵ�ָ�ʽ�����
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

void CreateList(SqList*& L, ElemType a[], int n)   //�������˳���
{
	srand(time(nullptr));
	int min = 1, max = 40;
	int randome= (rand() % (max - min + 1)) + min;	//��Χ[min,max]
	int i = 0, k = 0;
	L = new SqList;
	for (int i = 0; i < n; i++,k+= randome)
		L->data[i] = a[k];
	L->length = n;
}
void DestroyList(SqList*& L)
{
	//���ͷ����ݿռ�
	free(L->data);
	//���ͷ�˳��ջ�ṹ��ռ�
	free(L);
}

//���������㷨
int partition(ElemType R[], int s, int t)	//һ�˻���
{
	int i = s, j = t;
	ElemType tmp = R[i];					//��R[i]Ϊ��׼
	while (i < j)  							//�����˽������м�ɨ��,ֱ��i=jΪֹ
	{	
		while (j > i && R[j].final_score >= tmp.final_score)
			j--;							//��������ɨ��,��һ��С��tmp.key��R[j]
		R[i] = R[j];						//�ҵ�������R[j],����R[i]��
		while (i < j && R[i].final_score <= tmp.final_score)
			i++;							//��������ɨ��,��һ������tmp.key��R[i]
		R[j] = R[i];						//�ҵ�������R[i],����R[j]��
	}
	R[i] = tmp;
	return i;
}
void QuickSort(ElemType R[], int s, int t)	//��R[s..t]��Ԫ�ؽ��п�������
{
	int i;
	if (s < t) 								//���������ٴ�������Ԫ�ص����
	{
		i = partition(R, s, t);
		QuickSort(R, s, i - 1);				//��������ݹ�����
		QuickSort(R, i + 1, t);				//��������ݹ�����
	}
}

//�Զ����µĶ�·�鲢�����㷨
void Merge(ElemType R[], int low, int mid, int high)
{
	ElemType* R1;
	int i = low, j = mid + 1, k = 0; //k��R1���±�,i��j�ֱ�Ϊ��1��2�ε��±�
	R1 = (ElemType*)malloc((high - low + 1) * sizeof(ElemType));  //��̬����ռ�
	while (i <= mid && j <= high)     	//�ڵ�1�κ͵�2�ξ�δɨ����ʱѭ��
		if (R[i].final_score <= R[j].final_score)    	//����1���еļ�¼����R1��
		{
			R1[k] = R[i];
			i++; k++;
		}
		else                       		//����2���еļ�¼����R1��
		{
			R1[k] = R[j];
			j++; k++;
		}
	while (i <= mid)          	       	//����1�����²��ָ��Ƶ�R1
	{
		R1[k] = R[i];
		i++; k++;
	}
	while (j <= high)                	//����2�����²��ָ��Ƶ�R1
	{
		R1[k] = R[j];
		j++; k++;
	}
	for (k = 0, i = low; i <= high; k++, i++) //��R1���ƻ�R��
		R[i] = R1[k];
}

void MergeSortDC(ElemType R[], int low, int high)//��R[low..high]���ж�·�鲢����
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
void InsertHT(HashTable ha[], int& n, int p, KeyType k)  //���ؼ���k���뵽��ϣ����
{
	int adr;
	adr = k.student_id % p;		//�����ϣ����ֵ
	NodeType* q;
	q = (NodeType*)malloc(sizeof(NodeType));
	q->key = k;					//����һ�����q����Źؼ���k
	q->next = NULL;
	if (ha[adr].firstp == NULL)	//��������adrΪ��
		ha[adr].firstp = q;
	else						//��������adr����
	{
		q->next = ha[adr].firstp;	//����ͷ�巨���뵽ha[adr]�ĵ�������
		ha[adr].firstp = q;
	}
	n++;						//����ܸ�����1
}
void CreateHT(HashTable ha[], int& n, int m, int p, KeyType keys[], int n1)  //������ϣ��
{
	for (int i = 0; i < m; i++)			//��ϣ���ó�ֵ
		ha[i].firstp = NULL;
	n = 0;
	for (int i = 0; i < n1; i++)
		InsertHT(ha, n, p, keys[i]);//����n���ؼ���
}
void SearchHT(HashTable ha[], int p, int k)	//�ڹ�ϣ���в��ҹؼ���k
{
	int i = 0, adr;
	adr = k % p;					//�����ϣ����ֵ
	NodeType* q;
	q = ha[adr].firstp;			//qָ���Ӧ��������׽��
	while (q != NULL)				//ɨ�赥����adr�����н��
	{
		i++;
		if (q->key.student_id == k)			//���ҳɹ�
			break;				//�˳�ѭ��
		q = q->next;
	}
	if (q != NULL) {				//���ҳɹ�
		cout << "�ɹ�" << endl;
		cout <<"ѧ�ţ�" << setfill('0') << setw(5) << q->key.student_id << endl;
		int name_length = sizeof(q->key.student_name) / sizeof(q->key.student_name[0]);
		cout << "������";
		for (int j = 0; j < name_length; j++)
			cout << q->key.student_name[j];
		cout << endl;
		cout << "רҵ��" << setfill('0') << setw(2) << q->key.major_num << endl;
		cout << "������";
		for (int j = 0; j < 8; j++)
			cout  << q->key.score[j] << "  ";
		cout << endl;
		cout << "������" << fixed << setprecision(1) << q->key.final_score;
		cout << endl;

	}
	else						//����ʧ��
		printf("ʧ�ܣ�ѧ��%d���Ƚ�%d��\n", k, i);
}

void DispHT(HashTable ha[], int n, int m)  //�����ϣ��
{
	int succ = 0, unsucc = 0, s;
	NodeType* q;
	for (int i = 0; i < m; i++)		//ɨ�����й�ϣ���ַ�ռ�
	{
		s = 0;
		printf(" %3d:\t", i);
		q = ha[i].firstp;			//qָ������i���׽��
		while (q != NULL)			//ɨ�赥����i�����н��
		{
			cout << setfill('0') << setw(5) << q->key.student_id<<'\t';
			q = q->next;
			s++;				//s��¼��ǰ����Ƕ�Ӧ������ĵڼ������
			succ += s;			//�ۼƳɹ����ܱȽϴ���
		}
		unsucc += s;				//�ۼƲ��ɹ����ܱȽϴ���
		printf("\n");
	}
	printf(" �ɹ������ASL(%d)=%g\n", n, succ * 1.0 / n);
	printf(" ���ɹ������ASL(%d)=%g\n", n, unsucc * 1.0 / m);
}

void DestroyHT(HashTable ha[], int m)	//���ٹ�ϣ��
{
	int i;
	NodeType* q, * preq;
	for (i = 0; i < m; i++)
	{
		q = ha[i].firstp;			//qָ������i���׽��
		while (q != NULL)			//ɨ�赥����i�����н��
		{
			preq = q; q = q->next;
			free(preq);
		}
	}
}

bool InsertBST(BSTNode*& bt, KeyType k)
//�ڶ���������bt�в���һ���ؼ���Ϊk�Ľ�㡣����ɹ������棬���򷵻ؼ�
{
	if (bt == NULL)						//ԭ��Ϊ�գ��²���Ľ��Ϊ�����
	{
		bt = (BSTNode*)malloc(sizeof(BSTNode));
		bt->key = k; bt->lchild = bt->rchild = NULL;
		return true;
	}
	else if (k.student_id == bt->key.student_id) 				//���д�����ͬ�ؼ��ֵĽ�㣬���ؼ�
		return false;
	else if (k.student_id < bt->key.student_id)
		return InsertBST(bt->lchild, k);	//���뵽��������
	else
		return InsertBST(bt->rchild, k);	//���뵽��������
}

BSTNode* CreateBST(KeyType A[], int n)		//��������������
//����BST�������ָ��
{
	BSTNode* bt = NULL;				//��ʼʱbtΪ����
	int i = 0;
	while (i < n)
	{
		InsertBST(bt, A[i]);			//���ؼ���A[i]�������������bt��
		i++;
	}
	return bt;						//���ؽ����Ķ����������ĸ�ָ��
}

void DispBST(BSTNode* bt)		//���һ�����������
{
	if (bt != NULL)
	{
		printf("%d", bt->key.student_id);
		if (bt->lchild != NULL || bt->rchild != NULL)
		{
			printf("(");						//�к��ӽ��ʱ�����(
			DispBST(bt->lchild);				//�ݹ鴦��������
			if (bt->rchild != NULL) printf(",");	//���Һ��ӽ��ʱ�����,
			DispBST(bt->rchild);				//�ݹ鴦��������
			printf(")");						//�к��ӽ��ʱ�����)
		}
	}
}
BSTNode* SearchBST(BSTNode* bt, int k)
{
	if (bt == NULL)
	{
		return(NULL);
	}
	else if (bt->key.student_id == k)      	//�ݹ��ս�����
		return bt;
	if (k < bt->key.student_id)
		return SearchBST(bt->lchild, k);  //���������еݹ����
	else
		return SearchBST(bt->rchild, k);  //���������еݹ����
}

void DestroyBST(BSTNode*& bt)		//���ٶ���������bt
{
	if (bt != NULL)
	{
		DestroyBST(bt->lchild);
		DestroyBST(bt->rchild);
		free(bt);
	}
}
