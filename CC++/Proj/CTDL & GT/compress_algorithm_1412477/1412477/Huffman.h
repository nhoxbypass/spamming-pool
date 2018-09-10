


#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Node
{
	char c;
	int freq;
	Node* left;
	Node* right;
	Node()
	{
		c = '\0';
		freq = -1;
		left = NULL;
		right = NULL;
	}
};

//Luu tru cac bit da ma hoa prefix
struct Bit
{
	char c;
	string bit;
};




class HuffmanCompression
{
private:
	string data; //Luu chuoi doc vao tu file
	Node* root;
	vector<Bit> bit; // Luu bang tan so
	string bitTree; //Ma hoa cay huffman de luu vao file
	void convertTree();
	void visit(Node* curr, string bit);
	void MaHoaCayDeLuu(Node* curr);
	string convertBitStringToCharString(string input);
	char convertBitToChar(string temp);

public:
	HuffmanCompression() { 
		bitTree = ""; 
	}
	HuffmanCompression(string filePath)
	{
		data = "";
		ifstream inFile;
		inFile.open(filePath);

		if (!inFile.is_open())
		{
			cout << "Failed to open file! " << endl;
		}
		else
		{
			while (!inFile.eof())
			{
				string tmp;
				getline(inFile, tmp);
				data += tmp;
				data += '\n';
			}
		}

		inFile.close();
		
	}

	void compression(string outputPath);

	long getFileSize(string filePath);
	~HuffmanCompression()
	{

	}
};




class HuffmanExtraction
{
private:
	string bitTree;
	string data;
	Node* root;
	void generateTree(Node* curr);
	char visit(Node* curr);
	string convertBitStringToCharString(string input);
	char convertBitToChar(string temp);
public:
	HuffmanExtraction() { root = new Node(); }
	HuffmanExtraction(string filePath);
	void extraction(string outputPath);
	long getFileSize(string filePath);
};