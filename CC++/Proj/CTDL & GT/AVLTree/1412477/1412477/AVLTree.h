#pragma once


template <class T>

class Node
{
	int height;
	T info;
	Node* pLeft;
	Node* pRight;

	Node* pMin = NULL;
	int min;

	void traverse_binary_tree(Node* node, int key)
	{
		if (n == NULL)     //Cay rong
			return;
		else if (pMin == NULL)
		{
			min = abs(node->info - key);
			pMin = node;
		}
		else
		{
			//Tham nut
			int diff = abs(node->info - key);
			if (diff < min)
			{
				min = diff;
				pMin = node;
			}
			traverse_binary_tree(n->left);     //Duyet cay con trai theo thu tu giua      
			traverse_binary_tree(n->right);    //Duyet cay con phai theo thu tu giua
		}
	}



	int Height()
	{
		if (this != NULL)
		{
			return height;
		}
		return 0;
	}

	int getBalance()
	{
		if (this != NULL)
		{
			return this->pLeft->Height() - this->pRight->Height();
		}
		return 0;
	}

	

	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
public:
	Node* CreateNode(T val)
	{
		Node* newNode = new Node;
		if (newNode == NULL)
		{
			//Failed to create node
			return NULL;
		}
		newNode->info = val;
		newNode->pLeft = NULL;
		newNode->pRight = NULL;
		newNode->height = 1;

		return newNode;
	}

	static Node* inputTree(Node* root)
	{
		int n;
		cout << " - Nhap so phan tu: ";
		cin >> n;

		for (int i = 0; i < n; i++)
		{
			int val;
			cout << " - Nhap node: ";
			cin >> val;
			root = root->Insert(val);
		}

		return root;
	}

	//xoay phai cay avl voi node goc la this
	Node* rotateRight()
	{
		//Tai sao la left or right thi ve minh hoa ra se thay
		Node* x = this->pLeft;
		Node* T2 = x->pRight;

		//Xoay
		x->pRight = this; //Dem not x len lam not goc vi xoay phai thi not trai' se len lam goc
		this->pLeft = T2; //Lay node tiep theo cua x gan vao node goc

		//Update chieu cao
		this->height = max(this->pLeft->Height(), this->pRight->Height()) + 1;
		x->height = max(x->pLeft->Height(), x->pRight->Height()) + 1;
		
		//Swap(this, x);
		return x; //return node goc
	}

	Node* rotateLeft()
	{
		Node* y = this->pRight;
		Node* T2 = y->pLeft; //Tai sao la left right thi ve minh hoa ra se thay

		y->pLeft = this;
		this->pRight = T2;

		this->height = max(this->pLeft->Height(), this->pRight->Height()) + 1;
		y->height = max(y->pLeft->Height(), y->pRight->Height()) + 1;


		//Swap(this, y);
		return y;
	}

	Node* Insert(T val)
	{
		if (this == NULL)
		{
			return this->CreateNode(val);
		}

		if (val < this->info)
		{
			this->pLeft = this->pLeft->Insert(val);
		}
		else
		{
			this->pRight = this->pRight->Insert(val);
		}

		//Gan do cao cho node
		this->height = max(this->pLeft->Height(), this->pRight->Height()) + 1;

		//Can bang cay
		int balance = this->getBalance();

		//Neu cay mat can bang
		//Left Left
		if (balance > 1 && val < this->pLeft->info)
		{
			return this->rotateRight();
		}

		//Right right
		if (balance < -1 && val > this->pRight->info)
		{
			return this->rotateLeft();
		}

		//Left Right
		if (balance > 1 && val > this->pLeft->info)
		{
			this->pLeft = this->pLeft->rotateLeft();
			return this->rotateRight();
		}

		if (balance < -1 && val < this->pRight->info)
		{
			this->pRight = this->pRight->rotateRight();
			return this->rotateLeft();
		}

		return this;
	}

	Node* getMinimumNode()
	{
		Node* currNode = this;

		//Tim la' trai' nhat
		while (currNode->pLeft != NULL)
		{
			currNode = currNode->pLeft;
		}

		return currNode;
	}

	Node* deleteNode(T val)
	{
		if (this == NULL)
		{
			return this;
		}

		//Duyet nhanh trai hoac phai
		if (val < this->info)
		{
			this->pLeft = this->pLeft->deleteNode(val);
		}
		else if (val > this->info)
		{
			this->pRight = this->pRight->deleteNode(val);
		}
		else //now this is the node that need to be deleted
		{
			//Neu node co 0 hoac 1 child
			if (this->pLeft == NULL || this->pRight == NULL)
			{
				//Lay node con
				Node* temp = this->pLeft ? this->pLeft : this->pRight;

				//truong hop ko co node con
				if (temp == NULL)
				{
					temp = this;
					delete temp;
					return NULL;
					//this = NULL;
				}
				else
				{
					this->info = temp->info;
					this->height = temp->height;
					this->pLeft = temp->pLeft;
					this->pRight = temp->pRight;

					delete temp;
				}
			}

				
			else
			{
				Node* temp = this->pRight->getMinimumNode();

				this->info = temp->info;

				this->pRight = this->pRight->deleteNode(temp->info);
			}
		}

		if (this == NULL)
		{
			return this;
		}

		//Cap nhat chieu cao
		this->height = max(this->pLeft->Height(), this->pRight->Height()) + 1;

		//Kiem tra mat can bang
		int balance = this->getBalance();

		//LL
		if (balance > 1 && this->pLeft->getBalance() >= 0)
		{
			return this->rotateRight();
		}

		//LR
		if (balance > 1 && this->pLeft->getBalance() < 0)
		{
			this->pLeft = this->pLeft->rotateLeft();
			return this->rotateRight();
		}

		//RR
		if (balance < - 1 && this->pRight->getBalance() <= 0)
		{
			return this->rotateLeft();
		}
		
		//RL
		if (balance < -1 && this->pRight->getBalance() > 0)
		{
			this->pRight = this->pRight->rotateRight();
			return this->rotateLeft();
		}

		return this;
	}
	

	Node* searchNode(T val)
	{
		if (this == NULL)
		{
			return NULL;
		}

		if (val < this->info)
		{
			this->pLeft->searchNode(val);
		}
		else if (val > this->info)
		{
			this->pRight->searchNode(val);
		}
		else
		{
			return this;
		}

		
	}


	void preOrder()
	{
		if (this != NULL)
		{
			cout << this->info << " ";
			this->pLeft->preOrder();
			this->pRight->preOrder();
			
		}
		
	}

	void postOrder()
	{
		
		if (this != NULL)
		{
			this->pLeft->preOrder();
			this->pRight->preOrder();
			cout << this->info << " ";
		}
	}

	void inOrder()
	{
		if (this != NULL)
		{

			this->pLeft->preOrder();
			cout << this->info << " ";
			this->pRight->preOrder();
			
		}
	}

	void showNode()
	{
		if (this != NULL)
		{
			cout << " --> Node: " << this->info << ", muc: " << this->height <<endl;
			return;
		}
		cout << " --> Node khong ton tai!" << endl;
	}

// 	AVLTree()
// 	{
// 
// 	}
// 
// 	~AVLTree()
// 	{
// 
// 	}
};

