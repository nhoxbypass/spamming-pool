#pragma once


#define MAX_RLEN 100
using namespace std;

class RLE
{
private:
	string inputPath; //Duong dan tep tin dau vao
	string compressedPath; //Duong dan tep tin nen
	string extractedPath; //Duong dan tep tin giai nen
public:
	
	int encode();


	int Decode();

	long getCompressedSize();

	long getUnCompressedSize();

	RLE()
	{

	}
	RLE(string input, string compressed, string extracted)
	{
		inputPath = input;
		compressedPath = compressed;
		extractedPath = extracted;
	}
	~RLE(){

	}
};

