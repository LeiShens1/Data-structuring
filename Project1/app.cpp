#include"LinkNode.h"
#include<iostream>
#include<string>
using namespace std;
int main() {
	int choice;
	LinkNode *L;
	Readf1(L);						//�������Ա�
	while (1){
		cout << "1.�������" << endl;
		cout << "2.����ѧ��" << endl;
		cout << "3.����ǰ��" << endl;
		cout << "4.ɾ�����" << endl;
		cout << "5.��������" << endl;
		cin >> choice;
		system("cls");
		switch (choice){
		case 1:
			DispList(L);			//������Ա�
			break;
		case 2: {
			int i;					//����λ��
			ElemType e;				//����ѧ��
			string ID;				//ѧ��ID
			string name;			//ѧ������	
			string pro_num;			//ѧ��רҵ
			cout << "���������λ�ã�" << endl;
			cin >> i;
			cout << "������ID��" << endl;
			cin >> ID;
			for (int i = 0; i < ID.size(); i++) 
				e.ID[i] = ID[i];
			cout << "������������" << endl;
			cin >> name;
			for (int i = 0; i < name.size(); i++) 
				e.name[i] = name[i];
			cout << "������רҵ��ţ�" << endl;
			cin >> pro_num;
			for (int i = 0; i < pro_num.size(); i++)
				e.pro_number[i] = pro_num[i];
			cout << "����������ͨʶ�����Σ����������Σ�רҵ���ɿεĳɼ���" << endl;
			cin >> e.GEC1 >> e.GEC2>>e.GEC3>>e.PEC1>>e.PEC2>>e.PEC3>>e.CaIC1>>e.CaIC2;
			e.weights = 0.8 * (e.PEC1 + e.PEC2 + e.PEC3) + 1.2 * (e.CaIC1 + e.CaIC2);
			if (ListInsert(L, i, e))
				cout << "����ɹ�" << endl;
			else
				cout << "����ʧ��" << endl;
			break;
			}
		case 3: {
			int i;
			cout << "������Ҫ���ҵ�λ�ã�";
			cin >> i;
			FindandShow(L, i-1);
			break;
		}
		case 4: {
			int i;
			cout << "������Ҫɾ����λ�ã�";
			cin >> i;
			ElemType e;
			FindandShow(L, i);
			char is_delete;
			cout << "ȷ��ɾ������Ϣ��Y/N" << endl;
			cin >> is_delete;
			if (is_delete == 'Y' || is_delete == 'y')
				ListDelete(L, i, e);
			else if (is_delete == 'N' || is_delete == 'n')
				cout << "��ȡ��" << endl;	break;
			cout << "��ɾ��" << endl;
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