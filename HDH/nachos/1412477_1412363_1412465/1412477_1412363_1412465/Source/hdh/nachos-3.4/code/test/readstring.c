// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE readstring.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_ReadString
//Cho phep nguoi dung nhap 1 chuoi ky tu (sau do xuat chuoi de kiem tra)

#include "syscall.h"

int main()
{
	char str[255];
	PrintString("\nHay nhap mot chuoi: ");
	ReadString(str, 255);
	PrintString("Chuoi vua nhap la: ");
	PrintString(str);
	Halt();
	return 0;
}


