#pragma once
#include <iostream>
#include <sstream>
#include "PlusMul.h"
#include <fstream>
#include <ostream>
using namespace std;

#define BIT 128
class QInt
{
	char Bit[BIT + 1 + 360];

public:
	//Khởi tạo dãy bit 0 nếu i == 0
	//Khởi tạo dãy bit 1 nếu i != 0
	QInt(int i = 0)
	{
		Bit[BIT] = '\0';
		if (i == 0)
		{
			for (int i = 0; i < BIT; i++)
			{
				Bit[i] = '0';
			}
		}
		else
		{
			for (int i = 0; i < BIT; i++)
			{
				Bit[i] = '1';
			}
		}
		Standardize();
	}
	QInt(char *bit)
	{
		strcpy(Bit, bit);
		Standardize();
	}
	//Gán dãy bit
	void set(char *bit)
	{
		strcpy(Bit, bit);
		Standardize();
	}
	void operator=(QInt A)
	{
		strcpy(Bit, A.Bit);
	}

	//Nhập dãy Bit bằng tay (Test)
	QInt enterBit()
	{
		QInt A;
		cout << "Nhap day 8 bit:";
		/*do
		{*/
		char temp[255];
		cin >> temp;
		A.set(temp);
		/*if (A.isBit())
		break;*/
		A.Standardize();
		/*if (strlen(temp) == BIT)
		{
		A.set(temp);
		if (A.isBit())
		break;
		else
		{

		system("cls");
		cout << "Day khong phai mot day 8 bit, vui long nhap lai!\n";
		cout << "Nhap day 8 bit:";
		}
		}
		else
		{
		system("cls");
		cout << "Day bit qua dai hoac chua du 8 bit, vui long nhap lai!\n";
		cout << "Nhap day 8 bit:";
		}

		} while (1);*/
		*this = A;
		return A;
	}
	//Toán tử nhập xuất
	friend istream& operator>>(istream& is, QInt &x)
	{
		is >> x.Bit;
		return is;
	}
	friend ostream& operator <<(ostream  &os, QInt &x)
	{
		os << x.Bit;
		return os;
	}

	//Shift
	QInt shiftLeft()
	{
		QInt A = *this;

		for (int i = 0; i < BIT - 1; i++)
		{
			A.Bit[i] = A.Bit[i + 1];
		}
		A.Bit[BIT - 1] = '0';
		*this = A;
		return A;
	}
	QInt shiftRight()
	{
		QInt A = *this;

		for (int i = strlen(A.Bit) - 1; i > 0; i--)
		{
			A.Bit[i] = A.Bit[i - 1];
		}
		if (A.Bit[1] == '0')
			A.Bit[0] = '0';
		else
			A.Bit[0] = '1';
		*this = A;
		return A;
	}
	QInt operator<<(QInt &A)
	{
		return A.shiftLeft();
	}
	QInt operator>>(QInt &A)
	{
		return A.shiftRight();
	}

	//Chuẩn hóa dãy bit
	//Thêm Bit cho đủ 128 bit
	void Standardize(int NumOfBit = BIT)
	{
		if (strlen(Bit) < NumOfBit)
		{
			QInt Temp;
			Temp.Bit[NumOfBit] = '\0';
			int k = strlen(Bit);
			int l = NumOfBit;
			for (l; l >= 0; l--)
			{
				Temp.Bit[l] = Bit[k];
				if (k == 0)
					break;
				k--;
			}

			//if (Bit[0] == '1')
			//{
			//	for (int i = l; i >= 0; i--)
			//	{
			//		Temp.Bit[i] = '1';
			//	}
			//}
			//else
			for (int i = l - 1; i >= 0; i--)
			{
				Temp.Bit[i] = '0';
			}

			strcpy(Bit, Temp.Bit);
		}

	}

	//Xoá bớt số 0 ở đầu
	void Reduce()
	{
		string Dec = Bit;
		for (int i = 0; i < Dec.length() - 1; i++)
		{
			if (Dec[i] == '0')
			{
				Dec.erase(0, 1);
				i--;
			}
			else
				break;
		}
		strcpy(Bit, Dec.c_str());
	}

	//Day bit hop le chi gom '0' va '1'
	bool isBit()
	{
		for (int i = 0; i < BIT; i++)
		{
			if (Bit[i] != '0')
			if (Bit[i] != '1')
				return false;
		}
		return true;

	}

	//AND OR XOR NOT
	QInt and(QInt bit)
	{
		QInt res;
		for (int i = 0; i < BIT; i++)
		{
			if (this->Bit[i] == '1' && bit.Bit[i] == '1')
			{
				res.Bit[i] = '1';
			}
			else
			{
				res.Bit[i] = '0';
			}
		}
		*this = res;
		return res;
	}
	QInt or(QInt bit)
	{
		QInt res;
		for (int i = 0; i < BIT; i++)
		{
			if (this->Bit[i] == '1' || bit.Bit[i] == '1')
			{
				res.Bit[i] = '1';
			}
			else
			{
				res.Bit[i] = '0';
			}
		}

		*this = res;
		return res;
	}
	QInt xor(QInt bit)
	{
		QInt res;
		for (int i = 0; i < BIT; i++)
		{
			if (this->Bit[i] == bit.Bit[i])
			{
				res.Bit[i] = '0';
			}
			else
			{
				res.Bit[i] = '1';
			}
		}

		*this = res;
		return res;
	}
	QInt not()
	{
		QInt res;
		for (int i = 0; i < BIT; i++)
		{
			res.Bit[i] = 1 - (this->Bit[i] - '0') + '0';
		}
		*this = res;
		return res;
	}
	QInt operator & (QInt B)
	{
		QInt A = *this;
		*this = A.and(B);
		return A;
	}
	QInt operator | (QInt B)
	{
		QInt A = *this;
		*this = A.or(B);
		return A;
	}
	QInt operator ^ (QInt B)
	{
		QInt A = *this;
		*this = A.xor(B);
		return A;
	}
	QInt operator ~ ()
	{
		QInt A = *this;
		A.not();
		*this = A;
		return A;
	}

	//ROL
	QInt rol()
	{
		QInt A = *this;
		char k;
		k = Bit[0];
		A << A;
		A.Bit[strlen(A.Bit) - 1] = k;
		*this = A;
		return A;
	}
	//ROR
	QInt ror()
	{
		QInt A = *this;
		char k;
		k = Bit[strlen(Bit) - 1];
		A >> A;
		A.Bit[0] = k;
		*this = A;
		return A;
	}

	//--------------------------- Các hàm chuyển đổi -------------------------------
	//Nhị phân sang thập phân
	string  BinToDec()
	{
		bignum<12345>  result = 0;
		QInt A = *this;
		int  sign = 1;
		if (A.Bit[0] == '1')
		{
			sign = -1;
			A = A.getTwoComplement();
		}
		int j = strlen(A.Bit) - 1;
		for (int i = 0; i < strlen(A.Bit); i++)
		{
			long long k = (A.Bit[j] - '0') *pow(2, i);
			bignum<12345> temp = k;
			result += temp;
			j--;
		}
		result *= sign;
		string S = result.toBase10().toString();
		return S;
	}
	//Thập phân sang nhị phân ------------------------------
	string  DecToBin()
	{
		string Dec = Bit;
		//Xoá số 0 ở đầu
		for (int i = 0; i < Dec.length() - 1; i++)
		{
			if (Dec[i] == '0')
			{
				Dec.erase(0, 1);
				i--;
			}
			else
				break;
		}


		string Bin = "";
		int Opponent = 1;
		if (Dec[0] == '-')
		{
			Opponent = -1;
			Dec.erase(0, 1);
		}

		while (Dec != "0")
		{
			if (isOdd(Dec[Dec.length() - 1]))
			{
				Bin = "1" + Bin;
			}
			else
				Bin = "0" + Bin;

			Dec = divByTwo(Dec);
		}
		if (Opponent == -1)
		{
			int i;
			for (i = Bin.length() - 1; i >= 0; i--)
			{
				if (Bin[i] == '1')
				{
					break;
				}
			}

			//Đảo các bit trước đó
			for (int j = i - 1; j >= 0; j--)
			{
				if (Bin[j] == '1')
				{
					Bin[j] = '0';
				}
				else
				{
					Bin[j] = '1';
				}
			}

			for (int k = BIT - Bin.length(); k > 0; k--)
				Bin = "1" + Bin;
		}


		for (int i = 0; i < Bin.length() - 1; i++)
		{
			if (Bin[i] == '0')
			{
				Bin.erase(0, 1);
				i--;
			}
			else
				break;
		}

		//cout << "Xau S:" << S << endl;
		return Bin;
	}
	typedef unsigned long long __Int64;
	//Nhị phân sang hex
	string binaryToHexadecimal(string binary)
	{
		std::string hex, newHex = "";
		//Khai bao iterator reverse de doc chuoi tu sau ra truoc
		std::string::reverse_iterator rIter;

		__Int64 count = 1;

		__Int64 exponent = 0;

		__Int64 total = 0;

		//Duyet chuoi tu sau ra truoc
		for (rIter = binary.rbegin(); rIter != binary.rend(); rIter++)
		{
			//Bo qua nhung bit = 0, tinh tong power cua cac bit = 1
			if (*rIter == '1')
				total += calculatePower(2, exponent);

			//Khi tinh xong mot cum 4 bit hoac khi het chuoi, thi xet tong de chuyen thanh ma Hexa
			if (count == 4 || rIter == binary.rend() - 1)
			{
				if (rIter == binary.rend() - 1 && total == 0)
				{
					break;
				}
				switch (total)
				{
				case 0:
					hex += '0';
					break;
				case 1:
					hex += '1';
					break;
				case 2:
					hex += '2';
					break;
				case 3:
					hex += '3';
					break;
				case 4:
					hex += '4';
					break;
				case 5:
					hex += '5';
					break;
				case 6:
					hex += '6';
					break;
				case 7:
					hex += '7';
					break;
				case 8:
					hex += '8';
					break;
				case 9:
					hex += '9';
					break;
				case 10:
					hex += 'A';
					break;
				case 11:
					hex += 'B';
					break;
				case 12:
					hex += 'C';
					break;
				case 13:
					hex += 'D';
					break;
				case 14:
					hex += 'E';
					break;
				case 15:
					hex += 'F';
					break;
				}

				//Gan mac dinh lai cac bien dem
				count = 0;
				exponent = -1;
				total = 0;
			}

			count++;
			exponent++;
		}

		//Gan chuoi moi kem theo 0x
		//newHex += "0x";

		for (rIter = hex.rbegin(); rIter != hex.rend(); rIter++)
		{
			newHex += *rIter;
		}

		return newHex;
	}
	//Hex sang nhị phân 
	string hexadecimalToBinary(string hex)
	{
		string binary = "";

		//Chuyen phan tu dau de tranh du so 0
		switch (hex[0])
		{
		case '1':
			binary += "1";
			break;
		case '2':
			binary += "10";
			break;
		case '3':
			binary += "11";
			break;
		case '4':
			binary += "100";
			break;
		case '5':
			binary += "101";
			break;
		case '6':
			binary += "110";
			break;
		case '7':
			binary += "111";
			break;
		case '8':
			binary += "1000";
			break;
		case '9':
			binary += "1001";
			break;
		case 'A':
			binary += "1010";
			break;
		case 'B':
			binary += "1011";
			break;
		case 'C':
			binary += "1100";
			break;
		case 'D':
			binary += "1101";
			break;
		case 'E':
			binary += "1110";
			break;
		case 'F':
			binary += "1111";
			break;
		}

		//Duyet tung phan tu cua ma hexa de chuyen thanh binary
		for (int i = 1; i < hex.length(); i++)
		{
			switch (hex[i])
			{
			case '0':
				binary += "0000";
				break;
			case '1':
				binary += "0001";
				break;
			case '2':
				binary += "0010";
				break;
			case '3':
				binary += "0011";
				break;
			case '4':
				binary += "0100";
				break;
			case '5':
				binary += "0101";
				break;
			case '6':
				binary += "0110";
				break;
			case '7':
				binary += "0111";
				break;
			case '8':
				binary += "1000";
				break;
			case '9':
				binary += "1001";
				break;
			case 'A':
				binary += "1010";
				break;
			case 'B':
				binary += "1011";
				break;
			case 'C':
				binary += "1100";
				break;
			case 'D':
				binary += "1101";
				break;
			case 'E':
				binary += "1110";
				break;
			case 'F':
				binary += "1111";
				break;
			}
		}

		return binary;
	}

	//Toán tử cộng trừ nhân chia TRÊN NHỊ PHÂN
	QInt operator+(QInt B)
	{
		QInt A = *this;
		int TEMP, temp = 0;
		char SumValue;
		for (int i = BIT - 1; i >= 0; i--)
		{
			TEMP = 0;
			if (temp > 0)
			{
				TEMP = 1;
				temp--;
			}
			SumValue = ((A.Bit[i] - '0') + (B.Bit[i] - '0') + TEMP) + '0';
			if (SumValue > '2')
			{
				SumValue = '1';
				temp += 1;
			}
			if (SumValue == '2')
			{
				SumValue = '0';
				temp += 1;
			}
			A.Bit[i] = SumValue;
		}
		return A;

	}
	QInt operator-(QInt B)
	{
		QInt A = *this;
		B = B.getTwoComplement();
		return A + B;
	}
	QInt operator*(QInt M)
	{
		QInt A;
		QInt Q = *this;
		int k = BIT;

		Q.Bit[BIT] = '0';
		Q.Bit[BIT + 1] = '\0';

		while (k > 0)
		{
			if (Q.Bit[BIT - 1] == '1' && Q.Bit[BIT] == '0')
			{
				A = A - M;
			}
			if (Q.Bit[BIT - 1] == '0' && Q.Bit[BIT] == '1')
			{
				A = A + M;
			}

			Q = Q.shiftRight();
			Q.Bit[0] = A.Bit[BIT - 1];
			if (A.Bit[BIT - 1] == '1')
			{
				Q.Bit[0] = '1';
			}
			A = A.shiftRight();

			k--;
		}
		Q.Bit[BIT] = '\0';
		//gan Q vao A
		strcat(A.Bit, Q.Bit);
		return A;
	}
	QInt operator/(QInt M)
	{

		//Q/M
		QInt Q = *this;
		//Q>0 A = n bit 0
		QInt A;

		if (Q.Bit[0] == '1')
		{
			Q = Q.getTwoComplement();
			M = M.getTwoComplement();
		}

		//Q<0 A = n bit 1
		QInt Temp(1);
		if (Q.Bit[0] == '1')
			A = Temp;
		int k = BIT;


		while (k > 0)
		{
			A = A.shiftLeft();
			if (Q.Bit[0] == '1')
				A.Bit[BIT - 1] = '1';

			Q = Q.shiftLeft();
			if (M.Bit[0] == '0')
				A = A - M;
			else
				A = A + M;
			if (A.Bit[0] == '1')
			{
				Q.Bit[BIT - 1] = '0';
				if (M.Bit[0] == '0')
					A = A + M;
				else
					A = A - M;
			}
			else
				Q.Bit[BIT - 1] = '1';

			k--;
		}
		//A la du
		return Q;
	}

	//Lấy Bù 2
	QInt getTwoComplement()
	{
		QInt A = *this;
		//Tìm đến số một đầu tiên tính từ cuối về
		int i;
		for (i = strlen(A.Bit) - 1; i >= 0; i--)
		{
			if (A.Bit[i] == '1')
			{
				break;
			}
		}

		//Đảo các bit trước đó
		for (int j = i - 1; j >= 0; j--)
		{
			if (A.Bit[j] == '1')
			{
				A.Bit[j] = '0';
			}
			else
			{
				A.Bit[j] = '1';
			}
		}
		return A;
	}
	//Tính lũy thừa
	__Int64 calculatePower(__Int64 base, __Int64 exponent)
	{
		__Int64 total = 1;

		for (__Int64 index = 0; index < exponent; index++)
			total *= base;

		return total;
	}
	bool isOdd(char s)
	{
		if (s == '1')
			return true;
		if (s == '3')
			return true;
		if (s == '5')
			return true;
		if (s == '7')
			return true;
		if (s == '9')
			return true;
		return false;
	}
	//Chia xâu thập phân cho 2
	string divByTwo(string s)
	{
		string new_s = s;
		int next_add = 0;
		for (int i = 0; i < new_s.length(); i++)
		{
			int add = next_add;
			if (isOdd(new_s[i]))
				next_add = 5;
			else
				next_add = 0;

			char new_char = ((((new_s[i] - '0') / 2) + add) + '0');
			new_s[i] = new_char;
		}
		for (int i = 0; i < new_s.length() - 1; i++)
		{
			if (new_s[i] == '0')
			{
				new_s.erase(0, 1);
				i--;
			}
			else
				break;
		}

		return new_s;
	}


	//Đọc - xử lý file + in file
	bool process(string In_Path = "input.txt", string Out_Path = "output.txt")
	{
		fstream File_In(In_Path, ios::in);
		fstream File_Out(Out_Path, ios::out);

		string Line, Result;
		while (getline(File_In, Line))
		{
			//cout << Line << endl;
			string p[6];
			for (int i = 0; i < 6; i++)
			{
				p[i] = "";
			}

			//Tách từng từ vào mảng p
			int k = 0;
			for (int i = 0; i < Line.size(); i++)
			{
				if (Line[i] == ' ')
					k++;
				else
					p[k] += Line[i];
			}

			//Chỉ số đầu vào và ra 
			string TypeIn, TypeOut;

			//Nếu bắt đầu vs chỉ số 2 (bin)
			if (p[0] == "2")
			{
				TypeIn = p[0];
				beginby2(p, TypeOut, Result);
				Result = convert(Result, TypeIn, TypeOut);//chuyển dãy nhị phân sang các hệ khác
			}
			//Nếu bắt đầu vs chỉ số 10 (dec)
			if (p[0] == "10")
			{
				string Temp_TypeOut = "10";
				if (p[1] == "10" || p[1] == "16" || p[1] == "2")
				{
					Temp_TypeOut = p[1];
				}
				TypeIn = p[0];
				beginby10(p, TypeOut, Result);

				Result = convert(Result, "2", Temp_TypeOut);//chuyển dãy nhị phân sang các hệ khác

				if (Temp_TypeOut == "2")
				{
					QInt A;
					strcpy(A.Bit, Result.c_str());
					A.Standardize();
					Result = A.Bit;
				}
			}
			//Nếu bắt đầu vs chỉ số 16 (hex)
			if (p[0] == "16")
			{
				string Temp_TypeOut = "16";
				if (p[1] == "10" || p[1] == "16" || p[1] == "2")
				{
					Temp_TypeOut = p[1];
				}
				TypeIn = p[0];
				beginby16(p, TypeOut, Result);

				Result = convert(Result, "2", Temp_TypeOut);//chuyển dãy nhị phân sang các hệ khác

				if (Temp_TypeOut == "2")
				{
					QInt A;
					strcpy(A.Bit, Result.c_str());
					A.Standardize();
					Result = A.Bit;
				}
			}
			File_Out << Result << endl;
			Line.clear();
			Result.clear();
		}

		return true;
	}

	//chuyển dãy nhị phân sang các hệ khác
	string convert(string Value, string TypeIn, string TypeOut)
	{
		if (TypeIn == TypeOut)
			return Value;
		if (TypeOut == "10")
		{
			QInt A;
			strcpy(A.Bit, Value.c_str());
			A.Standardize();
			return A.BinToDec();
		}
		if (TypeOut == "16")
		{
			QInt A;
			strcpy(A.Bit, Value.c_str());
			A.Standardize();
			return A.binaryToHexadecimal(Value);
		}

	}
	void beginby2(string p[6], string &TypeOut, string &Result)
	{
		//Không có chỉ số chuyển đổi
		if (p[1] != "10" && p[1] != "16" && p[1] != "2")
		{
			//Chỉ số đầu ra = chỉ số đầu vào
			TypeOut = p[0];
			//Xóa chỉ số trong mảng p
			for (int i = 0; i < 6 - 1; i++)
			{
				p[i] = p[i + 1];
			}
		}

		//Có chỉ số chuyển đổi
		if (p[1] == "10" || p[1] == "16" || p[1] == "2")
		{
			TypeOut = p[1];
			//Xóa chỉ số trong mảng p
			for (int i = 0; i < 6 - 2; i++)
			{
				p[i] = p[i + 2];
			}
		}

		//Chỉ có một giá trị
		if (p[1] == "")
		{
			Result = p[0];
			return;
		}//done


		QInt A, B;
		strcpy(A.Bit, p[1].c_str());//copy p1 cho A(Đối vs các toán tử rol, ror, ~)
		A.Standardize();
		//rol (Rol Left)
		if (p[0] == "rol")
		{
			A.rol();
			A.Reduce();
			Result = A.Bit;
			return;
		}

		//ror (Rol Right)
		if (p[0] == "ror")
		{
			A.ror();
			A.Reduce();
			Result = A.Bit;
			return;
		}

		//~(NOT)
		if (p[0] == "~")
		{
			~A;
			A.Reduce();
			Result = A.Bit;

			return;
		}


		strcpy(A.Bit, p[0].c_str());//copy p0 cho A(Đối vs các toán tử <<, >>)
		A.Standardize();
		//Shift left
		if (p[1] == "<<")
		{
			for (int i = 0; i < stoi(p[2]); i++)
				A << A;

			A.Reduce();
			Result = A.Bit;
			return;

		}
		//Shift right
		if (p[1] == ">>")
		{

			for (int i = 0; i < stoi(p[2]); i++)
				A.shiftRight();
			A.Reduce();

			Result = A.Bit;
			return;

		}

		//copy p2 cho B(Đối vs các toán tử +, -, *, /, &, |,^) 
		//VD: A+B = p[0]+p[2])
		strcpy(B.Bit, p[2].c_str());
		B.Standardize();
		//Cộng Trừ Nhân Chia
		if (p[1] == "+")
		{
			A = A + B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}
		if (p[1] == "-")
		{
			A = A - B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}
		if (p[1] == "*")
		{
			A = A * B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}
		if (p[1] == "/")
		{
			A = A / B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}

		//AND
		if (p[1] == "&")
		{
			A = A & B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}
		//OR
		if (p[1] == "|")
		{
			A = A | B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}
		//XOR
		if (p[1] == "^")
		{
			A = A ^ B;
			A.Reduce();
			Result = A.Bit;
			//cout << Result << endl;
			return;
		}


	}

	void beginby10(string p[6], string &TypeOut, string &Result)
	{
		string Temp = p[1];//chép p1 để kiểm tra có phải là chỉ số
		for (int i = 1; i < 6; i++)
		{
			//Nếu từ khác các ký tự sau
			if (p[i] != "")
			if (p[i] != "+" && p[i] != "-" && p[i] != "*" && p[i] != "/")
			if (p[i] != "ror" && p[i] != "rol" && p[i] != "&" && p[i] != "|")
			if (p[i] != "^" && p[i] != "~" && p[i] != "<<" && p[i] != ">>")
			{
				//Thì chuyển hết về nhị phân
				QInt A;
				strcpy(A.Bit, p[i].c_str());
				A.Standardize();
				p[i] = A.DecToBin();
			}

			if (p[i] == "<<" || p[i] == ">>")
				break;
		}
		p[0] = "2";
		if (Temp == "10" || Temp == "16" || Temp == "2")
		{
			p[1] = Temp;//Nếu p1 là chỉ số, trả lại giá trị ban đầu
		}
		beginby2(p, TypeOut, Result);
	}

	void beginby16(string p[6], string &TypeOut, string &Result)
	{
		string Temp = p[1];//chép p1 để kiểm tra có phải là chỉ số
		for (int i = 1; i < 6; i++)
		{
			//Nếu từ khác các ký tự sau
			if (p[i] != "")
			if (p[i] != "+" && p[i] != "-" && p[i] != "*" && p[i] != "/")
			if (p[i] != "ror" && p[i] != "rol" && p[i] != "&" && p[i] != "|")
			if (p[i] != "^" && p[i] != "~" && p[i] != "<<" && p[i] != ">>")
			{
				//Thì chuyển hết về nhị phân
				p[i] = hexadecimalToBinary(p[i]);
			}

			if (p[i] == "<<" || p[i] == ">>")
				break;
		}
		p[0] = "2";
		if (Temp == "10" || Temp == "16" || Temp == "2")
		{
			p[1] = Temp;//Nếu p1 là chỉ số, trả lại giá trị ban đầu
		}
		beginby2(p, TypeOut, Result);
	}
};



