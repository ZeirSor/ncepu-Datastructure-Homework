#include <iostream>
#include <stdio.h>
#define MAXSIZE 1000
#define OK 1;
typedef int Status;
typedef struct
{
	char c;
	int cur;

}Component,StaticLinkList[MAXSIZE];

Status InitList(StaticLinkList space)	//静态链表初始化
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++)
		space[i].cur = i + 1;			//游标依次为1，2，3 4，···
	space[MAXSIZE - 1].cur = 0;			//理解为最后一个游标指向首个空元素的下标
	return OK;
}

int Malloc_SST(StaticLinkList space)	//返回空结点的下标	空结点是用来插入新结点的
{
	int i = space[0].cur;				//这一步已经为返回准备好了 就是空结点下标

	if (space[0].cur)					//让首结点游标指向新的空结点	
		space[0].cur = space[i].cur;

	return i;
}

Status ListInsert(StaticLinkList L, int i, char e)
{
	int j, k, l;
	k = MAXSIZE - 1;
	if (i < 1 || i > ListLength(L) + 1)
		return 0;
}

int main()
{
	

}

