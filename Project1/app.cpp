#include"LinkNode.h"
#include<iostream>
#include<string>
using namespace std;
int main() {
	int choice;
	LinkNode *L;
	Readf1(L);						//建立线性表
	while (1){
		cout << "1.输出名单" << endl;
		cout << "2.插入学生" << endl;
		cout << "3.求结点前驱" << endl;
		cout << "4.删除结点" << endl;
		cout << "5.总评排序" << endl;
		cin >> choice;
		system("cls");
		switch (choice){
		case 1:
			DispList(L);			//输出线性表
			break;
		case 2: {
			int i;					//插入位置
			ElemType e;				//插入学生
			string ID;				//学生ID
			string name;			//学生姓名	
			string pro_num;			//学生专业
			cout << "请输入插入位置：" << endl;
			cin >> i;
			cout << "请输入ID：" << endl;
			cin >> ID;
			for (int i = 0; i < ID.size(); i++) 
				e.ID[i] = ID[i];
			cout << "请输入姓名：" << endl;
			cin >> name;
			for (int i = 0; i < name.size(); i++) 
				e.name[i] = name[i];
			cout << "请输入专业编号：" << endl;
			cin >> pro_num;
			for (int i = 0; i < pro_num.size(); i++)
				e.pro_number[i] = pro_num[i];
			cout << "请依次输入通识教育课，公共基础课，专业主干课的成绩：" << endl;
			cin >> e.GEC1 >> e.GEC2>>e.GEC3>>e.PEC1>>e.PEC2>>e.PEC3>>e.CaIC1>>e.CaIC2;
			e.weights = 0.8 * (e.PEC1 + e.PEC2 + e.PEC3) + 1.2 * (e.CaIC1 + e.CaIC2);
			if (ListInsert(L, i, e))
				cout << "插入成功" << endl;
			else
				cout << "插入失败" << endl;
			break;
			}
		case 3: {
			int i;
			cout << "请输入要查找的位置：";
			cin >> i;
			FindandShow(L, i-1);
			break;
		}
		case 4: {
			int i;
			cout << "请输入要删除的位置：";
			cin >> i;
			ElemType e;
			FindandShow(L, i);
			char is_delete;
			cout << "确认删除该信息？Y/N" << endl;
			cin >> is_delete;
			if (is_delete == 'Y' || is_delete == 'y')
				ListDelete(L, i, e);
			else if (is_delete == 'N' || is_delete == 'n')
				cout << "已取消" << endl;	break;
			cout << "已删除" << endl;
			break;
		}
		case 5: {
			sort(L);
			DispList(L);
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	}
}