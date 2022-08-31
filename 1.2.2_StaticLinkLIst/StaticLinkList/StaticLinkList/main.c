#include <stdio.h>
#define maxSize 6

typedef struct
{
	char data;
	int cur;
}component;

void reserveArr(component* array)
{
	int i;
	for (i = 0; i < maxSize; i++)
	{
		array[i].cur = i + 1;
	}
	array[maxSize - 1].cur = 0;
}

int mallocArr(component* array)
{
	int i = array[0].cur;
	if (array[0].cur)
	{
		array[0].cur = array[i].cur;
	}
	return i;
}

int initArr(component* array)
{
	reserveArr(array);
	int body = mallocArr(array);
	int tempBody = body;
	int i;
	for (i = 1; i < 5; i++)
	{
		int j = mallocArr(array);

	}
}