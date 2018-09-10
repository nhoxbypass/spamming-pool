#pragma once


#include "stdio.h"
#include "conio.h"
#include <fstream>


#define MAX 100
#define INF -1
//cau truc do thi
typedef struct
{
	int n;
	int L[MAX][MAX];
} GRAPH;

//Bien toan cuc
extern int T[MAX]; // mãng đánh dấu đỉnh trong T
extern int Length[MAX]; // độ dài tử đỉnh đầu đến các định trong đồ thị
extern int Prev[MAX]; // mảng lưu đỉnh liền trước của đường đi

//Doc file va luu vao ma tran, kem theo diem dau, diem cuoi
void readFromFile(string path, GRAPH &g, int& diemdau, int& diemcuoi);


//Khoi tao cac gia tri mac dinh cua thuat toan
//Gan T:=X
// Length[x]=0; Length[k]=+vocuc, voi moi k thuoc X\{x}
//Prev[k]=-1, voi moi k thuoc X\{x}
void Init(GRAPH g, int dinhdau, int dinhcuoi);

//Thuat toan 
bool Dijkstra(GRAPH g, int dinhdau, int dinhcuoi);

//In nguoc tu dinh cuoi <-- dinh dau
void ShowPath(int dinhdau, int dinhcuoi);

//Luu vao file
void writeToFile(string path, int dinhdau, int dinhcuoi);

//Cau 5
void goToSpecificPath(GRAPH g, int A, int B, int C);

//Cau 6
void goToSpecificPath(GRAPH g, int A, int B, int C, int D);