#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

int main()
{
	GRAPH g;
	int iTPLienThong;
	g.docMaTranKe();
	g.xuatMaTranKe();

	iTPLienThong = g.XetLienThong();

	if (iTPLienThong != 1)
	{
		cout << "Do thi co " << iTPLienThong << " thanh phan lien thong. " << endl;
		cout << " --> DO THI CHUA LIEN THONG, CAC GA TAU CHUA LIEN THONG VOI NHAU!" << endl << endl;
	}
	else
		cout << " --> DO THI LIEN THONG!" << endl << endl;
	

	//Cau 3
	//Dem tong so TPLT cua do thi, duyet va kiem tra, tim thanh phan co duong di nho nhat
	//--> Cach xay dung do thi hieu qua nhat
	g.bai3();
	cout << endl;

	//Cau 4
	//Dua vao TRONG SO cua ma tran do thi. Tim CAY KHUNG nho nhat.
	//g.PrimAlg();
	//g.ShowTree();

	system("pause");
}