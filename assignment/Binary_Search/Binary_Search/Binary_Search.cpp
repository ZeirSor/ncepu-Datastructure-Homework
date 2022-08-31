#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct List
{
	int* data;
	int length;
}List, * ListPtr;

List* initList(int length)
{
	List* L = (ListPtr)malloc(sizeof(List));
	L->data = (int*)malloc(sizeof(int) * length);
	L->length = length;
	for (int i = 0; i < L->length; i++) {
		L->data[i] = i + 1;
	}
	return L;
}

void printList(List* L)
{
	for (int i = 0; i < L->length; i++) {
		printf("\t%d", L->data[i]);
	}
}

int binarySearch(List* L, int key)		//循环
{
	int start = 0;
	int end = L->length - 1;
	int mid;
	while (start <= end) {
		mid = (start + end) / 2;
		if (L->data[mid] < key) {
			start = mid + 1;
		}
		else if (key < L->data[mid]) {
			end = mid - 1;
		}
		else if (L->data[mid] == key)
			return mid;
	}
	return -1;
}

int binarySearch_recurs(List* L, int key, int start, int end)	//递归法
{
	if (start == end) {
		if (L->data[start] == key)
			return start;
		else
			return -1;
	}
	int mid = (start + end) / 2;
	if (key < L->data[mid]) {
		binarySearch_recurs(L, key, start, mid - 1);
	}
	else if (L->data[mid] < key) {
		binarySearch_recurs(L, key, mid + 1, end);
	}
	else {
		return mid;
	}
}

int main(int argc, char* argv[])
{
	List* L = initList(10);
	printList(L);
	printf("\n");
	printf("\t%d", binarySearch(L,3));
	printf("\t%d", binarySearch(L,5));
	printf("\t%d", binarySearch(L,11));
	printf("\t%d", binarySearch(L,1));
	printf("\t%d", binarySearch_recurs(L, 6, 0, L->length - 1));
	printf("\t%d", binarySearch_recurs(L,99,0,L->length-1));
	printf("\t%d", binarySearch_recurs(L,10,0,L->length-1));
	printf("\t%d", binarySearch_recurs(L,9,0,L->length-1));
	return 0;
}

/*	OUTPUT
*	1       2       3		 4       5       6       7       8       9       10
*	2       4		-1		 0       5		 -1      9       8
*/
