#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<string.h>
#include"Find&Sort.h"
using namespace std;

stu students_list[MAX_stus];//����ȫ��ѧ���Ľṹ������

int main()
{
	int n = 100;
	SqList* L;
	Readf1(students_list);
	CreateList(L, students_list, n);
	while (1)
	{
		cout << "*********************************************" << endl;
		cout << "*       1.���벢���ѡȡ100��ѧ������       *" << endl;
		cout << "*       2.�������ɼ����п�������            *" << endl;
		cout << "*       3.�������ɼ����й鲢����            *" << endl;
		cout << "*       4.��ѧ�����ݽ��й�ϣ����            *" << endl;
		cout << "*       5.��ѧ�����ݽ��ж��ֲ���            *" << endl;
		cout << "*       6.��ѧ�����ݽ������Բ���            *" << endl;
		cout << "*       0.�˳�                              *" << endl;
		cout << "*********************************************" << endl;
		cout << "����������ѡ��0--5��" << endl;
		int choice;
		cin >> choice;
		switch (choice){
		case 0:
			goto END;
			break;
		case 1:
		{
			if (Readf1(students_list))
				cout << "�ļ���ȡ�ɹ�" << endl;
			else
				cout << "�ļ���ȡʧ��" << endl;					//���ѡ�������ݸ���
			Show(L->data,n);
			break;
		}
		case 2:
		{
			QuickSort(L->data, 0, 99);
			Show(L->data, n);
			break;
		}
		case 3:
		{
			MergeSortDC(L->data, 0, 99);
			Show(L->data, n);
			break;
		}
		case 4:
		{
			HashTable ht[MaxSize];
			int ht_num = 0;//��¼��ϣ����Ԫ�ظ���
			int ht_space = 101;//��ϣ������
			int p = 101; //��ϣ��ȡģ��ֵ
			CreateHT(ht, ht_num, ht_space, p, L->data, L->length);
			//DispHT(ht, ht_num, ht_space);
			cout << "������ҪѰ��ͬѧ��ѧ��:";
			int id;
			cin >> id;
			SearchHT(ht, p, id);
			DestroyHT(ht, ht_space);
			break;
		}
		case 5:
		{
			BSTNode* BST;
			BST = CreateBST(L->data, L->length);
			//DispBST(BST);
			cout << "������ҪѰ��ͬѧ��ѧ��:";
			int id;
			cin >> id;
			BSTNode* search;
			search = SearchBST(BST, id);
			if (search != NULL) {
				cout << "�ɹ�" << endl;
				cout << "ѧ�ţ�" << setfill('0') << setw(5) << search->key.student_id << endl;
				int name_length = sizeof(search->key.student_name) / sizeof(search->key.student_name[0]);
				cout << "������";
				for (int j = 0; j < name_length; j++)
					cout << search->key.student_name[j];
				cout << endl;
				cout << "רҵ��" << setfill('0') << setw(2) << search->key.major_num << endl;
				cout << "������";
				for (int j = 0; j < 8; j++)
					cout << search->key.score[j] << "  ";
				cout << endl;
				cout << "������" << fixed << setprecision(1) << search->key.final_score;
				cout << endl;
			}
			else
				cout << "����ʧ��" << endl;
			DestroyBST(BST);
			break;
		}
		case 6:
		{
			cout << "������ҪѰ��ͬѧ��ѧ��:";
			int id;
			cin >> id;
			int i;
			for ( i = 0; i < L->length; i++) {
				if (L->data[i].student_id == id)
					break;
			}
			if (i < L->length) {
				cout << "�ɹ�" << endl;
				cout << "ѧ�ţ�" << setfill('0') << setw(5) << L->data[i].student_id << endl;
				int name_length = sizeof(L->data[i].student_name) / sizeof(L->data[i].student_name[0]);
				cout << "������";
				for (int j = 0; j < name_length; j++)
					cout << L->data[i].student_name[j];
				cout << endl;
				cout << "רҵ��" << setfill('0') << setw(2) << L->data[i].major_num << endl;
				cout << "������";
				for (int j = 0; j < 8; j++)
					cout << L->data[i].score[j] << "  ";
				cout << endl;
				cout << "������" << fixed << setprecision(1) << L->data[i].final_score;
				cout << endl;
				cout << "�ɹ����Ҵ���ASL=50" << endl;
				cout << "���ɹ������ASL=100" << endl;
			}
			else
				cout << "����ʧ��" << endl;
				cout << "�ɹ����Ҵ���ASL=50" << endl;
				cout << "���ɹ������ASL=100" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	}
END:
	cout << "��л����ʹ�ã��ټ�" << endl;
	DestroyList(L);
	system("pause");
	return 0;
}
