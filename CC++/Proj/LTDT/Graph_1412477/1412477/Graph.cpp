#include "Graph.h"


void GRAPH::ViengTham(int i, int _label)
{
	Label[i] = _label;
	for (int j = 0; j < n; j++)
	{
		//Kiem tra dinh J co duoc vieng tham chua
		if ((Label[j] == 0) && (Arr[i][j] || Arr[j][i]))  //Neu Label[j]=0 thi J chua duoc vieng tham, De dam bao tinh lien thong thi J noi voi I
			ViengTham(j, _label); //Vieng tham J, danh dau 1
	}
}
int GRAPH::XetLienThong()
{
	for (int i = 0; i < n; i++)
		Label[i] = 0; //Khoi tao cac dinh co label = 0
	int iSoMienLienThong = 0;
	for (int i = 0; i < n; i++)
	{
		if (Label[i] == 0)
		{
			iSoMienLienThong++; //Tang so TPLT danh dau
			ViengTham(i, iSoMienLienThong);
		}
	}
	return iSoMienLienThong;
}

void GRAPH::docMaTranKe()
{
	string tmp;
	string path;
	cout << "Nhap ten file Do thi (Mac dinh GATAU.info): ";
	getline(cin, path);

	//Default path if current path is empty
	if (path == "")
	{
		path = "GATAU.info";
	}

	ifstream myfile;
	myfile.open(path);

	if (!myfile.is_open())
	{
		cout << "Khong the mo tep!" << endl;
		system("pause");
		exit(0);
	}

	getline(myfile, tmp);
	n = stoi(tmp);

	if (n > MAX)
	{
		cout << "Kich thuoc qua lon! " << endl;
		return;
	}
	Label = new int[n];


	for (int i = 0; i < n; i++)
	{
		//Get city name without deliminator
		if (i == 7)
		{
			getline(myfile, tmp);
		}
		else
		{
			getline(myfile, tmp, ',');
		}

		//Trim string that have leading space
		if (tmp[0] == ' ')
		{
			tmp.erase(0, 1);
		}

		Station.push_back(tmp);
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			myfile >> Arr[i][j];
		}
	}

	myfile.close();
}

void GRAPH::xuatMaTranKe()
{
	cout << "\tMA TRAN KE: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "     ";
		for (int j = 0; j < n; j++)
		{
			cout << Arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
