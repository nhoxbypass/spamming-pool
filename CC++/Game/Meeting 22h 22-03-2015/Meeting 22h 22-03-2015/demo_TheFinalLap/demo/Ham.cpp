#include <stdio.h>
#include <Windows.h>
#include <math.h>
#include "Ham.h"
#include "Mang.h"

extern int points;


void XoaManHinh()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}



void DiChuyen_Xuong (toado vatcan[], int &Nvatcan, toado tien[], int &Ntien)
{
	for (int i = 0; i < Nvatcan; i++)
	{
		vatcan[i].y++;

		if (vatcan[i].y > doc)
		{
			Xoa_1_PhanTu (vatcan, Nvatcan, i);
			i--;

			points++;
		}
	}


	for (int i = 0; i < Ntien; i++)
	{
		tien[i].y++;

		if (tien[i].y >= doc)
		{
			Xoa_1_PhanTu (tien, Ntien, i);
			i--;
		}
	}
}


void DieuKhien_Xe (toado &xe)
{
	if (GetAsyncKeyState(VK_LEFT) && xe.x > 2)
	{
		xe.x--;
	}

	if (GetAsyncKeyState(VK_RIGHT) && xe.x < ngang-2)
	{
		xe.x++;
	}
}


void Tao_VatCan (int &ThoiGian_tao_VatCan, int MAX, toado vatcan[], int &Nvatcan)
{
	if (ThoiGian_tao_VatCan <= 0 && rand() % 2)
	{
		ThoiGian_tao_VatCan = MAX;

		vatcan[Nvatcan].y = 0;
		vatcan[Nvatcan].x = rand() % (ngang-3) + 2;
		Nvatcan++;
	}
}


void Tao_Tien (int &ThoiGian_tao_Tien, int MAX, toado tien[], int &Ntien)
{
	if (ThoiGian_tao_Tien <= 0 && rand() % 2)
	{
		ThoiGian_tao_Tien = MAX;

		tien[Ntien].y = 0;
		tien[Ntien].x = rand() % (ngang-1) + 1;
		Ntien++;
	}
}


int Va_Cham (toado xe, toado mang[], int N, int dodai, int dorong)
{
	for (int i = 0; i < N; i++)
	{
		int Y = mang[i].y;
		int X = mang[i].x;

		int Y_xe_giua = abs(xe.y - Y) < dodai;
		int X_xe_giua = abs(xe.x - X) < dorong;

		if (Y_xe_giua && X_xe_giua)
			return i;
	}

	return -1;
}


void An_Tien (toado xe, toado tien[], int &Ntien)
{
	int vitri_tien = Va_Cham (xe, tien, Ntien, 2, 2);

	if (vitri_tien >= 0)
	{
		Xoa_1_PhanTu (tien, Ntien, vitri_tien);
		points = points + 3;
	}
}


int GameOver (toado xe, toado vatcan[], int Nvatcan)
{
	if (Va_Cham (xe, vatcan, Nvatcan, 3, 3) >= 0)
		return true;

	return false;
}