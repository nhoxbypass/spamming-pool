#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#define MAX 100

struct EDGE
{
	int v1;//Đỉnh v1.
	int v2;//Đỉnh v2.
	int w;//Trọng số.
};


class GRAPH
{
	vector<string> Station;
	int n;
	int Arr[MAX][MAX];
	int* Label;
	//Cay khung
	vector<EDGE> CayKhung;
	
public:


	void docMaTranKe();


	void xuatMaTranKe();

	void ViengTham(int i, int _label);
	int XetLienThong();

	void bai3() {
		int soMienLienThong = this->XetLienThong(); bool flag = 0; int max = 0; int maxVote; int count = 0; for (int i = 0; i < n; i++){ for (int j = i - 1; j >= 0; j--){ if (Label[i] == Label[j]) flag = 1; } if (!flag) { for (int k = i; k < n; k++) { if (Label[i] == Label[k]) count++; } if (count>max){ max = count; maxVote = i; } } flag = 0; count = 0; } for (int j = 0; j < n; j++) {
			if (Label[j] == Label[maxVote])//CÁC ĐỈNH CÙNG MIỀN LIÊN THÔNG SẼ CÓ NHÃN = NHAU.
				cout << Station[j] << "-"<<Station[j+1]<<","; } }


	//Additional
	void GRAPH::ShowTree()
	{
		int iWeight = 0;
		for (int i = 0; i < CayKhung.size(); i++)
			iWeight += CayKhung[i].w;
		cout << "Chi phi la: " << iWeight << endl;
		cout << "Duong day la: " << endl;
		for (int i = 0; i < CayKhung.size(); i++)
			cout << CayKhung[i].v1 << "-" << CayKhung[i].v2;
		cout << endl;
	}
	void GRAPH::PrimAlg()
	{
		vector <bool>  DaTham(n, false);//Mang danh dau dinh da xet
		CayKhung.clear(); //lam rong ket qua cay khung
		DaTham[0] = true;//Da Tham dinh 0

		while (CayKhung.size() < (n - 1))
		{
			EDGE eMin;
			int iMinWeight = -1; //Chua co canh min
			for (int i = 0; i < n; i++)
			{
				if (DaTham[i] == false)
				{
					for (int j = 0; j < n; j++)
					{
						if (DaTham[j] == true && Arr[i][j] != 0)
						{
							if (iMinWeight == -1 || iMinWeight > Arr[i][j])
							{
								eMin.v1 = i;
								eMin.v2 = j;
								eMin.w = Arr[i][j];
								iMinWeight = Arr[i][j];
							}
						}
					}
				}
			}
			if (iMinWeight == -1)
				cout << "Do thi khong lien thong";
			else
			{
				CayKhung.push_back(eMin);
				DaTham[eMin.v1] = true;
			}
		}
	}

	bool kiemTraMaTranHopLe()
	{
		for (int i = 0; i < n; i++)
		{
			if (Arr[i][i] != 0)
			{
				return false;
			}
		}
		return true;
	}

	bool kiemTraDoThiVoHuong()
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != Arr[j][i])
				{
					return false;
				}
			}
		}
		return true;
	}

	int timDinhKe(int Vertex, int Print = 0)
	{
		Vertex--;

		int cout = 0;
		int AdjaVertex[MAX];
		for (int i = 0; i < n; i++)
		{
			if (Arr[Vertex][i] != 0)
			{
				AdjaVertex[cout] = i + 1;
				cout++;

			}
		}
		if (!kiemTraDoThiVoHuong())
		{
			for (int i = 0; i < n; i++)
			{
				if (Arr[i][Vertex] != 0)
				{
					AdjaVertex[cout] = i + 1;
					cout++;
				}
			}
		}
		if (Print != 0)
		{
			std::cout << " --> Cac dinh ke voi dinh " << Vertex + 1 << ": ";
			for (int i = 0; i < cout; i++)
			{
				std::cout << AdjaVertex[i] << " ";
			}
		}
		return cout;
	}


	void inBacCuaDinh()
	{
		int _Count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != 0)
				{
					_Count++;
				}
			}
			cout << "Dinh " << i + 1 << " la dinh bac " << _Count << endl;
			_Count = 0;
		}
	}

	int demSoDinhBacChan()
	{
		int res = 0;
		int _Count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != 0)
				{
					_Count++;
				}
			}
			if (_Count % 2 == 0)
			{
				res++;
			}
			_Count = 0;
		}

		return res;
	}

	int demSoDinhBacLe()
	{
		int res = 0;
		int _Count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != 0)
				{
					_Count++;
				}
			}
			if (_Count % 2 == 1)
			{
				res++;
			}
			_Count = 0;
		}

		return res;
	}

	int demSoDinhTreo()
	{
		int res = 0;
		int _Count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != 0)
				{
					_Count++;
				}
			}
			if (_Count == 1)
			{
				res++;
			}
			_Count = 0;
		}

		return res;
	}

	int demSoDinhCoLap()
	{
		int res = 0;
		int _Count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Arr[i][j] != 0)
				{
					_Count++;
				}
			}
			if (_Count == 0)
			{
				res++;
			}
			_Count = 0;
		}

		return res;
	}

	GRAPH()
	{
		n = 0;
	}

	~GRAPH()
	{
		n = 0;
		delete[] Label;
	}
};

