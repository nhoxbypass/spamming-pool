#include "stdafx.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <cstdlib>


using namespace std;

struct Vertex{
	int Color;
	char kytu;
};



typedef struct car{
	int x, y;
};



#define LEVEL1 5
#define LEVEL2 10
#define LEVEL3 15
#define LEVEL4 20
#define LEVEL5 25 

int  LEVEL = 1;

char map[50][50]; // Mảng 2 chiều các ký tự.
int Point = 0;
int Life = 3;

int o[50] = { -1 };
int no = 0;

// Tọa độ viên đạn ban đầu
car dan[20]; // tối đa 20 viên đạn 
int n_dan = 0;

int flagXoaXe = 0;

// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle

		(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1, y - 1 };
	hConsoleOutput = GetStdHandle

		(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput,

		Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle

		(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void VeDuongDua_1()
{
	// Dài 30, rộng 30.
	for (int i = 0; i < 30; i++)
	{
		map[i][0] = '|';
		map[i][29] = '|';
		if (i % 2 == 0)
		{
			map[i][14] = '|';
		}

		for (int j = 1; j < 29 && j != 14; j++)
		{
			map[i][j] = ' ';
		}
	}
}

void VeDuongDua_2()
{
	// Dài 30, rộng 30.
	for (int i = 0; i < 30; i++)
	{
		map[i][0] = '|';
		map[i][29] = '|';
		if (i % 2 != 0)
		{
			map[i][14] = '|';
		}

		for (int j = 1; j < 29 && j != 14; j++)
		{
			map[i][j] = ' ';
		}
	}
}

void InDuongDua()
{

	// Dài 30, rộng 30.
	for (int i = 0; i < 30; i++)
	{
		cout << "\t\t\t";
		for (int j = 0; j < 30; j++)
		{

			/* ============ In Đường Đua ========== */
			if (j == 0 || j == 29)
			{
				textcolor(191);
				map[i][j] = ' ';
				cout << map[i][j];
				textcolor(7);
			}

			/* ================================= */

			/* IN XE PLAYER */
			else if (map[i][j] == 'X' || map[i][j] == '@' || map[i][j] == '#')
			{
				textcolor(14); // Màu vàng.
				cout << map[i][j];
				textcolor(7); // Trở lại màu bình thường.
			}

			/* IN XE COMPUTER */
			else if (map[i][j] == '!')
			{
				//map[i][j] = ' '; // Bỏ đi ký tự '!'
				textcolor(200);
				cout << map[i][j];
				textcolor(7);
			}
			else if (j == 14)
			{
				textcolor(15);
				cout << map[i][j];
				textcolor(7);

				map[i][j] = ' '; // Xóa lằn đi.
			}


			// Những ký tự không phải là xe.
			else
			{
				cout << map[i][j];
			}
		}
		if (i == 5)
		{
			cout << "\t   Point : " << Point;
		}
		if (i == 6)
		{
			cout << "\t   Life : " << Life << " ";
		}
		if (i == 7 && LEVEL == 6)
		{
			cout << "\t   LEVEL : MAX (6)" << " ";
		}
		else if (i == 7)
		{
			cout << "\t   LEVEL : " << LEVEL << " ";
		}

		cout << endl;
	}
}

void VeXePlayer(int x, int y)
{
	map[x][y] = 'X'; // Thân xe.
	map[x][y - 1] = '#'; // Bên trái thân xe.
	map[x][y + 1] = '#'; // Bên phải thân xe.
	map[x - 1][y - 1] = '@'; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = '@'; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = '@'; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = '@'; // Bánh xe dưới bên phải.
}

void VeXeChuongNgaiVat(int x, int y)
{
	map[x][y] = '!'; // Thân xe.
	map[x][y - 1] = '!'; // Bên trái thân xe.
	map[x][y + 1] = '!'; // Bên phải thân xe.
	map[x - 1][y - 1] = '!'; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = '!'; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = '!'; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = '!'; // Bánh xe dưới bên phải.	
}

void XoaXeChuongNgai(int x, int y)
{
	map[x][y] = ' '; // Thân xe.
	map[x][y - 1] = ' '; // Bên trái thân xe.
	map[x][y + 1] = ' '; // Bên phải thân xe.
	map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
	map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
	map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
	map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.
}


bool diemNamTrongHCN(int x, int y, car cOpponent){
	return  ((x >= cOpponent.x - 1) && (x <= cOpponent.x + 1) && (y >= cOpponent.y - 1) && (y <= cOpponent.y + 1));
}

bool xeDungNhau(car cPlayer, car cOpponent)
{
	return (diemNamTrongHCN(cPlayer.x - 1, cPlayer.y - 1, cOpponent) || diemNamTrongHCN(cPlayer.x + 1, cPlayer.y - 1, cOpponent) || diemNamTrongHCN(cPlayer.x - 1, cPlayer.y + 1, cOpponent) || diemNamTrongHCN(cPlayer.x + 1, cPlayer.y + 1, cOpponent));
}

int xeBiDung(car cPlayer, car *cOpponent, int n)
{
	for (int i = 0; i < n; i++){
		if (xeDungNhau(cPlayer, cOpponent[i]))
			return i;
	}

	return -1;
}

void DiChuyenXe(int &x, int &y, car& cPlayer, car *cOpponent, int& LEVEL) // x, y là tọa độ hiện tại của xe.
{

	/*

	Trái Trên cùng: 1, 2
	Trái dưới cùng: 28, 2
	phải trên cùng: 1, 27
	phải dưới cùng: 28, 27

	*/

	// qua trái.

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (y > 2)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				cout << "\a";
				//exit(0); // Kết thúc.
				Life--;
				//return;
				o[no++] = xeBiDung(cPlayer, cOpponent, LEVEL);

				XoaXeChuongNgai(x, y);

				x = 28; y = 15;

				VeXePlayer(x, y);
				return;
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			y--; // Giảm cột xuống.
			VeXePlayer(x, y); // Vẽ lại xe.


		}

	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		//map[xo - 1][yo] = ' ';
		//xo = x;
		//yo = y;

		n_dan++;
		dan[n_dan - 1].x = x;
		dan[n_dan - 1].y = y;
	}
	// qua phải.
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (y <= 26)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				cout << "\a";
				//exit(0); // Kết thúc.
				Life--;
				//return;

				o[no++] = xeBiDung(cPlayer, cOpponent, LEVEL);


				XoaXeChuongNgai(x, y);

				x = 28; y = 15;

				VeXePlayer(x, y);
				return;
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			y++; // Tăng cột lên.
			VeXePlayer(x, y); // Vẽ lại xe.


		}
	}

	// Đi lên.
	else if (GetAsyncKeyState(VK_UP))
	{
		if (x > 1)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				cout << "\a";
				//exit(0); // Kết thúc.
				Life--;
				//return;

				o[no++] = xeBiDung(cPlayer, cOpponent, LEVEL);

				XoaXeChuongNgai(x, y);

				x = 28; y = 15;

				VeXePlayer(x, y);
				return;
			}

			// Xóa xe đi.
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			x--; // Giảm số dòng.
			VeXePlayer(x, y); // Vẽ lại xe.
		}
	}

	// Đi xuống
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (x <= 27)
		{
			// Đang so sánh xem có bị trùng với xe tĩnh & xe động hay không ?
			if (map[x][y] == '!' || map[x][y - 1] == '!' || map[x][y + 1] == '!' || map[x - 1][y - 1] == '!' || map[x + 1][y - 1] == '!' || map[x - 1][y + 1] == '!' || map[x + 1][y + 1] == '!')
			{
				cout << "\a";
				//exit(0); // Kết thúc.
				Life--;
				//return;

				o[no++] = xeBiDung(cPlayer, cOpponent, LEVEL);

				XoaXeChuongNgai(x, y);

				x = 28; y = 15;

				VeXePlayer(x, y);
				return;
			}

			// Xóa xe đi.-
			map[x][y] = ' '; // Thân xe.
			map[x][y - 1] = ' '; // Bên trái thân xe.
			map[x][y + 1] = ' '; // Bên phải thân xe.
			map[x - 1][y - 1] = ' '; // Bánh xe trên bên trái.
			map[x + 1][y - 1] = ' '; // Bánh xe dưới bên trái.
			map[x - 1][y + 1] = ' '; // Bánh xe trên bên phải.
			map[x + 1][y + 1] = ' '; // Bánh xe dưới bên phải.

			x++; // Tăng số dòng.
			VeXePlayer(x, y); // Vẽ lại xe.
		}
	}

}

void xoaPhanTu(int pos, int *a, int& n)
{
	for (int i = pos - 1; i < n - 1; i++)
	{
		a[i] = a[i + 1];
	}
	n--;
}

void deleteCar(int pos, car *a, int& n)
{
	for (int i = pos - 1; i < n - 1; i++)
	{
		a[i].x = a[i + 1].x;
		a[i].y = a[i + 1].y;
	}
	n--;
}



/*
Viết hàm tìm ra chiếc xe đối thủ mình đã đụng trúng
*/


/*
Các tính năng của trò chơi
- Tính năng điểm số
- Tiền rơi
- Lượt chơi
- Chạy theo quảng đường tính theo cấp độ
- Bắn súng
- Mono car
- Top xe đua
- Tăng tốc thời gian thực
- Mod xăng rơi xăng giữa đường
*/



int main()
{

	resizeConsole(800, 600);

	car cPlayer;
	cPlayer.x = 20; cPlayer.y = 15;

	car *cOpponent;
	cOpponent = (car*)malloc(LEVEL * sizeof(car));

	// Khởi tạo giá trị ban đầu của các xe đối thủ


	for (int i = 0; i < LEVEL; i++)
	{
		//cOpponent[i].x = 2 + rand() % (LEVEL + 5);
		cOpponent[i].x = 2 + rand() % (LEVEL + 2);
		cOpponent[i].y = 2 + (rand() % 26);
	}


	for (int i = 0; i < LEVEL; i++){
		bool flag = false;

		for (int j = 0; j < LEVEL; j++)
		{
			if (i != j && (cOpponent[i].y == cOpponent[j].y || cOpponent[i].y == (cOpponent[j].y + 1) || cOpponent[i].y == (cOpponent[j].y - 1) || cOpponent[i].y == (cOpponent[j].y + 2) || cOpponent[i].y == (cOpponent[j].y - 2)))
			{
				flag = true;
			}
		}
		if (flag){
			cOpponent[i].y = 2 + (rand() % 26);
			i--;
		}
	}


	int a = 0;
	int count = 0;

	while (true)
	{


		a++;
		if (a % 2 != 0)
		{
			VeDuongDua_1();
		}
	else
		{
		VeDuongDua_2();
	}

		VeXePlayer(cPlayer.x, cPlayer.y);

		for (int i = 0; i < LEVEL; i++)
		{
			bool flag = false;

			for (int j = 0; j < no; j++)
			{
				if (i == o[j])
					flag = true;
			}

			if (!flag && cOpponent[i].x != 30)
			{
				VeXeChuongNgaiVat(cOpponent[i].x, cOpponent[i].y);
			}

			flag = false;
		}

		for (int i = 0; i < n_dan; i++)
		{
			map[dan[i].x - 1][dan[i].y] = 'o';
		}

		//for (int i = 0; i < LEVEL; i++)
		//{
		//	//if (diemNamTrongHCN(xo, yo, cOpponent[i]))
		//	//{
		//	//	XoaXeChuongNgai(cOpponent[i].x, cOpponent[i].y);
		//	//	deleteCar(i + 1, cOpponent, LEVEL);
		//	//	flagXoaXe = true;
		//	//	Point++;
		//	//}
		//	for (int j = 0; j < n_dan; j++)
		//	{
		//		if (diemNamTrongHCN(dan[j].x, dan[j].y, cOpponent[i]))
		//		{
		//			XoaXeChuongNgai(cOpponent[i].x, cOpponent[i].y);
		//			deleteCar(i + 1, cOpponent, LEVEL);
		//			flagXoaXe++;
		//			Point++;
		//		}
		//	}
		//}

		for (int i = 0; i < LEVEL; i++)
		{
			for (int j = 0; j < n_dan; j++)
			{
				if (diemNamTrongHCN(dan[j].x, dan[j].y, cOpponent[i]))
				{
					XoaXeChuongNgai(cOpponent[i].x, cOpponent[i].y);
					deleteCar(i + 1, cOpponent, LEVEL);
					deleteCar(j + 1, dan, n_dan);
					flagXoaXe++;
					Point++;
					break;
					i--;
				}
			}
		}

		XoaManHinh();



		InDuongDua();


		DiChuyenXe(cPlayer.x, cPlayer.y, cPlayer, cOpponent, LEVEL);



		Sleep(0);

		if (a >= 30)
		{
			a = 0;
		}

		// Cách 2 : tính điểm khi vượt mặt một xe đối thủ thì có điểm ngay lập tức
		for (int i = 0; i < LEVEL; i++){
			if (cPlayer.x == cOpponent[i].x)
			{
				Point++;
			}
		}


		if (map[cPlayer.x][cPlayer.y] == '!' || map[cPlayer.x][cPlayer.y - 1] == '!' || map[cPlayer.x][cPlayer.y + 1] == '!' || map[cPlayer.x - 1][cPlayer.y - 1] == '!' || map[cPlayer.x + 1][cPlayer.y - 1] == '!' || map[cPlayer.x - 1][cPlayer.y + 1] == '!' || map[cPlayer.x + 1][cPlayer.y + 1] == '!')
		{
			cout << "\a";
			Life--;

			o[no++] = xeBiDung(cPlayer, cOpponent, LEVEL);

			XoaXeChuongNgai(cPlayer.x, cPlayer.y);

			cPlayer.x = 28; cPlayer.y = 15;

			VeXePlayer(cPlayer.x, cPlayer.y);

		}

		if (Life == 0)
		{
			printf("\a"); // Tiếng beep.
			gotoxy(60, 5);
			cout << "Ban duoc :" << Point << " diem";
			gotoxy(26, 45);


			delete[] cOpponent;
			system("pause");
			Sleep(500);
			return 0; // Kết thúc.
		}


		///


		///

		for (int i = 0; i < LEVEL; i++)
		{
			XoaXeChuongNgai(cOpponent[i].x, cOpponent[i].y);
			(cOpponent[i].x)++;
			if (cOpponent[i].x == 31)
			{
				//cOpponent[i].x = 2 + rand() % (LEVEL + 5);
				cOpponent[i].x = 2 + rand() % (LEVEL + 2);
				cOpponent[i].y = 2 + rand() % (26);

				// Cách 1 : tính điểm theo xe đối thủ đi đến hết đường thì thêm một điểm
				//Point++;

			}
		}

		//if (flagXoaXe)
		//{
		//	LEVEL++;
		//	//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
		//	cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
		//	cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		//	flagXoaXe = false;
		//}
		if (flagXoaXe)
		{
			if (LEVEL + flagXoaXe <= 6)
			{
				LEVEL += flagXoaXe;
				for (int i = LEVEL - flagXoaXe; i < LEVEL; i++)
				{
					cOpponent[i].x = 2 + rand() % (LEVEL + 2);
					cOpponent[i].y = 2 + rand() % (26);
				}

				flagXoaXe = 0;
			}

		}

		for (int t = 0; t < no; t++)
		{
			int objectPos = o[t];

			if (cOpponent[objectPos].x == 30)
			{
				xoaPhanTu(t + 1, o, no);
			}
		}



		for (int i = 0; i < LEVEL; i++){
			bool flag = false;

			for (int j = 0; j < LEVEL; j++)
			{
				if (i != j && (cOpponent[i].x == cOpponent[j].x || cOpponent[i].x == cOpponent[j].x - 1 || cOpponent[i].x == cOpponent[j].x + 1 || cOpponent[i].x == cOpponent[j].x + 2 || cOpponent[i].x == cOpponent[j].x - 2) && (cOpponent[i].y == cOpponent[j].y || cOpponent[i].y == (cOpponent[j].y + 1) || cOpponent[i].y == (cOpponent[j].y - 1) || cOpponent[i].y == (cOpponent[j].y + 2) || cOpponent[i].y == (cOpponent[j].y - 2)))
				{
					flag = true;
				}
			}
			if (flag){
				cOpponent[i].y = 2 + (rand() % 26);
				//Sleep(5);
				i--;
			}
			flag = false;
		}


		//if (xo != -1)
		//{
		//	map[xo - 1][yo] = ' ';
		//	xo--;
		//}
		for (int i = 0; i < n_dan; i++)
		{
			if (dan[i].x != -1)
			{
				map[dan[i].x - 1][dan[i].y] = ' ';
				dan[i].x--;
			}
			if (dan[i].x == -1)
			{
				deleteCar(i + 1, dan, n_dan);
			}
		}


		if (count == 0 && Point == LEVEL1)
		{
			LEVEL++;
			cOpponent = (car*)realloc(cOpponent, LEVEL * sizeof(car));
			count++;
			//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
			cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
			cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		}
		else if (count == 1 && Point == LEVEL2)
		{
			LEVEL++;
			cOpponent = (car*)realloc(cOpponent, LEVEL * sizeof(car));
			count++;
			//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
			cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
			cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		}
		else if (count == 2 && Point == LEVEL3)
		{
			LEVEL++;
			cOpponent = (car*)realloc(cOpponent, LEVEL * sizeof(car));
			count++;
			//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
			cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
			cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		}
		else if (count == 3 && Point == LEVEL4)
		{
			LEVEL++;
			cOpponent = (car*)realloc(cOpponent, LEVEL * sizeof(car));
			count++;
			//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
			cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
			cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		}
		else if (count == 4 && Point == LEVEL5)
		{
			LEVEL++;
			cOpponent = (car*)realloc(cOpponent, LEVEL * sizeof(car));
			count++;
			//cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 5);
			cOpponent[LEVEL - 1].x = 2 + rand() % (LEVEL + 2);
			cOpponent[LEVEL - 1].y = 2 + rand() % (26);
		}

	}
}