// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE printchar.c
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_PrintChar
//In 1 ky tu duy nhat ra man hinh

#include "syscall.h"

int main()
{
	PrintChar('X');
	Halt();
	return 0;
}
