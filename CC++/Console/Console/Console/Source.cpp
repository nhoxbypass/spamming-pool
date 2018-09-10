#include<set>
#include<map>
#include<list>
#include<queue>
#include<stack>
#include<string>
#include<math.h>
#include<time.h>
#include<vector>
#include<bitset>
#include<memory>
#include<utility>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<iostream>
#include<stdlib.h>


#include<algorithm>
#include <stdarg.h>
using namespace std;

// DoanHieuTam
// Yes, I can hear the sound
// Of a windmill going round
// I guess I'll always be
// A soldier of fortune.
// 
// I guess I'll always be
// A soldier of fortune.



#define _CRT_SECURE_NO_WARNINGS

class StringNumber
{
	//Convert string to long
	long parseLong(string s)
	{
		long result = 0;

		for (int i = 0; i < s.length(); i++)
		{
			int k = s[i] - '0';
			result = result * 10 + k;
		}

		return result;
	}

	//Convert long to string
	string parseString(long n)
	{
		string tmp = "", result = "";

		while (n > 0)
		{
			char c = (n % 10) + '0';
			tmp += c;
			n /= 10;
		}

		for (int i = tmp.length() - 1; i >= 0; i--)
		{
			result += tmp[i];
		}

		return result;
	}

public:
	string addBigNumber(string str1, string str2)
	{
		long l1 = parseLong(str1);
		long l2 = parseLong(str2);

		return parseString(l1 + l2);
	}

};








char* crosswordInfoConstruct(int _numberOfPlayer, int _turn, int _crosswordLength, char* hint)
{
	string temp = to_string(_numberOfPlayer) + "/" + to_string(_turn) + "/" + to_string(_crosswordLength) + "/" + string(hint);

	const char* tempChar = new char[temp.length()];

	tempChar = temp.c_str();

	char* result = new char[temp.length() + 1];
	strcpy_s(result, sizeof(temp), tempChar);

	return result;
}

// bubblesort.c
//Chuong trinh Bubble sort duoc cai dat de sap xep mang cac so nguyen co so phan tu la n
//Voi 1 <= n <= 100
//Su dung ReadInt() de nhapn va cac phan tu mang
//Su dung PrintString(char[]) va PrintInt(int) de xuat thong tin ra man hinh


float sum(int n, ...)
{
	va_list ap;
	va_start(ap, n);
	double v, s = 0;
	for (int i = 0; i < n; i++)
	{
		v = va_arg(ap, double);
		printf("%f\n", v);
		s += v;
	}
	va_end(ap);
	return s;
}

char* parseCrosswordInfo(char* info, int& _numberOfPlayer, int& _turn, int& _crosswordLength)
{
	_numberOfPlayer = atoi(strtok(info, "/"));
	_turn = atoi(strtok(NULL, "/"));
	_crosswordLength = atoi(strtok(NULL, "/"));
	return strtok(NULL, "/");
}

char* parseGuessWordPosition(char* appearance)
{
	char* result = new char[100];
	char playerName[30];
	int startIndex = 0;
	int len = strlen(appearance);

	for (int i = 2; i < len; i++)
	{
		if (appearance[i] == '/')
		{
			playerName[startIndex] = '\0';
			startIndex = i + 1;
			break;
		}
		playerName[startIndex] = appearance[i];
		startIndex++;
	}

	strcpy_s(result, sizeof(playerName), playerName);
	result = strcat(result, " vua doan ky tu '");
	result = strcat(result, &appearance[len - 1]);


	int sum = 0;
	result = strcat(result, "'. Vi tri:");

	//Bo 'A' va '/' va ky tu cuoi 
	for (int i = startIndex; i < len - 1; i++)
	{
		if (appearance[i] == '/')
		{
			char c_sum[10];

			_itoa_s(sum, c_sum, 10);
			result = strcat(result, " ");
			result = strcat(result, c_sum);
			sum = 0;
		}
		else
			sum = sum * 10 + appearance[i] - '0';
	}


	return result;

}


char* parseGuessString(char* appearance)
{
	//Duyet tu ten nguoi choi
	char name[10];
	int index = 0;
	int len = strlen(appearance);
	for (int i = 2; i < len; i++)
	{
		if (appearance[i] == '/')
		{
			name[index] = '\0';
			index = i + 1;
			break;
		}
		else
		{
			name[index] = appearance[i];
			index++;
		}
	}

	char* result = new char[100];
	strcpy_s(result, sizeof(name), name);
	result = strcat(result, " doan o chu: '");
	result = strcat(result, (appearance + index * sizeof(char)));
	result = strcat(result, "' nhung khong chinh xac!");
	return result;
}



typedef struct{
	int a;
	char* b;
}S;

void main()
{
	int i;

	for (i = 100; i <= 0; i--)
	{
		cout << i << endl;
	}

	system("pause");
}



