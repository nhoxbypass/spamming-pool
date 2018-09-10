#pragma once

#define MAX 100
#define VoCuc 32767

using namespace std;
//
//Bellman chấp nhận cạnh âm, không the sử dụng trị -1.
//sử dụng trị MAXINT (32767) cho giá trị VoCuc
//

struct graph
{
	int n;
	int a[MAX][MAX];
};

extern graph g;
extern int LastV[MAX]; //chi so dinh nam truoc dinh i tren duong di
//ngan nhat tu x toi i
extern int dau, cuoi;
// dòng trước và dòng hiện tại của ma trận P
extern int P_truoc[MAX], P_hientai[MAX];

void nhapTuFile(string duongdan);

bool DuongDiNganNhat_Bellman(int dinhDau);

void inDoDai(int dinhDau);

void xuatDuongDi();

void xuatFile(string path); //Xuat duong di tu dau->cuoi ra file