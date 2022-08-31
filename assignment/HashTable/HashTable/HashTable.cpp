#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define NUM 10

typedef struct HashList
{
	char *data;
	int num;
}HashList, * HashListPtr;

HashList* initHashList()
{
	HashList* list = (HashList*)malloc(sizeof(HashList));
	list->data = (char*)malloc(sizeof(char) * NUM);
	list->num = 0;
	for (int i = 0; i < NUM; i++) {
		list->data[i] = '0';
	}
	return list;
}

int Hash(int data)
{
	return data % NUM;
}

void putHash(HashList* list, char data)
{
	int index = Hash(data);
	if (list->data[index] != '0') {
		int count = 1;
		while (list->data[index] != '0') {
			index = Hash(Hash(data) + count);
			count++;
		}
	}
	list->data[index] = data;
	list->num ++;
}

const char* HashSearch(HashList* list, int key)
{
	int index = Hash(key);
	if (list->data[index] != key) {
		int count = 1;
		while (list->data[index] != key) {
			index = Hash(Hash(key) + count);
			if (list->data[index] == '0' || list->data[index] == Hash(key))
				return "NOT EXIST!";
			count++;
		}
	}
	return "SUCCESS!";
}

int main(int argc, char* argv[])
{
	HashList* list = initHashList();
	printf("序号");
	for (int i = 0; i < NUM; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	for (int i = 0; i < NUM; i++) {
		printf("\t%c", list->data[i]);
	}
	printf("\n");
	printf("\n");
	putHash(list, 'A');
	putHash(list, 'F');
	putHash(list, 'G');
	putHash(list, 'E');
	putHash(list, 'M');
	putHash(list, 'l');
	putHash(list, 'i');
	printf("序号");
	for (int i = 0; i < NUM; i++) {
		printf("\t%d", i);
	}
	printf("\n");
	for (int i = 0; i < NUM; i++) {
		printf("\t%c", list->data[i]);
	}
	printf("\n");

	puts(HashSearch(list, 'G'));
	puts(HashSearch(list, 'e'));
	puts(HashSearch(list, 'M'));
	puts(HashSearch(list, 'F'));
	puts(HashSearch(list, 'l'));
	puts(HashSearch(list, 'L'));
	puts(HashSearch(list, 'D'));
	puts(HashSearch(list, '1'));

	return 0;
}
