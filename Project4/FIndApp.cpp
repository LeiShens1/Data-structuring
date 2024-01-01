#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<string.h>
#include"Find&Sort.h"
using namespace std;

stu students_list[MAX_stus];//定义全体学生的结构体数组

int main()
{
	int n = 100;
	SqList* L;
	Readf1(students_list);
	CreateList(L, students_list, n);
	while (1)
	{
		cout << "*********************************************" << endl;
		cout << "*       1.读入并随机选取100个学生数据       *" << endl;
		cout << "*       2.对总评成绩进行快速排序            *" << endl;
		cout << "*       3.对总评成绩进行归并排序            *" << endl;
		cout << "*       4.对学生数据进行哈希查找            *" << endl;
		cout << "*       5.对学生数据进行二分查找            *" << endl;
		cout << "*       6.对学生数据进行线性查找            *" << endl;
		cout << "*       0.退出                              *" << endl;
		cout << "*********************************************" << endl;
		cout << "请输入您的选择（0--5）" << endl;
		int choice;
		cin >> choice;
		switch (choice){
		case 0:
			goto END;
			break;
		case 1:
		{
			if (Readf1(students_list))
				cout << "文件读取成功" << endl;
			else
				cout << "文件读取失败" << endl;					//随机选区的数据个数
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
			int ht_num = 0;//记录哈希表中元素个数
			int ht_space = 101;//哈希表容量
			int p = 101; //哈希表取模的值
			CreateHT(ht, ht_num, ht_space, p, L->data, L->length);
			//DispHT(ht, ht_num, ht_space);
			cout << "请输入要寻找同学的学号:";
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
			cout << "请输入要寻找同学的学号:";
			int id;
			cin >> id;
			BSTNode* search;
			search = SearchBST(BST, id);
			if (search != NULL) {
				cout << "成功" << endl;
				cout << "学号：" << setfill('0') << setw(5) << search->key.student_id << endl;
				int name_length = sizeof(search->key.student_name) / sizeof(search->key.student_name[0]);
				cout << "姓名：";
				for (int j = 0; j < name_length; j++)
					cout << search->key.student_name[j];
				cout << endl;
				cout << "专业：" << setfill('0') << setw(2) << search->key.major_num << endl;
				cout << "分数：";
				for (int j = 0; j < 8; j++)
					cout << search->key.score[j] << "  ";
				cout << endl;
				cout << "总评：" << fixed << setprecision(1) << search->key.final_score;
				cout << endl;
			}
			else
				cout << "查找失败" << endl;
			DestroyBST(BST);
			break;
		}
		case 6:
		{
			cout << "请输入要寻找同学的学号:";
			int id;
			cin >> id;
			int i;
			for ( i = 0; i < L->length; i++) {
				if (L->data[i].student_id == id)
					break;
			}
			if (i < L->length) {
				cout << "成功" << endl;
				cout << "学号：" << setfill('0') << setw(5) << L->data[i].student_id << endl;
				int name_length = sizeof(L->data[i].student_name) / sizeof(L->data[i].student_name[0]);
				cout << "姓名：";
				for (int j = 0; j < name_length; j++)
					cout << L->data[i].student_name[j];
				cout << endl;
				cout << "专业：" << setfill('0') << setw(2) << L->data[i].major_num << endl;
				cout << "分数：";
				for (int j = 0; j < 8; j++)
					cout << L->data[i].score[j] << "  ";
				cout << endl;
				cout << "总评：" << fixed << setprecision(1) << L->data[i].final_score;
				cout << endl;
				cout << "成功查找次数ASL=50" << endl;
				cout << "不成功情况下ASL=100" << endl;
			}
			else
				cout << "查找失败" << endl;
				cout << "成功查找次数ASL=50" << endl;
				cout << "不成功情况下ASL=100" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	}
END:
	cout << "感谢您的使用，再见" << endl;
	DestroyList(L);
	system("pause");
	return 0;
}
