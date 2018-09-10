#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "game.h"
#include "Mang.h"
#include "Ham.h"
#include "Diem.h"

int points = 0;

void Tang_DoKho (int &ThoiGian_sleep, int &MAX_ThoiGian_tao_VatCan, int &MAX_ThoiGian_tao_Tien);


int main()
{
	srand (time(NULL));

	int a[doc+5][ngang+1];

	toado xe = {doc-2, (ngang+1)/2};
	toado vatcan[10];	int Nvatcan = 0;
	toado tien[10];		int Ntien = 0;


	int MAX_ThoiGian_tao_VatCan = 3000;
	int MAX_ThoiGian_tao_Tien = 6000;

	int ThoiGian_tao_VatCan = MAX_ThoiGian_tao_VatCan;
	int ThoiGian_tao_Tien = MAX_ThoiGian_tao_Tien;


	int ThoiGian_sleep = 300;

	
	int thua_game = 0;
	while (!GetAsyncKeyState(13) && thua_game == 0)
	{
		XoaManHinh();

		ThoiGian_tao_VatCan -= ThoiGian_sleep;
		Tao_VatCan (ThoiGian_tao_VatCan, MAX_ThoiGian_tao_VatCan, vatcan, Nvatcan);

		ThoiGian_tao_Tien -= ThoiGian_sleep;
		Tao_Tien (ThoiGian_tao_Tien, MAX_ThoiGian_tao_Tien, tien, Ntien);

		DiChuyen_Xuong (vatcan, Nvatcan, tien, Ntien);
		An_Tien (xe, tien, Ntien);

		DieuKhien_Xe (xe);

		Gan_TatCa_vao_Mang (a, xe, vatcan, Nvatcan, tien, Ntien);
		InRaManHinh (a);

		if (GameOver(xe, vatcan, Nvatcan))
			thua_game = 1;

		Tang_DoKho (ThoiGian_sleep, MAX_ThoiGian_tao_VatCan, MAX_ThoiGian_tao_Tien);
		Sleep (ThoiGian_sleep);
	}
	
	getch();

	if (thua_game)
	{
		XoaManHinh();
		printf ("GAME OVER \n\n\n");
		printf ("Diem cua ban la %d \n\n", points);
		Luu_Diem();
		getch();
	}
	
	getch();
}


void Tang_DoKho (int &ThoiGian_sleep, int &MAX_ThoiGian_tao_VatCan, int &MAX_ThoiGian_tao_Tien)
{
	if (points > 180)
	{
		ThoiGian_sleep = 20;
		MAX_ThoiGian_tao_VatCan = 80;
		MAX_ThoiGian_tao_Tien = 150;
	}
	else if (points > 120)
	{
		ThoiGian_sleep = 30;
		MAX_ThoiGian_tao_VatCan = 140;
		MAX_ThoiGian_tao_Tien = 220;
	}
	else if (points > 70)
	{
		ThoiGian_sleep = 50;
		MAX_ThoiGian_tao_VatCan = 200;
		MAX_ThoiGian_tao_Tien = 400;
	}
	else if (points > 50)
	{
		ThoiGian_sleep = 70;
		MAX_ThoiGian_tao_VatCan = 400;
		MAX_ThoiGian_tao_Tien = 800;
	}
	else if (points > 30)
	{
		ThoiGian_sleep = 100;
		MAX_ThoiGian_tao_VatCan = 600;
		MAX_ThoiGian_tao_Tien = 1000;
	}
	else if (points > 15)
	{
		ThoiGian_sleep = 200;
	}
	else if (points > 6)
	{
		MAX_ThoiGian_tao_VatCan = 2000;
		MAX_ThoiGian_tao_Tien = 4000;
	}
}