#include "stdafx.h"
#include "Dijkstra.h"



void Init(GRAPH g, int dinhdau, int dinhcuoi)
{
	for (int i = 0; i < g.n; i++)
	{
		T[i] = 1; //1 nghia la dinh i con nam trong T
		Length[i] = INF; //khoi tao do dài ban dau là vô cùng lon
		Prev[i] = -1; //chua co dinh lien truoc
	}
	Length[dinhdau] = 0; //khoi tao dinh dau tien
}

bool Dijkstra(GRAPH g, int dinhdau, int dinhcuoi)
{
	Init(g, dinhdau, dinhcuoi); //khoi tao thong so cho thuat toan

	//trong khi dinh cuoi van nam trong T
	while (T[dinhcuoi] == 1)  //(Neu y khong thuoc T thi dung.)
	{
		//Tìm diem v thuoc T sao cho Length[v] nho nhat
		int iMin = INF;
		int v = -1;
		for (int i = 0; i < g.n; i++)
		{
			//Neu dinh i thuoc T, va co the di toi dinhdau, va do dai do < iMin, hoac iMin chua khoi tao
			if (T[i] == 1 && Length[i] != INF && (Length[i] < iMin ||
				iMin == INF))
			{
				//Gan dinh min
				iMin = Length[i];
				v = i;
			}
		}

		if (iMin == INF)
		{
			printf("Ko tim thay duong di\n");
			return false;
		}

		//Luc nay v da la dinh min roi
		Length[v] = iMin;

		//Loai v ra khoi T
		T[v] = 0; 

		//Tinh toan do dài cac canh noi tu v
		//Duyet tat ca cac dinh
		for (int j = 0; j < g.n; j++)
		{
			//Neu dinh j con nam trong T, va co canh noi tu v -> j
			if (T[j] == 1 && g.L[v][j] != 0)
			{
				//Neu len[j] chua khoi tao hoac len[j] dai hon di tu dinhdau -> v sau do di tu v -> j
				if (Length[j] == -1 || Length[j] > Length[v] + g.L[v][j])
				{
					//Gan lai len cho j, khi do di tu dinhdau toi j thi qua v
					Length[j] = Length[v] + g.L[v][j];

					//Dinh truoc cua j la v
					Prev[j] = v;
				}
			}
		}
	}
	return true;
}

void ShowPath(int dinhdau, int dinhcuoi)
{
	int k = dinhcuoi; //Gan dinh k la dinh cuoi, bat dau tu cuoi in nguoc lai

	//Cho den khi chua den dinh dau
	while (k != dinhdau)
	{
		printf(" %d <--- ", k + 1); //in ra
		k = Prev[k]; //Lay diem truoc do
	}

	//In dinh dau
	printf(" %d", dinhdau + 1);
}

void readFromFile(string path, GRAPH &g, int& diemdau, int& diemcuoi)
{
	ifstream inFile;
	inFile.open(path);

	if (!inFile.is_open())
	{
		cout << "Khong the mo file!" << endl;
	}
	else
	{
		inFile >> g.n; //Doc so phan tu

		inFile >> diemdau >> diemcuoi; //Doc diem dau diem cuoi

		for (int i = 0; i < g.n; i++)
		{
			for (int j = 0; j < g.n; j++)
			{
				inFile >> g.L[i][j]; //Doc ma tran
			}
		}
	}
	

	inFile.close();
}

int showLength(int dinhcuoi)
{
	//Do dai tu diem dau den dinh cuoi
	cout << " - Do dai duong di ngan nhat: " << Length[dinhcuoi] << endl << endl;
	return Length[dinhcuoi];
}

void writeToFile(string path, int dinhdau, int dinhcuoi)
{
	ofstream inFile;
	inFile.open(path);

	int k = dinhcuoi;
	while (k != dinhdau)
	{
		inFile << k + 1 << " <--- ";
		k = Prev[k];
	}
	inFile << " " << dinhdau + 1;
	
	cout << "Write to file: Done!" << endl << endl;

	inFile.close();
}

void goToSpecificPath(GRAPH g, int A, int B, int C)
{
	//Xet xem neu C - > B ko thanh cong thi coi nhu khong the di tu A - > B ma phai qua C
	if (Dijkstra(g, C - 1, B - 1))
	{
		ShowPath(C - 1, B - 1); //In ra

		cout << " <--- ";

		if (Dijkstra(g, A - 1, C - 1))
		{
			ShowPath(A - 1, Prev[C - 1]); //In tu A - > diem truoc cua C
		}
	}

	cout << endl;
}

void goToSpecificPath(GRAPH g, int A, int B, int C, int D)
{
	int len1 = 0, len2 = 0;
	
	//Xet truong hop A -> C, C - D, D -> B
	Dijkstra(g, D - 1, B - 1);
	len1 += Length[B - 1];

	Dijkstra(g, A - 1, C - 1);
	len1 += Length[C - 1];
		
	//Xet truong hop A -> D, D- C, C-> B
	Dijkstra(g, C - 1, B - 1);
	len2 += Length[B - 1];

	Dijkstra(g, A - 1, D - 1);
	len2 += Length[D - 1];


	//So sanh doan duong nao be hon
	if (len1 <= len2)
	{
		//Xuat A -> C, C - D, D -> B
		if (Dijkstra(g, D - 1, B - 1))
		{
			ShowPath(D - 1, B - 1);
			cout << " <--- ";
			if (Dijkstra(g, A - 1, C - 1))
			{
				ShowPath(A - 1, C - 1);
			}
		}
	}
	else
	{
		//Xuat A -> D, D- C, C-> B
		if (Dijkstra(g, C - 1, B - 1))
		{
			ShowPath(C - 1, B - 1);
			cout << " <--- ";
			if (Dijkstra(g, A - 1, D - 1))
			{
				ShowPath(A - 1, D - 1);
			}
		}
	}

	cout << endl;
}
