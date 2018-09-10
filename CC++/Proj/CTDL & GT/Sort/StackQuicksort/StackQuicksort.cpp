// StackQuicksort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>      // thu vien de khoi tao tham so cho ham rand()
#include<stack>       // Su dung Stack trong C++
#define swap(type, a, b) {type temp = a; a = b; b = temp; }

using namespace std;

void quickSortUnRecursive(int *a, int l, int r)
{
	srand(time(NULL));
	stack<int> Sl;       // Stack left
	stack<int> Sr;       // Stack right
	Sl.push(l);         // dua phan tu dau tien l vao Sl
	Sr.push(r);         // dua phan tu dau tien r vao Sl

	while (!Sl.empty())  // trong khi stack khong rong
	{

		int l = Sl.top(); Sl.pop();     // lay phan tu dau tien trong Sl l ra
		int r = Sr.top(); Sr.pop();     // lay phan tu dau tien trong Sr r ra
		int key = a[l + rand() % (r - l + 1)];
		int i = l, j = r;
		while (i <= j)       // phan hoach thanh 2 day con
		{
			while (a[i] < key) i++;
			while (a[j] > key) j--;

			if (i <= j)
			{
				if (i < j)
					swap(int, a[i], a[j]);
				i++;
				j--;
			}
		}
		if (l < j) { Sl.push(l); Sr.push(j); }   // dua 2 dau mut l va j vao Sl va Sr
		if (i < r) { Sl.push(i); Sr.push(r); }   // dua 2 dau mut i va r vao Sl va Sr
	}
}

int main()
{
	int i, arr[] = { 40, 10, 100, 90, 20, 25 };
	quickSortUnRecursive(arr, 0, 5);
	for (i = 0; i < 6; i++)
		printf("%d ", arr[i]);

	system("pause");
	return 0;
}
