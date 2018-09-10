#pragma once
#include <conio.h>

#define MAX 100
#define NON_BRIDGE -1
#define BRIDGE 0
#define DONE 1
#define NOT_DONE 0
#define HAS_EULER_PATH 0
#define HAS_EULER_CYCLE 1
#define NOT_HAS_EULER_PATH -1

//Class đồ thị vô hướng
class UndirectedGraph
{
private:
	int nV; //số đỉnh của đồ thị
	int adjencyMatrix[MAX][MAX]; //ma trận trọng số
public:
	//Hàm khởi tạo ma trận rỗng
	UndirectedGraph();
	//Hàm khởi tạo đồ thị từ ma trận trọng số
	UndirectedGraph(int n, int A[][MAX]);
	//Hàm xác định bậc của một đỉnh
	unsigned int getVertexDeg(int v);
	//Hàm thêm cạnh (i,j)
	int addEdge(int i, int j);
	//Hàm xóa cạnh (i,j);
	int removeEdge(int i, int j);
	//Hàm lấy cạnh (i,j)
	int getEdge(int i, int j);
	//Hàm kiểm tra cạnh (i,j) có phải là cầu hay không
	int bridgeDetection(int i, int j);
	//Ham duyet dfs, co xac dinh cau
	int DFS(int u, int v, static int dfsNum[MAX], static int &curNum, static int num_p, static int startV);
	//Ham tinh so luong canh cua do thi
	int getNumEdge();
	//Ham xuat ma tran
	void outputMatrix();
	//Hàm Fleury
	int runFleury(int eulerPath[MAX], int& nVer);
};
