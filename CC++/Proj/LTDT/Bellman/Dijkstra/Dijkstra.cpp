#include "stdafx.h"
using namespace std;

#define MAX 100
#define VoCuc  -1

struct graph
{
	int n;
	int a[MAX][MAX];
};

graph g; //<1> bien toan cuc chua ma tran ke
bool ThuocT[MAX]; //<2> mang luu dinh i lay ra
int Length[MAX]; //<3> luu do dai duong di cho den dinh thu i 
int LastV[MAX]; //<4> luu dinh truoc ke no tren duong di
int x,y;

void nhapTuFile(string duongdan)
{
	ifstream fileDauVao;
	fileDauVao.open(duongdan);

	fileDauVao >> g.n;

	for (int i = 0; i < g.n; i++)
	{
		for (int j = 0; j < g.n; j++)
		{
			fileDauVao >> g.a[i][j];
		}
	}

	fileDauVao.close();
}

void Dijkstra()
{
	int min=-1;
	int i,j;
	//
	//begin <5> khoi tao
	//
	for (i=0; i<g.n; i++)
	{
		ThuocT[i] = true;
		Length[i] = VoCuc;
		LastV[i] = -1;
	}
	Length[x]=0;
	ThuocT[x] = false;
	LastV[x] = x;
	//end <5>
	int v=x;
	int t=x;
	while(ThuocT[y]) //<6> neu Y ko khuoc T thi dung 
	{
		//
		//begin<7> chon dinh v thuoc T sao cho length[V] nho nhat
		//
		for (int k=0; k<g.n; k++)
		{
			if (g.a[v][k]!=0 && ThuocT[k]==true && (Length[k]==VoCuc ||
				Length[k]>Length[v] + g.a[v][k]))
			{
				Length[k] = Length[v] + g.a[v][k];
				LastV[k] = v;
			}
		}
		//end <7>
		//
		//begin <8> xem xet va cap nhat lai length cho cac dinh co canh noi tu v toi
		// 
		v = -1;
		for (i=0; i<g.n; i++)
		{
			if (ThuocT[i] == true && Length[i] != VoCuc)
				if (v == -1 || Length[v] > Length[i])
					v = i;
		}
		ThuocT[v] = false;
		//end <8>
	}
}

void xuat()
{
	int Len = Length[y]; // cap nhat de xuat do dai cua duong di
	int DuongDi[MAX]; // duong di xuat nguoc
	int v = y,i;
	//tim duong di: truy xuat latsV
	int id = 0;
	while (v != x)
	{
		DuongDi[id] = v;
		v = LastV[v];
		id++;
	}
	DuongDi[id] = x;
	// xuất ngược để tìm đường đi dinhDau -> dinhCuoi
	printf("%d\n", Len);
	for (i=id; i>0; i--)
	{
		printf("%d -> ", DuongDi[i]);
	}
	printf("%d\n", DuongDi[i]);
	
}

void xuatFile(string duongdan)
{
	ofstream outFile;
	outFile.open(duongdan);
	
	
	int Len = Length[y]; // cap nhat de xuat do dai cua duong di
	int DuongDi[MAX]; // duong di xuat nguoc
	int v = y, i;
	//tim duong di: truy xuat latsV
	int id = 0;
	while (v != x)
	{
		DuongDi[id] = v;
		v = LastV[v];
		id++;
	}
	DuongDi[id] = x;
	// xuất ngược để tìm đường đi dinhDau -> dinhCuoi
	//printf("%d\n", Len);
	for (i = id; i > 0; i--)
	{
		outFile << DuongDi[i] << " -> ";
		//printf("%d -> ", DuongDi[i]);
	}

	outFile << DuongDi[i] << endl;
	cout << "Da viet vao file! " << endl << endl;
		
	outFile.close();
}

void main()
{
	//Hai dinh dau, dinh cuoi
	x=0;
	y=4;
	//doc do thi
	nhapTuFile("dt.txt");
	//tim duong di ngan nhat tu x den y bang thuat toan Dijkstra
	Dijkstra();
	//in duong di ngan nhat tu x den y
	printf("duong di ngan nhat tu %d den %d la:\n", x,y);

	xuat();

	//cap nhat de xuat ra file
	
	xuatFile("output.txt");

	system("pause");
}