// Test.cpp : Defines the entry point for the console application.
//

#include <iostream>
using namespace std;

bool isLeapYear(int  iY);


int _tmain(int argc, _TCHAR* argv[])
{
	int iD, iM, iY;
	cout << "Nhap ngay: ";
	cin >> iD;
	cout << "Nhap thang: ";
	cin >> iM;
	cout << "Nhap nam: ";
	cin >> iY;

	iD -= 1;
	if (iD == 0)
	{
		switch (iM - 1)
		{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			iD = 31;
			iM -= 1;
			break;
		case 4: case 6: case 9: case 11:
			iD = 30;
			iM -= 1;
			break;
		case 2:
			if (isLeapYear(iY))
				iD = 29;
			else
				iD = 28;
			iM -= 1;
			break;
		case 0:
			iD = 31;
			iY -= 1;
			iM = 12;
			break;
		}


	}
	cout << iD << "/" << iM << "/" << iY << endl;

	system("pause");
	return 0;


}



bool isLeapYear(int  iY){
	if (((iY % 4 == 0) && (iY % 100 != 0)) || (iY % 400 == 0))
	{
		return true;
	}
	return false;
}