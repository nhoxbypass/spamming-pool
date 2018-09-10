// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE printstring.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_PrintString
//In chuoi ra man hinh

#include "syscall.h"

int main()
{
	PrintString("\nHe dieu hanh TH2014/3");
	PrintString("\nDummy NachOS!\n");
	Halt();	
	return 0;
}

