#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include "console.h"


enum TrangThai {UP, DOWN};

struct ChuChay	// chữ chạy
{
	char s[51];
	int tt;
	int y, x;	// tung độ y và hoành độ x
};




#define consoleWidth 80
#define consoleHeight 25


void main()
{
	srand(1234);

	ChuChay A;
	
	strcpy (A.s, "Hello World");
	A.y = 0;
	A.x = (consoleWidth - strlen(A.s))/ 2;
	A.tt = DOWN;
	
	while (1)
	{
		clrscr();
		//system("cls");

		gotoXY (A.x, A.y);		// di chuyển đến hoành độ x, tung độ y
		TextColor(8 + rand()%8);	// đổi sang màu gì đó =))
		printf ("%s", A.s);


		if (A.y >= consoleHeight-1)
			A.tt = UP;
		if (A.y < 1)
			A.tt = DOWN;
		

		if (A.tt == DOWN)
			A.y++;
		else if (A.tt == UP)
			A.y--;


		// -- điều khiển

		if (kbhit())	// hàm này ko phải là hàm chính quy
		{
			char key = _getch();

			if (key == 'A' || key == 'a')
				A.x--;
			else if (key == 'D' || key == 'd')
				A.x++;
		}

		Sleep(100);	// tui gọi là 1 nhịp game
	}
}