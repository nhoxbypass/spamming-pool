#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

//Don vi chua ma morse va ky tu tuong ung
struct Morse
{
	string letter;
	string code;
};


struct Node
{
	string data;
	string code;
	Node *pLeft;
	Node *pRight;
};


class MorseTree
{
private:
	Node *root; //Node goc
	vector<Morse> m_array; //Bang tra
public:
	class MorseTree()
	{
		root = NULL;

		//Khoi tao mang bang tra
		m_array = {
			{ "ROOT", "" }, { "E", "." }, { "T", "-" }, { "I", ".." }, { "A", ".-" }, { "N", "-." },
			{ "M", "--" }, { "S", "..." }, { "U", "..-" }, { "R", ".-." }, { "W", ".--" }, { "D", "-.." },
			{ "K", "-.-" }, { "G", "--." }, { "O", "---" }, { "H", "...." }, { "V", "...-" }, { "F", "..-." }, { "", "..--" },
			{ "L", ".-.." }, { "P", ".--." }, { "J", ".---" }, { "B", "-..." }, { "X", "-..-" }, { "C", "-.-." },
			{ "Y", "-.--" }, { "Z", "--.." }, { "Q", "--.-" }, { "", "---." }, { "", "----" },
			{ "5", "....." }, { "4", "....-" }, { "3", "...--" }, { "2", "..---" }, { "1", ".----" },
			{ "6", "-...." }, { "7", "--..." }, { "8", "---.." }, { "9", "----." }, { "0", "-----" }

		};
	}

	//Chen node
	void Insert(Node *&r, string letter, string code)
	{
		if (r == NULL)
		{
			r = new Node;
			r->data = letter;
			r->code = code;
			r->pLeft =  r->pRight = NULL;
		}
	}

	void Insert(string letter, string code)
	{
		Node *r = root;
		if (r != NULL)
		{
			//Duyet ma morse, di toi node theo huong '.' : trai, '-' : phai
			//Neu node chua ton tai, thi tao va gan node moi
			for (int i = 0; i < code.length(); i++)
			{
				if (code[i] == '.')
				{
					if (r->pLeft)
						r = r->pLeft;
					else
					{
						//Khoi tao va gan gia tri node
						Node* lNode = new Node;
						lNode->pLeft = NULL;
						lNode->pRight = NULL;
						lNode->code = code;
						lNode->data = letter;

						r->pLeft = lNode;
						break;
					}

						
				}
				else if (code[i] == '-')
				{
					if ( r->pRight)
						r =  r->pRight;
					else
					{
						//Khoi tao va gan gia tri node
						Node* rNode = new Node;
						rNode->pLeft = NULL;
						rNode->pRight = NULL;
						rNode->code = code;
						rNode->data = letter;

						r->pRight = rNode;
						break;
					}
						
				}
				
				else break;
			}
			
		}
		else Insert(root, letter, code);
	}


	//Tao cay
	void BuildTree()
	{
		for (int i = 0; i < m_array.size(); i++)
		{
			this->Insert(m_array[i].letter, m_array[i].code);
		}

		
	}


	//Ma hoa va giai ma
	string Decode(string code)
	{
		//Xuat ra text tuong ung voi 1 dong ky tu morse
		string result = "";

		//String token, cat chuoi khi gap khoang trang
		istringstream iss(code);
		string part;
		while (getline(iss, part, ' '))
		{
			if (part == "|" || part == " |" || part == "| ")
			{
				result += " "; //Them khoang trang khi gap ky tu |
			}
			else
			{
				Node* r = SearchMorseCode(part); //Tim node chua ma morse va lay data cua no
				if (r != NULL) result += r->data;
			}

		}

		return result;
	}

	string Encode(string text)
	{
		//Xuat ra chuoi morse tuong ung voi 1 dong text
		string result = "";
		for (int i = 0; i < text.length(); i++)
		{
			//Neu gap khoang trang thi them "| " vao
			if (text[i] == ' ')
			{
				result += "| ";
			}
			else
			{
				//Tao chuoi tmp tu ky tu text[i]
				string tmp(1, text[i]);
				result += SearchCharacter(tmp);
				result += " ";
			}

		}

		return result;
	}

	void MorseTranslate(string inputPath, string outputPath)
	{
		//Khai bao bien
		int text_lines, morse_lines; //So luong dong text va morse code
		vector<string> text; //Vector chua text sau khi chuyen tu morse -> text
		vector<string> morse; //Vector chua morse

		string str_text;
		string str_morse;

		//File stream
		ifstream inFile;
		ofstream outFile;

		//Mo file
		inFile.open(inputPath);
		outFile.open(outputPath);

		if (!inFile.is_open())
		{
			cout << "File open failed!" << endl << endl;
			return;
		}

		//thuc thi

		//Lay so dong text va morse
		inFile >> text_lines >> morse_lines;

		//Xuong dong, vi con tro van con nam o dong tren
		getline(inFile, str_text);


		//Chuyen text -> morse
		for (int i = 0; i < text_lines; i++)
		{
			getline(inFile, str_text); //Lay chuoi text
			str_morse = Encode(str_text); //Chuyen doi
			morse.push_back(str_morse); //Luu vao vector
		}


		//Chuyen morse -> Text
		for (int i = 0; i < morse_lines; i++)
		{
			getline(inFile, str_morse);
			str_text = Decode(str_morse);
			text.push_back(str_text);
		}

		//Viet vao file
		//Morse
		for (int i = 0; i < text_lines; i++)
		{
			cout << morse[i] << endl; //Xuat ra man hinh kiem tra
			outFile << morse[i] << endl;
		}
		cout << endl;

		//Text
		for (int i = 0; i < morse_lines; i++)
		{
			cout << text[i] << endl;
			outFile << text[i] << endl;
		}


		cout << endl;
		cout << "Printed to file " << outputPath << endl << endl;

		//Dong file
		inFile.close();
		outFile.close();
	}

	
	//Tim kiem
	Node* SearchMorseCode(string code)
	{
		if (root == NULL)
		{
			cout << "Empty Morse Tree!" << endl << endl;
			return NULL;
		}
		else
		{
			Node* currNode = root;
			for (int i = 0; i < code.length(); i++)
			{
				if (code[i] == '.' && currNode->pLeft != NULL)
				{
					currNode = currNode->pLeft;
				}
				else if (code[i] == '-' && currNode->pRight != NULL)
				{
					currNode = currNode->pRight;
				}
				else
				{
					cout << "Wrong format Morse code, can't contain " << code[i] << endl << endl;
					break;
				}
			}


			if (currNode->code == code)
			{
				return currNode;
			}
		}

		return NULL;
	}

	string SearchCharacter(string text)
	{
		for (int i = 0; i < m_array.size(); i++)
		{
			if (text == m_array[i].letter)
			{
				return m_array[i].code;

			}
		}
		return "";
	}

};


int main()
{

	cout << "\t --- DOAN HIEU TAM - 1412477 - MORSE TRANSLATOR ---" << endl << endl;
	cout << "Ket qua: " << endl << endl;

	//Khai bao cay morse
	MorseTree t;
	
	//Khoi tao cay
	t.BuildTree();

	//Chuyen doi va ghi vao file
	t.MorseTranslate("input.txt", "1412477.txt");

	system("pause");
	return 0;
}