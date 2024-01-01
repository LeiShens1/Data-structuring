#include <iostream>
#include "BinarTree.h"
int main() {
    BTNode* b;
    char data[30];
    //A(B(D(,G)),C(E,F))
    cout << "��ʹ�����ŷ����������" << endl;
    cin >> data;
    CreateBTree(b, data);
    while (true)
    {
        system("cls");
        char choice;
        cout << "1.ԭ�������" << endl;
        cout << "2.˫�׽ڵ�" << endl;
        cout << "3.�������" << endl;
        cout << "4.���߶�" << endl;
        cout << "5.���·��" << endl;
        cout << "6.�˳�" << endl;
        cin >> choice;
        switch (choice) {
        case '1':
        {
            cout << "ԭ�������" << endl;
            DispBTree(b);
            cout << endl;
            system("pause");
            break;
        }
        case '2':
        {
            cout << "������Ҫ���ҵĽ��ֵ��" << endl;
            ElemType find;
            cin >> find;
            if (FindNodeParent(b, find) != NULL)
                cout << "���" << find << "��˫����" << FindNodeParent(b, find)->data << endl;
            else
                cout << "��" << find << "��" << find << "Ϊ���ڵ�" << endl;
            system("pause");
            break;
        }
        case '3':
        {
            cout << "�������";
            PreOrder(b);
            cout << endl;
            cout << "�������";
            InOrder(b);
            cout << endl;
            cout << "�������";
            PostOrder(b);
            cout << endl;
            system("pause");
            break;
        }
        case '4':
        {
            cout << "���������ѯ���" << endl;
            ElemType target;
            cin >> target;
            cout << "�Ľ��߶�Ϊ��" << NodeHeight(b, target) << endl;
            system("pause");
            break;
        }
        case '5':
        {
            ElemType start, end;
            cout << "��������ʼ�ڵ����ֹ��㣺" << endl;
            cin >> start >> end;
            FindWay(b,start, end);
            system("pause");
            break;
        }
        case '6':
            DestroyBTree(b);
            break;

        default:
            break;
        }
        system("cls");
        if (choice == 6)
            break;
    }
    
    //TransTree(b, NewTree);
    //cout << "������" << endl;
    //DispBTree(NewTree);
    return 0;
}
