// DH KHOA HOC TU NHIEN
// HE DIEU HANH TH2014/3
// DOAN HIEU TAM	-	1412477
// TRAN THI NHA		-	1412363
// NGUYEN DINH SON	-	1412465

// FILE bubblesort.c

//Chuong trinh Bubble sort duoc cai dat de sap xep mang cac so nguyen co so phan tu la n
//Voi 1 <= n <= 100
//Su dung ReadInt() de nhapn va cac phan tu mang
//Su dung PrintString(char[]) va PrintInt(int) de xuat thong tin ra man hinh

#include "syscall.h"

int main()
{
	int nMax = 100; int n = 0; // nMax la so phan tu toi da, n la so phan tu nhap vao
	int array[100];  // Khai bao mang so nguyen co 100 phan tu
	int index;

	PrintString("\n------------------------ BUBBLE SORT --------------------------\n");
	
	do
	{
		PrintString("Nhap so phan tu cua mang (1 <= n <= 100): ");
		n = ReadInt(); // Goi ham ReadInt de nhap so luong phan tu cua mang (n)
	} while (n < 1 || n>nMax); //Nhap n den khi nao nhan dc n hop le

	PrintString("Nhap gia tri cac phan tu trong mang:\n");

	for (index = 0; index < n; index++)
	{
		//PrintString("--> Array["); PrintInt(index); PrintString("]: "); <-- Khong hieu sao them dong nay cho dep ma lai loi ASSERTION FAILED
		array[index] = ReadInt(); // Goi ham ReadInt de nhap cac phan tu cua mang
	}

	PrintString("Mang truoc khi sap xep: ");
	for (index = 0; index < n; index++)
	{
		PrintInt(array[index]);	// Goi ham PrintInt de in cac phan tu cua mang
		PrintString(" ");	
	}
	PrintString("\n");

	// Dung thuat toan Bubble sort de sap mang tang dan
	for (index = 0; index < n - 1; index++) 
	{
		int j;
		for (j = n - 1; j > index; j--)
		{
			if (array[j] < array[j - 1])
			{
				int tmp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = tmp;
			}
		}
	}

	PrintString("Mang da sap xep tang dan: ");
	for (index = 0; index < n; index++)
	{
		PrintInt(array[index]);	// Goi ham PrintInt de in cac phan tu cua mang
		PrintString(" ");
	}

	PrintString("\n----------------------------------------------------------");
	Halt();
	return 0;
}
