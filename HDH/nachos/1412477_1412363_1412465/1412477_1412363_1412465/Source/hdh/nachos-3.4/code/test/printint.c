// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE printint.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_PrintInt
//Dung de int mot so nguyen ra man hinh

#include "syscall.h"

int main()
{
	int number = -4;
	PrintString("\nSo nguyen in ra la: ");
	PrintInt(number);	// Goi ham PrintInt in thu mot so nguyen
	Halt();
	return 0;
}
