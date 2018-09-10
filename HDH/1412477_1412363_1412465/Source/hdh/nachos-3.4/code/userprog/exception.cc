//
//	DH KHOA HOC TU NHIEN
// 	HE DIEU HANH TH2014/3
// 	DOAN HIEU TAM		-	1412477
// 	TRAN THI NHA		-	1412363
// 	NGUYEN DINH SON		-	1412465
//
//	FILE exception.cc
//
//	La diem khoi dau de Chuong trinh nguoi dung ket noi vao loi hat nhan cua Nachos
//	Co 2 loai truong hop co the gay ra su dieu khien
//	tu chuong trinh nguoi dung:
//
//	syscall -- Ma nguon cua chuong trinh nguoi dung goi mot thu tuc Systemcall
//	trong loi cua Nachos. Sau khi da hoan thien, cac ham xu ly chung toi ho tro nhu sau:
//	"Halt", "Create", "ReadInt", "PrintInt", "ReadChar", "PrintChar", "ReadString", "PrintString", "Help", "Ascii", "BubbleSort"
//
//	exceptions -- Ma nguon cua user lam mot so thao tac ma CPU khong the handle
//	Vi du, truy cap vao bo nho khong ton tai, loi so hoc,
//	.v.v...
//
//	Interrupts (thu ma cung co the gay ra su dieu khien tu ma nguon cua nguoi dung
//	toi hat nhan loi Nachos) da duoc handled o 1 noi khac
//
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "synchcons.h"
#define MaxFileLength 32


//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	Voi cac System calls, de thuan tien ta quy uoc nhu sau:
//
// 	Ma systemcall -- thanh ghi r2
//	Tham so arg1 -- thanh ghi r4
//	Tham so arg2 -- thanh ghi r5
//	Tham so arg3 -- thanh ghi r6
//	Tham so arg4 -- thanh ghi r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------


// Input: Khong gian dia chi User(int) - gioi han cua buffer(int)
// Output: Bo nho dem Buffer(char*)
// Cong dung: Sao chep vung nho User sang vung nho System
char* User2System(int virtAddr, int limit)
{
	int i; //chi so index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; //can cho chuoi terminal
	if (kernelBuf == NULL)
		return kernelBuf;

	memset(kernelBuf, 0, limit + 1);

	//printf("\n Filename u2s:"); 
	for (i = 0; i < limit; i++)
	{
		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		//printf("%c",kernelBuf[i]); 
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

// Input: Khong gian vung nho User(int) - gioi han cua buffer(int) - bo nho dem buffer(char*)
// Output: So byte da sao chep(int)
// Cong dung: Sao chep vung nho System sang vung nho User
int System2User(int virtAddr, int len, char* buffer)
{
	
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0;
	do
	{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}


//Day thanh ghi Program counter cua he thong ve sau 4 byte de tiep tuc ghi
void IncreasePC()
{
	//Tang program counter (thay the Halt)
	machine->registers[PrevPCReg] = machine->registers[PCReg];
	machine->registers[PCReg] = machine->registers[NextPCReg];
	machine->registers[NextPCReg] += 4;
}


void ExceptionHandler(ExceptionType which)
{
    	int type = machine->ReadRegister(2);
	// Bien toan cuc cho lop SynchConsole
	SynchConsole gSynchConsole;

	//Bat dau
	switch(which)
	{
		case NoException:
		break;

		case PageFaultException:
		DEBUG('a', "\nNo valid translation found");
		printf("\nNo valid translation found");
		interrupt->Halt();
		break;

		case ReadOnlyException:
		DEBUG('a', "\nWrite attempted to page marked read-only");
		printf("\nWrite attempted to page marked read-only");
		interrupt->Halt();
		break;

		case BusErrorException:
		DEBUG('a', "\nTranslation resulted invalid physical address");
		printf("\nTranslation resulted invalid physical address");
		interrupt->Halt();
		break;

		case AddressErrorException:
		DEBUG('a', "\nUnaligned reference or one that was beyond the end of the address space");
		printf("\nUnaligned reference or one that was beyond the end of the address space");
		interrupt->Halt();
		break;

		case OverflowException:
		DEBUG('a', "\nInteger overflow in add or sub.");
		printf("\nInteger overflow in add or sub.");
		interrupt->Halt();
		break;

		case IllegalInstrException:
		DEBUG('a', "\nUnimplemented or reserved instr.");
		printf("\nUnimplemented or reserved instr.");
		interrupt->Halt();
		break;

		case NumExceptionTypes:
		DEBUG('a', "\nNumber exception types");
		printf("\nNumber exception types");
		interrupt->Halt();
		break;

		case SyscallException:
		{
			switch(type)
			{
				case SC_Halt:
				{
					// Input: Khong co
					// Output: Thong bao tat may
					// Cong dung: Tat HDH
					DEBUG('a', "\nShutdown, initiated by User program. ");
					printf("\nShutdown, initiated by User program. ");
					interrupt->Halt();
					return;
				}
				
				case SC_Create:
				{
					// Input: Ten file(char*)
					// Output: -1 = Loi, 0 = Thanh cong
					// Cong dung: Tao ra file voi tham so la ten file
					int virtAddr;
					char* fileName;
					DEBUG('a', "\n SC_Create called ...\n Reading virtual address of filename...");
	
					virtAddr = machine->ReadRegister(4); //Doc dia chi cua file tu thanh ghi R4
					DEBUG('a', "\n Reading filename.");
					
					//Sao chep khong gian bo nho User sang System, voi do dang toi da la (32 + 1) bytes
					fileName = User2System(virtAddr, MaxFileLength + 1); 
			
					if (fileName == NULL) //Neu khong doc duoc
					{
						printf("\n Not enough memory in system");
						DEBUG('a', "\n Not enough memory in system");
						machine->WriteRegister(2, -1); //Return -1 vao thanh ghi R2
						delete fileName; //Clear bo nho
						IncreasePC();
						return;
					}

					DEBUG('a', "\nFinish reading filename.");

					if (!fileSystem->Create(fileName, 0)) //Tao file bang ham Create cua fileSystem, tra ve ket qua
					{
						//Tao file that bai
						printf("\n Error create file '%s'", fileName);
						machine->WriteRegister(2, -1); //Return ket qua -1 vao thanh ghi R2
						delete fileName;
						IncreasePC();
						return;
					}
			
					//Tao file thanh cong
					machine->WriteRegister(2, 0); //Return ket qua 0 vao thanh ghi R2
					delete fileName;
					IncreasePC(); //Day thanh ghi lui ve sau de tiep tuc ghi 
					return;
					break;
				}
				

				case SC_ReadInt:
				{
					// Input: Khong co
					// Output: So nguyen (kieu Int)
					// Cong dung: Doc mot so nguyen do nguoi dung nhap vao

					int maxBytes = 255; // So byte toi da
					char* buffer = new char[255]; // Bo dem cho chuoi nhap vao
					int numBytes = gSynchConsole.Read(buffer, maxBytes); // Goi ham Read cua SynchConsole, tra ve so byte doc duoc
					bool negative = false; //Flag de xet gia tri am/duong cua so Int
					
					//Xet phan tu dau chuoi nhap vao, xem neu la dau '-' thi la so am
					if (buffer[0] == '-')
					{
						negative = true; // Neu am co bang 1
					}

					//Kiem tra co phai so thap phan (dau cham dong)
					for (int i = negative ? 1:0; i < numBytes; i++) //Vong lap, neu la so am thi chay tu i = 1 (bo qua dau '-')
					{
						if (buffer[i] == '.') //Tim dau cham, de xet cac ky tu con lai (phan thap phan)
						{
							// 9.00 van duoc xem la so nguyen
							// Kiem tra so co dang n.00000 nhu tren hay khong
							int value = 0;
							for (int j = i + 1; j < numBytes; j++)
							{
								if (buffer[j] != '0') //Co so khac '0' o phan thap phan
								{
									//Khong phai la so nguyen
									machine->WriteRegister(2, 0); //Return 0 vao thanh ghi R2
									
									delete buffer; //clear bo nho
									IncreasePC(); 
									return;
								}
							}

							//La so nguyen, lay gia tri phan nguyen, bo phan thap phan (day so 00000)
							// Lan luot xet tung ki tu va doi sang so nguyen
							// Chuyen thanh ca day so bang cong thuc: result = result*10 + so don vi tiep theo tu buffer
							for (int j = negative ? 1:0; j < i; j++)
							{
								//buffer la chuoi nen phai - 48 (tuong duong - '0') de ra so
								value = (buffer[j] - 48) + value * 10; 
							}

							if (negative)  
								value *= (-1); // Neu la so am thi nhan ket qua voi -1
							
							machine->WriteRegister(2, value); // Tra ve ket qua so nguyen

							delete buffer;
							IncreasePC(); 
							return;
						}

						// Xu ly truong hop nhap vao ky tu khong phai la so
						else if (buffer[i] < '0' || buffer[i] > '9')
						{
							// Return 0 vao thanh ghi R2
							machine->WriteRegister(2, 0);

							delete buffer;
							IncreasePC();
							return;
						}
					}

					//Khong phai so thap phan dau cham dong.
					int value = 0;
					
					for (int i = negative ? 1:0; i < numBytes; i++)
					{
						value = (buffer[i] - 48) + value * 10;
					}

					if (negative)  
						value *= (-1); 

					machine->WriteRegister(2, value); 

					delete buffer;
					IncreasePC();
					return;
					break;
				}

				case SC_PrintInt:
				{	
					// Input: So nguyen(int)
					// Output: So nguyen(char*)
					// Cong dung: In mot so nguyen la tham so truyen vao ra man hinh

					int number = machine->ReadRegister(4); //Lay gia tri so nguyen tu thanh ghi R4
					bool negative = false; //Flag xet gia tri am/duong cua so Int					
					int countNum = 0; //Do dai cua so Int
					int index = 0; //Chi so de duyet va chep tung chu so sang chuoi

					//Neu so vua nhap la so 0
					if (number == 0)
					{
						gSynchConsole.Write("0", 1); //Goi ham Write cua SynchConsole de in ra so 0
						IncreasePC();
						return;
					}

					//Xet truong hop la so am
					if (number < 0)
					{
						negative = true; //Bat flag
						index = 1;
						number *= -1;
					}

					//Dem so chu so
					int temp = number; //Bien tam luu so Int
					while (temp)
					{
						countNum++;
						temp /= 10;
					}

					// Tao ra mot chuoi co do dai la so chu so dem duoc
					char* buffer = new char[countNum + index + 1]; 
			
					// Tach lan luot tung ky tu tu sau ra truoc
					// Chuyen so int sang chuoi ky tu bang cong thuc: char = number % 10 + '0'; number = number/10
					for (int i = countNum + index - 1; i >= index; i--)
					{
						buffer[i] = number % 10 + 48; //48 la ma ascii cua ky tu '0'
						number /= 10;
					}

					//Them 1 byte cho ky tu ket thuc chuoi '\0', va 1 byte de chua dau '-' neu la so am
					if (!negative)
					{
						buffer[countNum] = '\0'; // Neu khong phai la so am thi gan '\0' ket thuc chuoi 
					}
					else
					{
						// Neu la so am thi gan ki tu dau la '-' va ki tu '\0' ket thuc chuoi
						buffer[0] = '-';
						buffer[countNum + 1] = '\0';
					}					

					//Goi ham Write cua SynchConsole de in ra chuoi so, voi do dai la (countNum + index) bytes
					gSynchConsole.Write(buffer, countNum + index);
					delete buffer;
					IncreasePC();
					return;
					break;
				}

				case SC_ReadChar:
				{
					//Input: Khong co
					//Output: Duy nhat 1 ky tu (char)
					//Cong dung: Doc mot ky tu tu nguoi dung nhap
					int maxBytes = 255;
					char* buffer = new char[255];
					int numBytes = gSynchConsole.Read(buffer, maxBytes);

					if(numBytes > 1) //Neu nhap nhieu hon 1 ky tu thi khong hop le
					{
						printf("Chi duoc nhap duy nhat 1 ky tu!");
						DEBUG('a', "\nERROR: Chi duoc nhap duy nhat 1 ky tu!");
						machine->WriteRegister(2, 0);
					}
					else if(numBytes == 0) //Ky tu rong
					{
						printf("Ky tu rong!");
						DEBUG('a', "\nERROR: Ky tu rong!");
						machine->WriteRegister(2, 0);
					}
					else
					{
						//Chuoi vua lay co dung 1 ky tu, lay ky tu o index = 0, return vao thanh ghi R2
						char c = buffer[0];
						machine->WriteRegister(2, c);
					}

					delete buffer;
					IncreasePC();
					return;
					break;
				}

				case SC_PrintChar:
				{
					// Input: Ki tu(char)
					// Output: Ki tu(char)
					// Cong dung: Xuat mot ki tu la tham so arg ra man hinh
					char c = (char)machine->ReadRegister(4); // Doc ki tu tu thanh ghi r4
					gSynchConsole.Write(&c, 1); // In ky tu tu bien c, 1 byte
					IncreasePC();
					break;
				}

				case SC_ReadString:
				{
					// Input: Buffer(char*), do dai toi da cua chuoi nhap vao(int)
					// Output: Khong co
					// Cong dung: Doc vao mot chuoi voi tham so la buffer va do dai toi da
					int address = machine->ReadRegister(4); // Lay dia chi buffer tu r4
					int length = machine->ReadRegister(5); // Lay do dai toi da cua chuoi nhap vao tu r5
					char *buffer = User2System(address, length);;
					int l = gSynchConsole.Read(buffer, length);//Doc chuoi
					System2User(address, l, buffer);// Copy chuoi tu Kernel Space sang vung nho User Space		
					delete buffer; 
					IncreasePC();		
					break;

					
				}

				case SC_PrintString:
				{
					// Input: Buffer(char*)
					// Output: Chuoi doc duoc tu buffer(char*)
					// Cong dung: Xuat mot chuoi la tham so buffer truyen vao ra man hinh
					int virtAddr = machine->ReadRegister(4);// Lay dia chi cua tham so buffer tu r4
					char* buffer = User2System(virtAddr, 255); // Copy chuoi tu vung nho User Space sang Kernel Space 
												//voi bo dem buffer dai 255 ki tu
					int length = 0;
					while (buffer[length] != 0) 
						length++; // Lay do dai that cua chuoi
					gSynchConsole.Write(buffer, length + 1); // Goi ham Write cua SynchConsole de in chuoi
									
					delete buffer; 
					IncreasePC();	
					break;
				}      
                                    
				
				default:
					IncreasePC(); //Tang Program Counter 
					return;					
				break;
					
			}

		}
	}
	
}
