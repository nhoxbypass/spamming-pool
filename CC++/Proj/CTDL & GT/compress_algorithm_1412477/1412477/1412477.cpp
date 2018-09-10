// 1412477.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RLE.h"
#include "Huffman.h"
#include "LZW.h"

int main(int argc, char* argv[])
{
	int typeCompression = atoi(argv[2]); //Loai nen
	string Flag(argv[1]); //D or C tuong ung voi giai nen hay nen file
	string inputPath(argv[3]); //Duong dan input
	string outputPath(argv[4]); //Duong dan output
	cout << endl;

	//
	//Chuong trinh build o che do Debug thi Huffman no ghi file thanh cong, nhung release no bi loi, em van chua fix duoc :(
	//

	switch (typeCompression)
	{
	case 1:
	{
			  cout << "\tHUFFMAN DATA COMPPRESSION: " << endl << endl;
		if (Flag == "c")
		{
			cout << "      ----- Compression Mode -----   " << endl;
			HuffmanCompression compress(inputPath);
			compress.compression(outputPath);
			cout << "Compressed file size: " << compress.getFileSize(outputPath) << ", Original file size: " << compress.getFileSize(inputPath) << endl;
			float compRatio = compress.getFileSize(inputPath)*1.0 / compress.getFileSize(outputPath);
			cout << "Compression ratio: " << compRatio << ", space saved " << (1 - 1 / compRatio) * 100 << "%" << endl << endl;

		}
		else if (Flag == "d")
		{
			cout << "      ----- Extraction Mode -----   " << endl;
			HuffmanExtraction extract(inputPath); //inputPath la duong dan tep tin da nen
			extract.extraction(outputPath); 
		}

		break;
	}

	case 2:
	{
			  cout << "\tRun-Length Encoding DATA COMPPRESSION: " << endl << endl;
			  if (Flag == "c")
			  {
				  cout << "      ----- Compression Mode -----   " << endl;
				  RLE compress(inputPath, outputPath, "rleExtracted.txt");
				  compress.encode();

				  cout << "Compressed file size: " << compress.getCompressedSize() << ", Original file size: " << compress.getUnCompressedSize() << endl;
				  float compRatio = compress.getUnCompressedSize()*1.0 / compress.getCompressedSize();
				  cout << "Compression ratio: " << compRatio << ", space saved " << (1 - 1 / compRatio) * 100 << "%" << endl << endl;

			  }
			  else if (Flag == "d")
			  {
				  cout << "      ----- Extraction Mode -----   " << endl;
				  RLE extract("RLEInput.txt", inputPath, outputPath);
				  extract.Decode();
			  }
			 
			  break;
	}
		
	case 3:
	{
			  cout << "\tLZW DATA COMPPRESSION: " << endl << endl;
			  vector<int> compressed;
			  if (Flag == "c")
			  {
				  cout << "      ----- Compression Mode -----   " << endl;
				  LZW compress(inputPath);
				  compress.compress(back_inserter(compressed));
				  compress.writeCompressedToFile(compressed, outputPath);

				  cout << "Compressed file size: " << compress.getFileSize(outputPath) << ", Original file size: " << compress.getFileSize(inputPath) << endl;
				  float compRatio = compress.getFileSize(inputPath)*1.0 / compress.getFileSize(outputPath);
				  cout << "Compression ratio: " << compRatio << ", space saved " << (1 - 1/compRatio)*100 << "%" << endl << endl;

			  }
			  else if (Flag == "d")
			  {
				  cout << "      ----- Extraction Mode -----   " << endl;
				  LZW extract;
				  compressed = extract.readCompressedFromFile(inputPath);
				  string decompressed = extract.decompress(outputPath, compressed.begin(), compressed.end());
			  }

			  break;
	}
		
	}
	
	system("pause");
	return 0;
}

