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
	int num;
}List, * ListPtr;

List* initList(int length)
{
	List* L = (ListPtr)malloc(sizeof(List));
	L->data = (int*)malloc(sizeof(int) * length);
	L->length = length;
	L->num = 1;
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

int searchList_sentry(List* L, int key)
{
	L->data[0] = key;
	int i;
	for (i = L->num - 1; L->data[i] != key; i--){}
	return i;
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
	printf("\t%d", searchList_sentry(L, 4));
	printf("\t%d", searchList_sentry(L, 10));
	return 0;
}
