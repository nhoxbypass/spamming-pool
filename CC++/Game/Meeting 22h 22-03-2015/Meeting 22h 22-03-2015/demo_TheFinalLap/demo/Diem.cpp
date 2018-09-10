#include <stdio.h>
#include <string.h>
#include "Diem.h"

extern int points;

#define FileName "Points.txt"


void Xoa_XuongHang (char s[30])
{
	if (s[strlen(s)-1] == '\n')
		s[strlen(s)-1] = NULL;
}


void Doc_Diem (char danhsach[][30], int diem[], int &n)
{
	FILE* f = fopen (FileName, "rt");
	if (f == NULL)
		return;

	fscanf (f, "%d ", &n);
	for (int i = 0; i < n; i++)
	{
		fgets (danhsach[i], 30, f);
		Xoa_XuongHang (danhsach[i]);
		fscanf (f, "%d ", &diem[i]);
	}
	fclose (f);
}


void Luu_Diem ()
{
	int n = 0;
	char danhsach[20][30];
	int diem[20];
	Doc_Diem (danhsach, diem, n);
	
	char name[30] = "";
	
	while (name[0] == NULL)
	{
		printf ("Nhap ten cua ban: ");
		fflush (stdin);	gets (name);
	}

	strcpy (danhsach[n], name);
	diem[n] = points;
	n++;
	
	// sort


	FILE* f = fopen (FileName, "wt");
	
	fprintf (f, "%d\n", n);
	for (int i = 0; i < n; i++)
	{	
		fprintf (f, "%s\n", danhsach[i]);
		fprintf (f, "%d\n", diem[i]);
	}

	fclose (f);
}