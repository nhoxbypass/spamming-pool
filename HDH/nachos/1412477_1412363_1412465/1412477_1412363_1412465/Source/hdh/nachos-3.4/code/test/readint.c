// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE readint.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_ReadInt
//Doc vao 1 so nguyen, va xuat ra de kiem tra

#include "syscall.h"

int main()
{
	int result;
	PrintString("\nMoi ban nhap so nguyen: ");
	result = ReadInt();	// Goi ham ReadInt de doc so nguyen vua nhap
	PrintString("So nguyen ban vua nhap la: ");
	PrintInt(result);	// Goi ham PrintInt de in so nguyen vua nhap
	
	Halt();
	return 0;
}
