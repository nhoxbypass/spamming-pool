// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Bellman.h"

using namespace std;

graph g;
int LastV[MAX]; //chi so dinh nam truoc dinh i tren duong di
//ngan nhat tu x toi i
int dau, cuoi;
int P_truoc[MAX], P_hientai[MAX];

int main()
{
	dau = 2;
	cuoi = 1;

	cout << "  Nhap dinh dau (x): ";
	cin >> dau;
	cout << "  Nhap dinh cuoi (y): ";
	cin >> cuoi;
	cout << endl;

	nhapTuFile("dt.txt");
	int ketqua = DuongDiNganNhat_Bellman(dau);
	// xuat duong di nhan nhat
	if (ketqua == true)
	{
		xuatDuongDi();
		xuatFile("output.txt");
	}
	else
	{
		printf("ton tai mach am! \n");
	}

	system("pause");
	return 0;
}

