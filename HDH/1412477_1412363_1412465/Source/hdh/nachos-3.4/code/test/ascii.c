// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE ascii.c
//La chuong trinh in ra cac ky tu co ma ASCII tu 32 -> 127

#include "syscall.h"

int main()
{
	int i;
	PrintString("\n--------------------------ASCII TABLE----------------------------");
	PrintString("\nTong cong 95 ki tu (TU 32 -> 127): ");
	PrintString("\n");
	for (i = 32; i <= 127; i++)
	{
		PrintChar(i);	// Su dung ham PrintChar de in cac ki tu
	}
	PrintString("\n Co the viet User Program khac de in them tuy y\n-----------------------------------------------------------");
	Halt();	
	return 0;
}
