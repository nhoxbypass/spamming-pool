#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"


#define consoleWidth 25
#define consoleHeight 25


enum TrangThai {UP, DOWN, LEFT, RIGHT};

struct ToaDo
{
	int y, x;
};


struct Snake
{
	ToaDo dot[30];	// dot[0] là đầu con rắn
	int n;
	TrangThai tt;
};


struct HoaQua
{
	ToaDo a;
};


void HienThi (Snake snake, HoaQua hoaqua)
{
	clrscr(); // xóa màn hình
	TextColor(7);

	for (int i = 0; i < consoleHeight; i++)
	{
		gotoXY (consoleWidth, i);
		printf ("|");
	}

	TextColor(14);
	for (int i = 0; i < snake.n; i++)
	{
		gotoXY (snake.dot[i].x, snake.dot[i].y);
		printf ("*");
	}

	// hiển thị hoa quả, tường,.....

	TextColor(12);
	gotoXY (hoaqua.a.x, hoaqua.a.y);
	printf ("x");
}


void DieuKhien (Snake &snake)
{
	if (_kbhit())
	{
		int key = _getch();

		// lưu ý nếu xài phím mũi tên thì ta phải xử lý đặc biệt
		if (key == 'A' || key == 'a')
			snake.tt = LEFT;
		else if (key == 'D' || key == 'd')
			snake.tt = RIGHT;
		else if (key == 'W' || key == 'w')
			snake.tt = UP;
		else if (key == 'S' || key == 's')
			snake.tt = DOWN;
	}


	for (int i = snake.n-1; i > 0; i--)
		snake.dot[i] = snake.dot[i-1];

	if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == LEFT)
		snake.dot[0].x--;
	else if (snake.tt == RIGHT)
		snake.dot[0].x++;
}


// trả về 1 nếu có ăn, trả về 0 nếu không ăn
int RanAn_HoaQua (Snake snake, HoaQua hoaqua)
{
	if (snake.dot[0].x == hoaqua.a.x &&
		snake.dot[0].y == hoaqua.a.y)

		return 1;

	return 0;
}

// nếu con rắn ăn thì mới gọi hàm này
void TaoHoaQua (HoaQua &hoaqua)
{
	hoaqua.a.y = rand() % consoleHeight;
	hoaqua.a.x = rand() % consoleWidth;
}


void TangDoDai (Snake &snake)
{
	for (int i = snake.n; i > 0; i--)
		snake.dot[i] = snake.dot[i-1];

	snake.n++;

	if (snake.tt == UP)
		snake.dot[0].y--;
	else if (snake.tt == DOWN)
		snake.dot[0].y++;
	else if (snake.tt == LEFT)
		snake.dot[0].x--;
	else if (snake.tt == RIGHT)
		snake.dot[0].x++;
}


int GameOver (Snake snake)
{
	if (snake.dot[0].y < 0 || snake.dot[0].y == consoleHeight ||
		snake.dot[0].x < 0 || snake.dot[0].x >= consoleWidth)

		return 1;


	for (int i = 1; i < snake.n; i++)
		if (snake.dot[0].x == snake.dot[i].x &&
			snake.dot[0].y == snake.dot[i].y)
				return 1;

	// riêng vụ rắn tự cắn mình thì các bạn tự làm, rất là dễ
	return 0;
}


void main()
{
	srand(time(NULL));
	Snake snake;
	snake.n = 1;
	snake.dot[0].y = snake.dot[0].x = 0;
	snake.tt = RIGHT;

	HoaQua hoaqua;
	hoaqua.a.y = 10;
	hoaqua.a.x = 10;


	int ThoiGianSleep = 100;


	while (1)
	{
		// hiển thị
		HienThi (snake, hoaqua);

		// điều khiển
		DieuKhien (snake);

		// xử lý ăn hoa quả, tạo hoa quả
		if (RanAn_HoaQua (snake, hoaqua))
		{
			ThoiGianSleep -= 10;
			TaoHoaQua (hoaqua);
			TangDoDai (snake);	// tăng độ dài cho snake
		}

		// game over, win game
		if (GameOver(snake))
		{
			//clrscr();
			gotoXY (0, 0);
			printf ("Ban thua roi");
			_getch();
			break;
		}


		Sleep(ThoiGianSleep);
	}

	_getch();
}