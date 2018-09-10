// Built-in_Quicksort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

int arr[] = { 40, 10, 100, 90, 20, 25 };

int compareInt(const void * a, const void * b)
{
	return (*(int*)a > *(int*)b);
}

int main()
{
	int n;
	qsort(arr, 6, sizeof(int), compareInt);
	for (n = 0; n < 6; n++)
		printf("%d ", arr[n]);

	system("pause");
	return 0;
}

