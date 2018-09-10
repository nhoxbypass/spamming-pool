// 1412477_1412465.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	QInt A, B;
	if (argc == 1)
		A.process(); //test tren visual
	else
	{
		A.process(argv[1], argv[2]);
	}

	cout << "Done!\n";
	return 0;
}

