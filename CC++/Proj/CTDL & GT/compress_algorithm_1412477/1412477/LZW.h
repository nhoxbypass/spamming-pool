#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
using namespace std;

// Compress a string to a list of output symbols.
// The result will be written to the output iterator
// starting at "result"; the final iterator is returned.


class LZW
{
private:
	string uncompressed; //Du lieu dau vao, nhap tu file chua nen
public:
	template <typename Iterator>
	Iterator compress(Iterator result) {
		// Build the dictionary.
		int dictSize = 256;
		std::map<string, int> dictionary;
		for (int i = 0; i < 256; i++)
			dictionary[string(1, i)] = i;

		string w;
		for (string::const_iterator it = uncompressed.begin();
			it != uncompressed.end(); ++it) {
			char c = *it;
			string wc = w + c;
			if (dictionary.count(wc))
				w = wc;
			else {
				*result++ = dictionary[w];
				// Add wc to the dictionary.
				dictionary[wc] = dictSize++;
				w = string(1, c);
			}
		}

		// Output the code for w.
		if (!w.empty())
			*result++ = dictionary[w];
		return result;
	}

	// Decompress a list of output ks to a string.
	// "begin" and "end" must form a valid range of ints
	template <typename Iterator>
	string decompress(string outputPath, Iterator begin, Iterator end) {
		// Xay dung dictionary.
		int dictSize = 256;
		std::map<int, string> dictionary;
		for (int i = 0; i < 256; i++)
			dictionary[i] = string(1, i);

		string w(1, *begin++);
		string result = w;
		string entry;
		for (; begin != end; begin++) {
			int k = *begin;
			if (dictionary.count(k))
				entry = dictionary[k];
			else if (k == dictSize)
				entry = w + w[0];
			else
				throw "Bad compressed k";

			result += entry;

			// Them w+entry[0] vao dictionary.
			dictionary[dictSize++] = w + entry[0];

			w = entry;
		}

		//Ghi vao file
		ofstream outFile;
		outFile.open(outputPath);
		outFile << result;
		outFile.close();

		cout << "Extracted!" << endl << endl;

		return result;
	}


	void writeCompressedToFile(vector<int> v, string outputPath)
	{
		ofstream outFile;
		outFile.open(outputPath);

		for (int i = 0; i < v.size(); i++)
		{
			outFile << v[i] << " ";
		}

		outFile.close();
	}
	

	vector<int> readCompressedFromFile(string compressedFilePath)
	{
		ifstream inFile;
		inFile.open(compressedFilePath);

		if (!inFile.is_open())
		{
			cout << "File open failed! " << endl;
			return {};
		}
		else
		{
			vector<int> v;
			while (!inFile.eof())
			{
				int tmp;
				inFile >> tmp;
				v.push_back(tmp);
			}

			return v;
		}

		inFile.close();
	}

	long getFileSize(string path)
	{
		ifstream file(path, ios::binary | ios::ate);
		long len = file.tellg();
		file.close();
		return len;
	}

	LZW(string inputPath)
	{
		ifstream inFile;
		inFile.open(inputPath);

		if (!inFile.is_open())
		{
			cout << "Failed to open file!" << endl;
		}
		else
		{
			string res = "";
			while (!inFile.eof())
			{
				string tmp;
				getline(inFile, tmp);
				res += tmp;
				res += '\n';
			}

			

			uncompressed = res;
		}
		inFile.close();
	}

	LZW()
	{

	}

	~LZW()
	{

	}
};

