// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Euler.h"
#include "OneTouchDrawing.h"


int _tmain(int argc, _TCHAR* argv[])
{

	//Khoi tao
	OneTouchDrawing v("input.txt");

	//In ma tran
	cout << "Ma tran de bai: " << endl;
	v.showMatrix();
	cout << endl;

	//Tim duong
	v.findWay();

	//In ra man hinh
	v.showWay();
	
	//In vao tep
	v.printToFile("output.txt");


	system("pause");
	return 0;
}

