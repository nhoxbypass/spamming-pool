#include "stdafx.h"
#include "Bellman.h"



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

bool DuongDiNganNhat_Bellman(int dinhDau)
{
	int k = 0, i, j, v;
	//
	//begin <1>
	//
	for (i = 0; i < g.n; i++)
	{
		P_hientai[i] = VoCuc;
	}
	P_hientai[dinhDau] = 0;
	//
	//end <1>
	//
	// lặp cho đến khi thỏa điều kiện dừng
	while (true)
	{
		// chuyen dòng P hien tai thành dòng P truoc
		for (i = 0; i < g.n; i++)
		{
			P_truoc[i] = P_hientai[i];
		}
		//
		//begin <2> voi moi dinh i tính P[k][i]=min( {P[k-1][i]} , {P[k-1][j]+L(j,i)/có cạnh nối j đến i} )
		//
		for (i = 0; i < g.n; i++) // voi moi dinh i
		{
			v = -1; // dinh ke truoc i trong duong di ngan nhat hien tai
			// (=-1 nghia là chua tìm dc dinh v)

			for (j = 0; j < g.n; j++) //for each (u,v) in danh_sach_cung:
			{
				// Neu co canh noi tu i -> j
				// Va 
				// Va v == -1 (chua tim duoc dinh v) hoac khoang_cach(i) + trong_so(i,j) < khoang cach(v)
				if (g.a[j][i] != 0 && P_truoc[j] != VoCuc &&
					(v == -1 || P_truoc[j] + g.a[j][i] < P_truoc[v] + g.a[v][i]))
				{
					v = j; //Dinh ke truoc i := j
				}
					
			}

			//  Neu v != 1 (co dinh v ke truoc i)
			// Va ... hoac
			if (v != -1 && (P_truoc[i] == VoCuc ||
				P_truoc[i] > P_truoc[v] + g.a[v][i]))
			{
				LastV[i] = v;
				P_hientai[i] = P_truoc[v] + g.a[v][i];
			}
		}
		//
		//end <2>
		//
		//
		//begin <3> Nếu dòng k và dòng k-1 của ma trận P trùng nhau thì P[k][i] chính là độ dài đường đi ngắn nhất tứ x đến i
		//
		bool trung_nhau = true; // bien kiem tra 2 dòng P có trùng nhau không
		for (i = 1; i <= g.n; i++)
		{
			if (P_truoc[i] != P_hientai[i])
			{
				trung_nhau = false; // có mat giá tri khác nhau
				break;  // thì ca 2 dòng se	 khác nhau
			}
		}
		if (trung_nhau == true)
		{
			// neu trùng nhau thì thuat toán tìm thay
			return true; // duong di ket thuc
		}
		else
		{
			//Nếu k<n - 1 thì k : = k + 1 và làm lại các bước trên
			if (k < g.n - 1)
				k = k + 1; // tiep tuc lap
			else //Nếu k = n - 1 thì dừng vì từ x đi tới được một mạch âm (chưa trong so am)
				return false;
		}
		//
		//end <3>
		//
	}
}

void xuatDuongDi()
{
	int i;
	for (i = 0; i < g.n; i++)
	{
		int sum = 0;
		if (i != dau && LastV[i] != 0)
		{
			printf(" - Duong di tu %d toi %d: \t", dau, i);
			int t = i;
			while (t != dau)
			{
				sum += g.a[LastV[t]][t]; //Cong trong so vao do dai
				cout << t << " <-- ";
				t = LastV[t];
			}
			cout << t << endl;
			cout << " - Voi do dai: " << sum << endl << endl;
		}
	}
}

void xuatFile(string path)
{
	ofstream outFile;
	outFile.open(path);

	int i = cuoi;
	if (i != dau && LastV[i] != 0)
	{
		printf(" - Duong di tu %d toi %d: \t", dau, i);
		int t = i;
		while (t != dau)
		{
			
			cout << t << " <-- ";
			outFile << t << " <-- ";
			t = LastV[t];
		}
		cout << t << endl ;
		outFile << t << endl;
		cout << " - Da ghi vao file!" << endl << endl;
	}
	else
	{
		cout << " - Khong tim thay duong di tu " << dau << " den " << cuoi << endl << endl;
	}

	outFile.close();
}


