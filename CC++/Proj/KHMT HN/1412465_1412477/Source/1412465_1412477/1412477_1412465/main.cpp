// 001.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	

	QInt A, B;
	if (argc == 1)
		A.process();//test tren visual
	else
	{
// 		string path_in = argv[0];
// 		for (int i = path_in.length(); i >= 0; i--)
// 		{
// 			if (path_in[i] == '\\')
// 				break;
// 			else
// 				path_in.erase(i, 1);
// 		}
// 
// 		for (int i = path_in.length(); i >= 0; i--)
// 		{
// 			if (path_in[i] == '\\')
// 				path_in.insert(i,"\\");
// 		}

// 		string path_out = path_in;
// 		path_in += argv[1];
// 		path_out += argv[2];
// 		cout << path_in << endl << path_out << endl;
// 		//fflush(stdin);
// 		char *in = new char[300];
// 		char *out = new char[300];
// 		strcpy(in, path_in.c_str());
// 		strcpy(out, path_in.c_str());
// 		_flushall;
// 		strcpy(out, path_out.c_str());
// 
// 		cout << in << endl << out << endl;
// 		//system("pause");



	A.process(argv[1], argv[2]);
	}
		
	cout << "Done!\n";
	return 0;
}

/*int choose;

do
{
system("cls");
cout << "1. Chuyen day bit sang thap phan.\n";
cout << "2. Tinh toan tren bit.\n";
cout << "3. Chuyen thap phan sang day bit.\n";
cout << "Chon chuc nang:";
cin >> choose;
} while (choose < 1 || choose >3);

QInt A, B;
switch (choose)
{
case 1:
{
system("cls");
A.enterBit();
cout << "Day bit vua nhap:" << A << endl;
cout << "Gia tri trong dang thap phan:" << A.BinToDec() << endl;
break;
}
case 3:
{
system("cls");
A.enterBit();
cout << "So vua nhap:" << A << endl;
cout << "Gia tri trong dang nhi phan:" << A.DecToBin() << endl;
break;
}
case 2:
{
system("cls");
A.enterBit();
system("cls");
B.enterBit();
system("cls");
cout << "2 day bit vua nhap:" << A << "   " << B << endl;
char Ope;
cout << "Nhap toan tu phep tinh:";
cin >> Ope;
switch (Ope)
{
case '+':
{
cout << A << " + " << B << " = " << A + B << endl;
cout << A.BinToDec() << " + " << B.BinToDec() << " = " << (A + B).BinToDec() << endl;
break;
}
case '-':
{
cout << A << " - " << B << " = " << A - B << endl;
cout << A.BinToDec() << " - " << B.BinToDec() << " = " << (A - B).BinToDec() << endl;
break;
}

case '*':
{
cout << A << " * " << B << " = " << A * B << endl;
cout << A.BinToDec() << " * " << B.BinToDec() << " = " << (A * B).BinToDec() << endl;
break;
}

case '/':
{
cout << A << " / " << B << " = " << A + B << endl;
cout << A.BinToDec() << " / " << B.BinToDec() << " = " << (A / B).BinToDec() << endl;
break;
}
}
break;
}
}*/