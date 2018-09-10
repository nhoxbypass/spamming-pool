// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


//Declaring functions prototypes
void splitName(char* InStr, char* sur, char* first);


int _tmain(int argc, _TCHAR* argv[])
{
	//Declare variables
	FILE* fpIn;
	FILE* fpOut;
	FILE* fpOutAll;
	char cId[8];
	char cName[31];
	char cGender[4];
	char cDOB[11];
	float fMath, fChem, fPhys;
	float fAvg;


	//Open file and work if open success
	fpIn = fopen("DSSV.txt", "r+");
	if (fpIn == NULL)
	{
		cout << "Error open file!" << endl;
	}
	else
	{
		//Open file 'BANGDIEM.html' to write the table
		fpOutAll = fopen("BANGDIEM.html", "w");
		fprintf(fpOutAll, "<html>\n<title>Bang diem tong ket</title>\n<body>\n<p style = 'text-align:center'>\n<b>\n<span style = 'font-size:20.0pt;font-family:""Tahoma""'>\nBANG DIEM TONG KET\n</span>\n</b>\n</p>\n<table align = center border = 1 cellspacing = 0 cellpadding = 5>\n<tr>\n<td align = center><b>MSSV</b></td>\n<td align = center><b>Ho va ten lot</b></td>\n<td align = center><b>Ten</b></td>\n<td align = center><b>Ngay sinh</b></td>\n<td align = center><b>Gioi tinh</b></td>\n<td align = center><b>Diem trung binh</b></td>\n<td align = center><b>Chi tiet</b></td>\n</tr>");
		char cSurName[20];
		char cFirstName[11];
		char cOutPath[13];


		//Read the input file until end of file and find data
		while (feof(fpIn) == 0)
		{
			//Read data from input file to variable
			fscanf(fpIn, "%[^-] -%[^(] (%[^,], %[^)])\t %f \t %f \t %f \n", &cId, &cName, &cDOB, &cGender, &fMath, &fPhys, &fChem);
			
			
			//Calculate average point of students and print to console to check data
			fAvg = (fMath + fPhys + fChem) / 3;
			printf("%s(%s, %s, %s) with the point average: %.2f\n", cName, cId, cGender, cDOB, fAvg);


			//Split Full name into first name and surname to print to file 'BANGDIEM.html'
			splitName(cName, cSurName, cFirstName);
			fprintf(fpOutAll, "<tr>\n<td>%s </td>\n<td>%s</td>\n<td>%s</td>\n<td align = center>%s </td >\n<td align = center>%s</td>\n<td align = center>%.2f</td>\n<td align = center><a href = ""%s.html"">Xem diem</a></td>\n</tr>",cId,cSurName,cFirstName,cDOB,cGender,fAvg,cId);
			

			//Create the path of file 'BANGDIEMCHITIET' of every student and open file to write data
			strcpy(cOutPath, cId);
			strcat(cOutPath, ".html");
			fpOut = fopen(cOutPath, "w");
			fprintf(fpOut,"<html>\n<title>Bang diem chi tiet</title>\n<body>\n<p style = 'text-align:center'>\n<b>\n<span style = 'font-size:20.0pt;font-family:""Tahoma""'>\nBANG DIEM CHI TIET\n<br>\nSinh viên : %s(%s)\n</span>\n</b>\n</p>\n<table align = center border = 1 cellspacing = 0 cellpadding = 5>\n<tr>\n<td align = center><b>Toan<b></td>\n<td align = center><b>Ly</b></td>\n<td align = center><b>Hoa</b></td>\n<td align = center><b>Diem trung binh</b></td>\n</tr>\n<tr>\n<td align = center>%.2f</td>\n<td align = center>%.2f </td>\n<td align = center>%.2f </td>\n<td align = center>%.2f</td>\n</tr>\n</table>\n</body>\n</html>",cName,cId,fMath, fPhys,fChem,fAvg );
			

			//Finish write data, notify if write success. Close file and continue to data of other students
			fclose(fpOut);
			printf("Written to file! \n \n");

		}

		
		//Finish read write data, close all file and end program
		fclose(fpOutAll);
			fclose(fpIn);
		
	}
	
		


	system("pause");
	return 0;
}



void splitName(char* InStr, char* sur, char* first)
{
	int flag;
	int j = 0;
	char tmp[11];

	
	for (int i = strlen(InStr) -2; i >= 0; i--)
	{
		if (InStr[i] != ' ')
		{
			tmp[j] = InStr[i];
			j++;

		}
		else
		{
			tmp[j] = '\0';
			flag = i;
			break;

		}
	}

	j = 0;
	for (int i = strlen(tmp) - 1; i >= 0; i--)
	{
		first[j] = tmp[i];
		j++;

	}
	first[j] = '\0';

	for (j = 0; j < flag; j++)
	{
		sur[j] = InStr[j];
	}
	sur[flag] = '\0';
}