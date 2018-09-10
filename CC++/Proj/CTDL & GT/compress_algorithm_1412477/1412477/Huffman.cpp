
#include "stdafx.h"
#include "huffman.h"
#include <bitset>




void HuffmanCompression::convertTree()
{
	vector<Node*> tree;
	// Lap bang tan so
	// Duyet het chuoi de kiem tra
	for (int i = 0; i < data.length(); i++)
	{
		bool existed = false;
		// Duyet trong bang tan so, neu da ton tai thi tang tan so len 1 ( ++freq )
		for (int j = 0; j < tree.size(); j++)
		{
			if (tree[j]->c == data[i])
			{
				tree[j]->freq++;
				existed = true;
				break;
			}
		}
		// Ngc lai them ky tu do vao bang tan so
		if (!existed)
		{
			Node* node = new Node();
			node->c = data[i];
			node->freq = 1;
			tree.push_back(node);
		}
	}

	// Sap xep lai bang tan so
	for (int i = 0; i < tree.size() - 1; i++)
	{
		for (int j = i + 1; j < tree.size(); j++)
		{
			if (tree[i]->freq > tree[j]->freq)
			{
				Node* temp = tree[i];
				tree[i] = tree[j];
				tree[j] = temp;
			}
		}
	}

	while (true)
	{
		// Tao node temp co con la 2 phan tu dau trong bang tan so
		Node* tmp = new Node();
		tmp->left = tree[0];
		tmp->right = tree[1];
		tmp->freq = tmp->left->freq + tmp->right->freq;

		// Xoa 2 phan tu dau
		tree.erase(tree.begin(), tree.begin() + 2);
		tree.resize(tree.size() + 1);

		// Neu con dung 1 phan tu thi la node goc
		if (tree.size() == 1)
		{
			tree[0] = tmp;
			break;
		}
		else
		{
			// Chen node vao theo thu tu
			// Giam dan
			for (int j = 0; j < tree.size() - 1; j++)
			{
				bool isMax = true;
				if (tree[j]->freq > tmp->freq)
				{
					for (int k = tree.size() - 1; k > j; k--)
					{
						tree[k] = tree[k - 1];
					}
					tree[j] = tmp;
					isMax = false;
					break;
				}
				if (isMax) tree[tree.size() - 1] = tmp;
			}
		}
	}

	//Cuoi cung ta co duoc cay huffman, voi node goc cua cay
	root = tree[0];
}


void HuffmanCompression::MaHoaCayDeLuu(Node* curr)
{
	if (curr != NULL)
	{
		// Neu node curr la la
		if (curr->left == NULL && curr->right == NULL)
		{
			bitTree += '1';
			bitset<8> bitSq(curr->c);
			bitTree += bitSq.to_string();
		}
		// Nguoc lai
		else
		{
			bitTree += '0';
			MaHoaCayDeLuu(curr->left);
			MaHoaCayDeLuu(curr->right);
		}
	}
}

void HuffmanCompression::visit(Node* curr, string bit)
{
	if (curr != NULL)
	{
		if (curr->left == NULL && curr->right == NULL)
		{
			Bit b;
			b.c = curr->c;
			b.bit = bit;
			this->bit.push_back(b);
			return;
		}
		else{
			visit(curr->left, bit + "0");
			visit(curr->right, bit + "1");
		}
	}
}

std::string HuffmanCompression::convertBitStringToCharString(string input)
{
	string result = "";
	while (input.length() > 0)
	{
		string temp;
		if (input.length() > 8)
		{
			temp = input.substr(input.length() - 8, 8);
			input = input.erase(input.length() - 8, 8);
		}
		else
		{
			temp = input;
			if (temp.length() > 8) temp = "0" + temp;
			input = "";
		}
		result = convertBitToChar(temp) + result;
	}
	return result;
}

char HuffmanCompression::convertBitToChar(string temp)
{
	char c = strtol(temp.c_str(), 0, 2);
	return c;
}

void HuffmanCompression::compression(string outputPath)
{
	this->convertTree();
	this->visit(root, "");
	this->MaHoaCayDeLuu(root);

	// Thay the cac ky tu bang ma bit tuong ung
	string bitSq = "";
	for (int i = 0; i < data.length(); i++)
	{
		for (int j = 0; j < bit.size(); j++)
		{
			if (data[i] == bit[j].c)
			{
				bitSq += bit[j].bit;
				break;
			}
		}
	}

	// Ma hoa cay huffman de luu vao file
	string main = convertBitStringToCharString(bitTree + bitSq);
	int realBit = 0, sizeBit = (bitTree + bitSq).length();

	
	// Ta can xac dinh so bit '0' duoc them vao chuoi bit bitTree va bitSq
	while (realBit < sizeBit) realBit += 8;
	char addBit = realBit - sizeBit;
	// Xac dinh so luong ky tu trong chuoi
	char bitNum = this->bit.size();

	ofstream fo(outputPath);
	fo << (char)bitNum << (char)addBit << main;
	fo.close();
}

long HuffmanCompression::getFileSize(string filePath)
{
	ifstream file(filePath, ios::binary | ios::ate);

	long len = file.tellg();
	file.close();
	return len;
}



// Constructor
// 
HuffmanExtraction::HuffmanExtraction(string filePath)
{
	root = new Node();
	string bitSequence = "";
	ifstream fi(filePath, ios::binary);
	char c;
	// Ta không thể đọc 1 lần toàn bộ kí tự trong file
	// Vì có thể đâu đó trong file có chứa kí tự '\0'
	// Nếu ta cố tình đọc thì chuỗi bitSequence sẽ không thể lưu hết được
	// Vì vậy ta cần phải đọc từng ký tự trong file
	while (fi >> noskipws >> c)
	{
		bitset<8> bit(c);
		bitSequence += bit.to_string();
	}

	// Lấy ra số ký tự có trong chuỗi mã hoá
	char numChar = convertBitToChar(bitSequence.substr(0, 8));
	bitSequence.erase(0, 8);

	// Lấy ra số bit '0' được thêm vào như phía trên mình đề cập
	char addBit = convertBitToChar(bitSequence.substr(0, 8));
	bitSequence.erase(0, 8);

	// Bỏ đi các bit '0' thừa
	bitSequence.erase(0, addBit);

	// Số bit cần lấy tuân theo công thức dưới đây
	int sizeBit = 10 * numChar - 1;
	bitTree = bitSequence.substr(0, sizeBit);
	bitSequence.erase(0, sizeBit);
	data = bitSequence;
	fi.close();
}

void HuffmanExtraction::generateTree(Node* curr)
{
	while (bitTree.length() > 0)
	{
		//Neu la node la
		if (curr->left != NULL && curr->right != NULL) return;

		Node* node = new Node();
		if (bitTree[0] == '0')
		{
			bitTree.erase(0, 1);
			// Xac dinh goi de qui trai hay phai
			if (curr->left == NULL)
			{
				curr->left = node;
				generateTree(curr->left);
			}
			else
			{
				curr->right = node;
				generateTree(curr->right);
			}
		}

		// Neu gap bit 1, lay 8 bit ke tiep
		else
		{
			string temp = bitTree.substr(1, 8);
			bitTree.erase(0, 9);

			// Ham char convertBitToChar(string temp) dung xuat ra ky tu tuong ung voi chuoi bit
			node->c = convertBitToChar(temp);
			if (curr->left == NULL) curr->left = node;
			else curr->right = node;
		}
	}
}



char HuffmanExtraction::visit(Node* curr)
{
	if (curr->left == NULL && curr->right == NULL)
	{
		return curr->c;
	}
	if (data[0] == '0')
	{
		data.erase(0, 1);
		visit(curr->left);
	}
	else
	{
		data.erase(0, 1);
		visit(curr->right);
	}
}


void HuffmanExtraction::extraction(string outputPath)
{
	this->generateTree(root);
	root = root->left;
	string result = "";
	while (data.length() > 0) result += this->visit(root);
	ofstream fo(outputPath);
	fo << result;
	fo.close();

	cout << "Extracted!" << endl << endl;
}
std::string HuffmanExtraction::convertBitStringToCharString(string input)
{
	string result = "";
	while (input.length() > 0)
	{
		string temp;
		if (input.length() > 8)
		{
			temp = input.substr(input.length() - 8, 8);
			input = input.erase(input.length() - 8, 8);
		}
		else
		{
			temp = input;
			if (temp.length() > 8) temp = "0" + temp;
			input = "";
		}
		result = convertBitToChar(temp) + result;
	}
	return result;
}

char HuffmanExtraction::convertBitToChar(string temp)
{
	char c = strtol(temp.c_str(), 0, 2);
	return c;
}

long HuffmanExtraction::getFileSize(string filePath)
{
	ifstream file(filePath, ios::binary | ios::ate);
	long len = file.tellg();
	file.close();
	return len;
}
