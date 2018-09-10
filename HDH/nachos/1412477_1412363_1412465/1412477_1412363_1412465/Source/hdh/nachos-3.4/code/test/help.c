// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE help.c
// La User Program dung de gioi thieu nhom
//In ra mo ta van tat ve chuong trinh sort va ascii

#include "syscall.h"

int main()
{
	// Goi cac ham PrintString de in chuoi gioi thieu ra man hinh
	PrintString("\nDH Khoa hoc tu nhien TPHCM");
	PrintString("\nHe Dieu Hanh TH2014");
	PrintString("\n");
	PrintString("\n------------------------ HELP FILE -------------------------");
	PrintString("\n");
	PrintString("\nThong tin nhom:");
	PrintString("\nNhom gom co 3 thanh vien:");
	PrintString("\nDoan Hieu Tam - 1412477");
	PrintString("\nTran Thi Nha - 1412363");
	PrintString("\nNguyen Dinh Son - 1412465");
	PrintString("\n");
	PrintString("\nMo ta van tat ve chuong trinh Ascii: ");
	PrintString("\nChuong trinh dung de in ra bang ma Ascii gom 95 ki tu (tu 32 -> 127).");
	PrintString("\nDuoc cai dat bang cach su dung vong lap (for statement) va goi ham PrintChar(char) de in ra.");
	PrintString("\n");
	PrintString("\nMo ta van tat ve chuong trinh Sort:");
	PrintString("\nChuong trinh cho phep nguoi dung nhap vao mang n so nguyen (voi 1 <= n <= 100).");
	PrintString("\nDuoc cai dat bang cach su dung thuat toan sap xep noi bot (Bubble sort) de sap xep mang va goi cac ham ReadInt(), PrintInt(int) de nhap va in mang.");
	PrintString("\n");
	PrintString("\nChuc thay co mot ngay lam viec vui ve :D");
	PrintString("\n");
	PrintString("\n-----------------------------------------------------------");
	Halt();
	return 0;
}
