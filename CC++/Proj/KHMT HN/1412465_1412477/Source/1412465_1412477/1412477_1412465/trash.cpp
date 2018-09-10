#include "stdafx.h"
#include "CalBit.h"
//
//#include <iostream>
//#include <string>
//
//typedef unsigned long long uInt64;
//
//uInt64 calculatePower(uInt64, uInt64);
//uInt64 binaryToDecimal(std::string);
//uInt64 hexadecimalToDecimal(std::string);
//std::string decimalToBinary(uInt64);
//std::string binaryToHexadecimal(std::string);
//
//uInt64 calculatePower(uInt64 base, uInt64 exponent)
//{
//	uInt64 total = 1;
//
//	for (uInt64 iter = 0; iter < exponent; iter++)
//		total *= base;
//
//	return total;
//}
//
//uInt64 binaryToDecimal(std::string binary)
//{
//	uInt64 decimal = 0;
//	uInt64 exponent = 0;
//	std::string::reverse_iterator iter;
//
//	for (iter = binary.rbegin(); iter != binary.rend(); iter++)
//	{
//		if (*iter == '1')
//			decimal += calculatePower(2, exponent);
//
//		exponent++;
//	}
//
//	return decimal;
//}
//
//uInt64 hexadecimalToDecimal(std::string binary)
//{
//	uInt64 decimal = 0;
//	uInt64 exponent = 0;
//	std::string::reverse_iterator iter;
//
//	for (iter = binary.rbegin(); iter != binary.rend(); iter++)
//	{
//		switch (*iter)
//		{
//		case '1':
//			decimal += calculatePower(16, exponent);
//			break;
//		case '2':
//			decimal += (2 * calculatePower(16, exponent));
//			break;
//		case '3':
//			decimal += (3 * calculatePower(16, exponent));
//			break;
//		case '4':
//			decimal += (4 * calculatePower(16, exponent));
//			break;
//		case '5':
//			decimal += (5 * calculatePower(16, exponent));
//			break;
//		case '6':
//			decimal += (6 * calculatePower(16, exponent));
//			break;
//		case '7':
//			decimal += (7 * calculatePower(16, exponent));
//			break;
//		case '8':
//			decimal += (8 * calculatePower(16, exponent));
//			break;
//		case '9':
//			decimal += (9 * calculatePower(16, exponent));
//			break;
//		case 'A':
//			decimal += (10 * calculatePower(16, exponent));
//			break;
//		case 'B':
//			decimal += (11 * calculatePower(16, exponent));
//			break;
//		case 'C':
//			decimal += (12 * calculatePower(16, exponent));
//			break;
//		case 'D':
//			decimal += (13 * calculatePower(16, exponent));
//			break;
//		case 'E':
//			decimal += (14 * calculatePower(16, exponent));
//			break;
//		case 'F':
//			decimal += (15 * calculatePower(16, exponent));
//			break;
//		}
//
//		exponent++;
//	}
//
//	return decimal;
//}
//
//std::string decimalToBinary(uInt64 decimal)
//{
//	std::string binary, newBinary = "";
//	std::string::reverse_iterator iter;
//	uInt64 remainder;
//
//	while (decimal > 0)
//	{
//		remainder = decimal % 2;
//
//		if (remainder == 0)
//			binary += '0';
//		else if (remainder == 1)
//			binary += '1';
//
//		decimal /= 2;
//	}
//
//	for (iter = binary.rbegin(); iter != binary.rend(); iter++)
//	{
//		newBinary += *iter;
//	}
//
//	return newBinary;
//}
//
//std::string binaryToHexadecimal(std::string binary)
//{
//	std::string hex, newHex = "";
//	std::string::reverse_iterator iter;
//
//	uInt64 incr = 1;
//
//	uInt64 exponent = 0;
//
//	uInt64 total = 0;
//
//	for (iter = binary.rbegin(); iter != binary.rend(); iter++)
//	{
//		if (*iter == '1')
//			total += calculatePower(2, exponent);
//
//		if (incr == 4)
//		{
//			switch (total)
//			{
//			case 1:
//				hex += '1';
//				break;
//			case 2:
//				hex += '2';
//				break;
//			case 3:
//				hex += '3';
//				break;
//			case 4:
//				hex += '4';
//				break;
//			case 5:
//				hex += '5';
//				break;
//			case 6:
//				hex += '6';
//				break;
//			case 7:
//				hex += '7';
//				break;
//			case 8:
//				hex += '8';
//				break;
//			case 9:
//				hex += '9';
//				break;
//			case 10:
//				hex += 'A';
//				break;
//			case 11:
//				hex += 'B';
//				break;
//			case 12:
//				hex += 'C';
//				break;
//			case 13:
//				hex += 'D';
//				break;
//			case 14:
//				hex += 'E';
//				break;
//			case 15:
//				hex += 'F';
//				break;
//			}
//
//			incr = 0;
//			exponent = -1;
//			total = 0;
//		}
//
//		incr++;
//		exponent++;
//	}
//
//	newHex += "0x";
//
//	for (iter = hex.rbegin(); iter != hex.rend(); iter++)
//	{
//		newHex += *iter;
//	}
//
//	return newHex;
//}


//
//int main()
//{
//	std::string binary, hex;
//	uInt64 decimal;
//	uInt64 choice;
//
//	std::cout << "\n\n* Decimal -> Binary & Hex (1)\n";
//	std::cout << "* Binary -> Decimal & Hex (2)\n";
//	std::cout << "* Hex -> Binary & Decimal (3)\n\n";
//	std::cin >> choice;
//
//	if (choice == 1)
//	{
//		std::cout << "\n> Decimal Input: ";
//		std::cin >> decimal;
//		std::string binaryOutput = decimalToBinary(decimal);
//		std::string hexOutput = binaryToHexadecimal(binaryOutput);
//		std::cout << "\n  Decimal Output: " << binaryOutput;
//		std::cout << "\n  Hex Output    : " << hexOutput << "\n\n\n";
//	}
//
//	else if (choice == 2)
//	{
//		std::cout << "\n> Binary Input: ";
//		std::cin.ignore();
//		std::getline(std::cin, binary);
//		uInt64 decimalOutput = binaryToDecimal(binary);
//		std::string hexOutput = binaryToHexadecimal(binary);
//		std::cout << "\n  Hex Output    : " << hexOutput;
//		std::cout << "\n  Decimal Output: " << decimalOutput << "\n\n\n";
//
//	}
//
//	else if (choice == 3)
//	{
//		std::cout << "\n> Hex Input: ";
//		std::cin.ignore();
//		std::getline(std::cin, hex);
//		uInt64 decimalOutput = hexadecimalToDecimal(hex);
//		std::string binaryOutput = decimalToBinary(decimalOutput);
//		std::cout << "\n  Binary Output : " << binaryOutput;
//		std::cout << "\n  Decimal Output: " << decimalOutput << "\n\n\n";
//	}
//
//	system("PAUSE");
//}