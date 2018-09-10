#include "stdafx.h"
#include "Euler.h"


UndirectedGraph::UndirectedGraph()
{
	nV = 0;
}
UndirectedGraph::UndirectedGraph(int n, int A[][MAX])
{
	nV = n;
	for (int i = 0; i < nV; i++)
	{
		for (int j = 0; j < nV; j++)
		{
			adjencyMatrix[i][j] = A[i][j];
		}
	}
}
int UndirectedGraph::addEdge(int i, int j)
{
	adjencyMatrix[i][j] = 1;
	return 1;
}
int UndirectedGraph::removeEdge(int i, int j)
{
	adjencyMatrix[i][j]--;
	adjencyMatrix[j][i]--;
	return 1;
}
int UndirectedGraph::getEdge(int i, int j)
{
	return adjencyMatrix[i][j];
}
int UndirectedGraph::getNumEdge()
{
	int nE = 0; for (int i = 0; i < nV; i++)
	for (int j = i; j < nV; j++)
	{
		nE = nE + adjencyMatrix[i][j];
	}
	return nE;
}
unsigned int UndirectedGraph::getVertexDeg(int v)
{
	int count = 0;
	for (int i = 0; i < nV; i++)
	{
		count = count + adjencyMatrix[v][i];
	}
	return count;
}
int UndirectedGraph::bridgeDetection(int i, int j)
{
	static int dfsNum[MAX]; //số thứ tự khi duyệt DFS
	static int curNum = 0;
	//begin 1
	for (int k = 0; k < nV; k++)
	{
		dfsNum[k] = -1;
	}
	//end 1
	int ret = NON_BRIDGE;
	dfsNum[j] = curNum;
	curNum++;
	//Tạo G1 = G
	UndirectedGraph g1(this->nV, this->adjencyMatrix);
	g1.removeEdge(i, j);
	ret = g1.DFS(i, j, dfsNum, curNum, dfsNum[j], i);
	if (ret <= dfsNum[j])
	{
		return NON_BRIDGE;
	}
	else
		return BRIDGE;
}
//DFS: p -> u ->
int UndirectedGraph::DFS(int u, int p, static int dfsNum[MAX], static int &curNum, static int num_p, static int startV)
{
	int ret = 0;
	dfsNum[u] = curNum;
	int oldestAncestor = dfsNum[u] = curNum;
	curNum++;
	for (int j = 0; j < nV; j++)
	{
		if (adjencyMatrix[u][j] != 0)
		{
			removeEdge(u, j);
			//begin 2
			if (dfsNum[j] == -1)
			{
				if (u == startV)
				{
					int t = 1;
				}
				ret = DFS(j, u, dfsNum, curNum, num_p, startV);
				if (u == startV)
				if (ret <= num_p)
				{
					return NON_BRIDGE;
				}
				oldestAncestor = min(oldestAncestor, ret);
			}
			//end 2
			else
				//begin 3
			{
				oldestAncestor = min(oldestAncestor, dfsNum[j]);
			}
			//end 3
		}
	}
	return oldestAncestor;
}
int UndirectedGraph::runFleury(int eulerPath[MAX], int& nVer)
{
	int count = 0;
	int u[2];
	//begin 4
	for (int i = 0; i<nV; i++)
	{
		if (getVertexDeg(i) % 2 != 0)
		{
			u[count] = i;
			count++;
		}
		if (count>2)
		{
			return NOT_HAS_EULER_PATH;
		}
	}
	//end 4
	//Tạo G1 = G
	UndirectedGraph g1(this->nV, this->adjencyMatrix);
	int ret;
	//begin 5
	if (count == 2)
	{
		ret = HAS_EULER_PATH;
		g1.addEdge(u[0], u[1]);
	}
	//end 5
	else
	{
		ret = HAS_EULER_CYCLE;
	}
	//Chọn đỉnh đầu tiên: P = { 0}
	int startVertex = u[0]; //sua tu 0 -> u0
	nVer = 0;
	eulerPath[nVer] = startVertex;
	nVer++;
	int nE = getNumEdge();
	while (nVer - 1 < nE)
	{
		//Chọn 1 cạnh e=(startVertex,i) từ g1
		int bridgeEndV = -1;
		int flag = NOT_DONE;
		for (int i = 0; i < nV; i++)
		{
			if (g1.getEdge(eulerPath[nVer - 1], i) != 0)
			{
				//begin 6
				if (g1.bridgeDetection(eulerPath[nVer - 1], i) == NON_BRIDGE)
				{
					eulerPath[nVer] = i;
					//Xóa cạnh khỏi G: G = G - e
					g1.removeEdge(eulerPath[nVer - 1], i);
					flag = DONE;
					nVer++;
					break;
				}
				else
				{
					bridgeEndV = i;
				}
				// end 6
			}
		}
		//begin 7
		if (bridgeEndV != -1 && flag == NOT_DONE)
		{
			eulerPath[nVer] = bridgeEndV;
			//Xóa cạnh khỏi G: G = G - e
			g1.removeEdge(eulerPath[nVer - 1], bridgeEndV);
			nVer++;
		}
		//end 7
	}
	return ret;
}
		
		void UndirectedGraph::outputMatrix()
		{
			for (int i = 0; i < nV; i++)
			{
				for (int j = 0; j < nV; j++)
				{
					cout << adjencyMatrix[i][j] << "\t";
				}
				cout << endl;
			}
		}