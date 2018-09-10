// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVLTree.h"


int _tmain(int argc, _TCHAR* argv[])
{
	int choice;
	Node<int> *root = NULL;
	int val;
	do 
	{
		system("cls");

		cout << endl << "\t ---- DOAN HIEU TAM - 1412477 ----" << endl << endl << endl;
		cout << " 1. Nhap cay AVL (mac dinh kieu Int): " << endl;
		cout << " 2. Them mot phan tu." << endl;
		cout << " 3. Xoa phan tu." << endl;
		cout << " 4. Tim kiem. " << endl;
		cout << " 5. Duyet cay " << endl << endl;
		cout << " 0. Ket thuc chuong trinh " << endl << endl;
		cout << "\t-----------------------------------" << endl;

		cout << endl << " --> Nhap lua chon: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:
			root = Node<int>::inputTree(root);
			break;
		case 2:
			cout << " - Nhap phan tu muon them: ";
			cin >> val;
			root = root->Insert(val);
			cout << " Da them..." << endl;
			system("pause");
			break;
		case 3:
			cout << " - Nhap phan tu muon xoa: ";
			cin >> val;
			root = root->deleteNode(val);
			break;
		case 4:
			cout << " - Nhap phan tu muon tim kiem: ";
			cin >> val;
			root->searchNode(val)->showNode();
			system("pause");
			break;
		case 5:
			cout << " - Duyet cay truoc (Pre-Order): " << endl << "   ";
			root->preOrder();
			cout << endl << endl;

			cout << " - Duyet cay giua (In-Order): " << endl << "   ";
			root->inOrder();
			cout << endl << endl;

			cout << " - Duyet cay sau (Post-Order): " << endl << "   ";
			root->postOrder();
			cout << endl << endl;
			system("pause");
			break;

		case 0:
			exit(0);
			break;
		}
	} while (1);
	
	

	system("pause");
	return 0;
}

