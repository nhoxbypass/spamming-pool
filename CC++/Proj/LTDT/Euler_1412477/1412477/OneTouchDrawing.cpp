#include "stdafx.h"
#include "OneTouchDrawing.h"


OneTouchDrawing::OneTouchDrawing()
{
}

OneTouchDrawing::OneTouchDrawing(string inputPath)
{
	//Khai báo m?ng ch?a ma tr?n
	int n;
	int Arr[MAX][MAX];

	ifstream inFile;
	inFile.open(inputPath);

	if (!inFile.is_open())
	{
		return;
	}

	inFile >> type;

	inFile >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inFile >> Arr[i][j];
		}
	}

	inFile.close();

	//Tao doi tuong graph
	G = new UndirectedGraph(n, Arr);
}


OneTouchDrawing::~OneTouchDrawing()
{
}

void OneTouchDrawing::showMatrix()
{
	G->outputMatrix();
}

int OneTouchDrawing::findWay()
{
	int ret = G->runFleury(eulerPath, nVer);
	return ret;
}

void OneTouchDrawing::showWay()
{
	cout << "Duong di can ve la:" << endl;
	for (int i = 0; i < nVer; i++)
		cout << eulerPath[i] << " -> ";

	cout << " Ket thuc " << endl << endl;
}

void OneTouchDrawing::printToFile(string outputPath)
{
	ofstream outFile;
	outFile.open(outputPath);

	outFile << eulerPath[0];
	for (int i = 1; i < nVer; i++)
		outFile << " -> " << eulerPath[i];

	outFile.close();

	cout << "Printed to file " << outputPath << " !" << endl << endl;
}
