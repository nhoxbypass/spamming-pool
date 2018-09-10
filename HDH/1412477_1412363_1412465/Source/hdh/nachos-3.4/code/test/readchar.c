// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE readchar.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_ReadChar
//Doc vao 1 ky tu, va xuat ra de kiem tra

#include "syscall.h"

int main()
{
	char result;
	PrintString("\nMoi ban nhap 1 ki tu: ");
	result = ReadChar();	// Goi ham ReadChar de doc ki tu nhap vao
	PrintString("Ki tu ban vua nhap la: ");
	PrintChar(result);		// Goi ham PrintChar de in ki tu vua nhap 
	
	Halt();	
	return 0;
}
