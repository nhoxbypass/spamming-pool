// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dijkstra.h"

int T[MAX]; // mãng đánh dấu đỉnh trong T
int Length[MAX]; // độ dài tử đỉnh đầu đến các định trong đồ thị
int Prev[MAX]; // mảng lưu đỉnh liền trước của đường đi

int _tmain(int argc, _TCHAR* argv[])
{
	GRAPH gr;
	int diemdau, diemcuoi;
	int A, B, C, D;

	cout << "\t DOAN HIEU TAM - 1412477 " << endl << endl;

	cout << "Doc du lieu tu tep tin va in ra: " << endl;
	readFromFile("input.txt", gr, diemdau, diemcuoi);
	Dijkstra(gr, diemdau - 1, diemcuoi-1);
	cout << "Duong di ngan nhat tu " << diemdau << " den " << diemcuoi << " la: " << endl;
	ShowPath(diemdau - 1, diemcuoi - 1);
	cout << endl;

	//In vao file
	writeToFile("output.txt", diemdau - 1, diemcuoi - 1);
	
	//Cau 5
	cout << "Nhap dinh A: ";
	cin >> A;
	cout << "Nhap dinh B: ";
	cin >> B;
	cout << "Nhap dinh C: ";
	cin >> C;

	cout << "Duong di ngan nhat tu A -> B ma di qua dinh C la: " << endl;
	goToSpecificPath(gr, A, B, C);
	cout << endl;

	//Cau 6
	cout << "Nhap dinh A: ";
	cin >> A;
	cout << "Nhap dinh B: ";
	cin >> B;
	cout << "Nhap dinh C: ";
	cin >> C;
	cout << "Nhap dinh D: ";
	cin >> D;
	cout << "Duong di ngan nhat tu A -> B ma di qua canh C-D la: " << endl;
	goToSpecificPath(gr, 1, 5, 3, 2);
	cout << endl;

	system("pause");
	return 0;
}

