// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE CREATE.C
// La User Program dung de kiem thu tinh dung dan cua chuong System call SC_Create
//Tao 1 file bat ky. Tra ve ket qua 

#include "syscall.h"

int main()
{
	if (Create("IceTea.txt") == -1) {
		PrintString("\nKhong tao duoc tap tin!\n");
	}	
	else {
		PrintString("\nTao tap tin thanh cong!\n");
	}
	Halt();
	return 0;
}


