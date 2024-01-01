#include <iostream>
#include "BinarTree.h"
int main() {
    BTNode* b;
    char data[30];
    //A(B(D(,G)),C(E,F))
    cout << "请使用括号法输入二叉树" << endl;
    cin >> data;
    CreateBTree(b, data);
    while (true)
    {
        system("cls");
        char choice;
        cout << "1.原树输出：" << endl;
        cout << "2.双亲节点" << endl;
        cout << "3.遍历输出" << endl;
        cout << "4.结点高度" << endl;
        cout << "5.结点路径" << endl;
        cout << "6.退出" << endl;
        cin >> choice;
        switch (choice) {
        case '1':
        {
            cout << "原树输出：" << endl;
            DispBTree(b);
            cout << endl;
            system("pause");
            break;
        }
        case '2':
        {
            cout << "请输入要查找的结点值：" << endl;
            ElemType find;
            cin >> find;
            if (FindNodeParent(b, find) != NULL)
                cout << "结点" << find << "的双亲是" << FindNodeParent(b, find)->data << endl;
            else
                cout << "无" << find << "或" << find << "为根节点" << endl;
            system("pause");
            break;
        }
        case '3':
        {
            cout << "先序遍历";
            PreOrder(b);
            cout << endl;
            cout << "中序遍历";
            InOrder(b);
            cout << endl;
            cout << "后序遍历";
            PostOrder(b);
            cout << endl;
            system("pause");
            break;
        }
        case '4':
        {
            cout << "请输入带查询结点" << endl;
            ElemType target;
            cin >> target;
            cout << "改结点高度为：" << NodeHeight(b, target) << endl;
            system("pause");
            break;
        }
        case '5':
        {
            ElemType start, end;
            cout << "请输入起始节点和终止结点：" << endl;
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
    //cout << "新树：" << endl;
    //DispBTree(NewTree);
    return 0;
}
