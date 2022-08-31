#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct List
{
	int *data;
	int length;
	int num;
}List, * ListPtr;

List* initList(int length)
{
	List* L = (ListPtr)malloc(sizeof(List));
	L->data = (int*)malloc(sizeof(int) * length);
	L->length = length;
	L->num = 0;
	return L;
}

void addList(List* L, int data)
{
	L->data[L->num++] = data;
}

void printList(List* L)
{
	for (int i = 0; i < L->num; i++) {
		printf("\t%d", L->data[i]);
	}
}

int searchList(List* L, int key)
{
	for (int i = 0; i < L->num; i++) {
		if (L->data[i] == key)
			return i;
	}
	return -1;
}

int main(int argc, char* argv[])
{
	List* L = initList(10);
	addList(L, 2);
	addList(L, 3);
	addList(L, 7);
	addList(L, 5);
	addList(L, 4);
	addList(L, 0);
	addList(L, 6);
	addList(L, 8);
	printList(L);
	printf("\n");
	printf("\t%d", searchList(L, 4));
	printf("\t%d", searchList(L, 3));
	printf("\t%d", searchList(L, 7));
	printf("\t%d", searchList(L, 10));
	return 0;
}
