#include <stdio.h>
#include "Mang.h"

extern int points;


void KhoiTao (int a[][ngang+1])
{
	for (int i = 0; i < doc; i++)
		for (int j = 0; j <= ngang; j++)
			if (j == 0 || j == ngang)
				a[i][j] = '|';
			else
				a[i][j] = ' ';
}


void Gan_TatCa_vao_Mang (int a[][ngang+1], toado xe, toado vatcan[], int Nvatcan, toado tien[], int Ntien)
{
	KhoiTao (a);
	
	int y = 0, x = 0;
	y = xe.y;
	x = xe.x;


	a[y][x] = 'X';
	a[y][x-1] = a[y][x+1] = '|';
	a[y-1][x-1] = a[y-1][x+1] = a[y+1][x-1] = a[y+1][x+1] = 'o';


	for (int i = 0; i < Nvatcan; i++)
	{
		y = vatcan[i].y;
		x = vatcan[i].x;

		a[y][x] = a[y][x-1] = a[y][x+1] = a[y-1][x-1] = a[y-1][x+1] = a[y+1][x-1] = a[y+1][x+1] = 219;
	}

	for (int i = 0; i < Ntien; i++)
	{
		y = tien[i].y;
		x = tien[i].x;

		a[y][x] = '$';
	}
}


void Xoa_1_PhanTu (toado mang[], int &n, int vitri)
{
	if (n <= 0)
		return;

	for (int i = vitri; i < n-1; i++)
		mang[i] = mang[i+1];

	n--;

}


void InRaManHinh (int a[][ngang+1])
{
	for (int i = 0; i < doc; i++)
	{
		for (int j = 0; j <= ngang; j++)
			printf ("%c", a[i][j]);

		if (i < doc-1)
			printf ("\n");
	}

	printf ("Points = %d", points);
}