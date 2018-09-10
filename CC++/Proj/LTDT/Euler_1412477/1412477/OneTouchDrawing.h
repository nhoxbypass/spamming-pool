#pragma once
#include "Euler.h"
#define MAX 100
class OneTouchDrawing
{
	int type;
	int eulerPath[MAX];
	int nVer;
	UndirectedGraph* G;
public:
	OneTouchDrawing();
	~OneTouchDrawing();
	
	//Hàm đọc file ma trận
	OneTouchDrawing(string inputPath);

	//Hàm in ma trận
	void showMatrix();

	//Hàm tìm đường và lưu dữ liệu
	int findWay();

	//In đường đi ra màn hình
	void showWay();

	//In ra tệp
	void printToFile(string outputPath);
	
};

