#include "stdafx.h"
#include "RLE.h"



int RLE::encode()
{
	ifstream inFile;
	inFile.open(inputPath);

	if (!inFile.is_open())
	{
		cout << "Failed to open file! " << endl;
		return 0;
	}

	string src = "";

	while (!inFile.eof())
	{
		string tmp;
		getline(inFile, tmp);

		src += tmp;
		src += "\n";
	}

	int rLen;
	char count[MAX_RLEN];
	int len = src.length();

	/* Neu tat ca ky tu trong chuoi deu khac nhau, file size se bi x2 len */

	int i, j = 0, k;
	string res = "";
	/* traverse the input string one by one */
	for (i = 0; i < len; i++)
	{

		/* Copy the first occurrence of the new character */
		char tmp = src[i];



		/* Count the number of occurrences of the new character */
		rLen = 1;
		while (i + 1 < len && src[i] == src[i + 1])
		{
			rLen++;
			i++;
		}

		res += to_string(rLen);
		res += src[i];
	}


	inFile.close();

	ofstream outFile;
	outFile.open(compressedPath);

	outFile << res;

	outFile.close();

	return 1;
}

int RLE::Decode()
{
	ifstream inFile;
	inFile.open(compressedPath);

	if (!inFile.is_open())
	{
		cout << "Failed to open file! " << endl;
		return 0;
	}

	ofstream outFile;
	outFile.open(extractedPath);

	int count = 0;


	string src = "";


	while (!inFile.eof())
	{
		string tmp;
		getline(inFile, tmp);
		src += tmp;
		src += '\n';
	}

	for (int i = 0; i < src.length(); i++)
	{
		char curr = src[i];
		if (curr == '\n')
		{
			outFile << curr;
			count = 0;
		}
		else if (curr >= '1' && curr <= '9')
		{
			count = count * 10 + (curr - '0');
		}
		else
		{
			for (int i = 0; i < count; i++)
			{
				outFile << curr;
			}
			count = 0;
		}
	}

	cout << "Extracted!" << endl << endl;
	outFile.close();
	inFile.close();

	return 1;
}

long RLE::getCompressedSize()
{
	ifstream file(compressedPath, ios::binary | ios::ate);
	long len = file.tellg();
	file.close();
	return len;
}

long RLE::getUnCompressedSize()
{
	ifstream file(inputPath, ios::binary | ios::ate);
	long len = file.tellg();
	file.close();
	return len;
}
