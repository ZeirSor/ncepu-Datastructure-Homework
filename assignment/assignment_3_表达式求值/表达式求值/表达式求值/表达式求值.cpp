// 120211080526 张烁 20220406
/*
*      Q3：写程序，实现表达式求值
*		   基本要求：操作数为1位整数；
*		   高阶要求：操作数为实数。
*/
/*	测试样例
	1+2+3#
	1.1+2.2+3.3#
	1+2-3#
	-2+3.1#
	-5.27*2+3.14*5#
	6+1/0#
	2.7+(-5*2.1+4)#
	8.16/5.27+19.91-20.03/3.06+(-7.25*2)#
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode
{
	char data;
	struct StackNode* next;
}SNode, * LinkStack;

typedef struct NumStack
{
	float data;
	struct NumStack* next;
}NSNode, *NumLinkStack;

int InitLinkStack(LinkStack* S)
{
	*S = NULL;		
	return 1;
}

int InitLinkStack2(NumLinkStack* S)
{
	*S = NULL;
	return 1;
}

int IsLinkStackEmpty(LinkStack S)
{
	if (S == NULL)
		return 1;
	else
		return 0;
}

int IsLinkStackEmpty2(NumLinkStack S)
{
	if (S == NULL)
		return 1;
	else
		return 0;
}

char GetLinkStackTop(LinkStack S)
{
	if (S == NULL)
		return 0;
	return S->data;
}

float GetLinkStackTop2(NumLinkStack S)
{
	if (S == NULL)
		return 0;
	return S->data;
}

int LinkStackLength(LinkStack S)
{
	int j = 0;
	LinkStack p = S;
	while (p) {
		p = p->next;
		j++;
	}
	return j;
}

int LinkStackLength2(NumLinkStack S)
{
	int j = 0;
	NumLinkStack p = S;
	while (p) {
		p = p->next;
		j++;
	}
	return j;
}

int PushLinkStack(LinkStack* S,char e)
{
	LinkStack p = (LinkStack)malloc(sizeof(SNode));
	if (p == NULL)
		return 0;
	p->data = e;
	p->next = *S;
	*S = p;
	return 1;
}

int PushLinkStack2(NumLinkStack* S, float e)
{
	NumLinkStack p = (NumLinkStack)malloc(sizeof(NSNode));
	if (p == NULL)
		return 0;
	p->data = e;
	p->next = *S;
	*S = p;
	return 1;
}

int PopLinkStack(LinkStack* S)
{
	LinkStack p = *S;
	if (p == NULL)
		return 0;
	*S = p->next;
	free(p);
	return 1;
}

int PopLinkStack2(NumLinkStack* S)
{
	NumLinkStack p = *S;
	if (p == NULL)
		return 0;
	*S = p->next;
	free(p);
	return 1;
}

int TraversLinkStack(LinkStack S)
{
	if (S == NULL) {
		printf("栈空！");
		return 0;
	}
	while (S) {
		printf("%c", S->data);
		S = S->next;
	}
	return 1;
}

int TraversLinkStack2(NumLinkStack S)
{
	if (S == NULL) {
		printf("栈空！");
		return 0;
	}
	while (S) {
		printf("%.2f ", S->data);
		S = S->next;
	}
	return 1;
}

char Prior(char theta1, char theta2)
{
	int i, j;
	char pri[7][7] = {//  +   -   *   /   (   )   = 
						{'>','>','<','<','<','>','>'},
						{'>','>','<','<','<','>','>'},
						{'>','>','>','>','<','>','>'},
						{'>','>','>','>','<','>','>'},
						{'<','<','<','<','<','=','0'},
						{'>','>','>','>','0','>','>'},
						{'<','<','<','<','<','0','='} };

	switch (theta1) {
						case '+': i = 0; break;
						case '-': i = 1; break;
						case '*': i = 2; break;
						case '/': i = 3; break;
						case '(': i = 4; break;
						case ')': i = 5; break;
						case '#': i = 6; break;
	}

	switch (theta2) {
						case '+': j = 0; break;
						case '-': j = 1; break;
						case '*': j = 2; break;
						case '/': j = 3; break;
						case '(': j = 4; break;
						case ')': j = 5; break;
						case '#': j = 6; break;
	}
	return pri[i][j];
}

int IsOPRT(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
		return 1;
	else return 0;
}

int IsNum(char c)
{
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return 1;
	default:
		return 0;
		break;
	}
	return 1;
}

float CCLT(float left, float right, char operators)
{
	switch (operators)
	{
		case '+':
			return  left + right;
		case '-':
			return left - right;
		case '*':	
			return float(left * right);
		case '/':
			if (right != 0)
				return float(left / right);
			else
			{
				printf("Divisor can not Be zero!\n");
				return 0;
			}
	}
	return 1;
}

float CCLT2(float left, float right, char operators)
{
	switch (operators)
	{
	case '+':
		return  1;
	case '-':
		return 1;
	case '*':
		return 1;
	case '/':
		if (right != 0)
			return 1;
		else
		{
			return 0;
		}
	}
	return 1;
}

void PrintMenu()
{
	printf("\n");
	printf("        ******************************************\n");
	printf("        *************** 实数范围内 ***************\n");
	printf("        *************** 表达式求值 ***************\n");
	printf("        ******************************************\n");
	printf("\n");
}

float CtoN(char c)
{
	if (IsNum(c))
		return float(c - '0');
	return 0;
}

int main()
{
	PrintMenu();
	while (1)
	{
		NumLinkStack Num;
		LinkStack Oprt;
		InitLinkStack2(&Num);
		InitLinkStack(&Oprt);
		PushLinkStack(&Oprt, '#');
		printf("	请输入运算表达式，以'#'结束！\n\n");
		printf("	");
		char Expression[100];
		scanf("%s", Expression);
		printf("    \n");
		int j = 0;
		int pan = 1;
		while ( pan &&(Expression[j] != '#' || GetLinkStackTop(Oprt) != '#')) {

			if (!IsOPRT(Expression[j])) {
				float sumIn = 0;
				float sumDe = 0;
				float temp = 1;
			
				do {
					sumIn *= 10;
					sumIn += CtoN(Expression[j]);
					j++;
				} while (IsNum(Expression[j]));

				if (Expression[j] == '.') {
					j++;
					float power = 1;
					do {
						power /= 10;
						sumDe += power * CtoN(Expression[j]);
						j++;
					} while (IsNum(Expression[j]));
				}
				PushLinkStack2(&Num, (float)(sumIn + sumDe));
				printf("	运算符栈：");
				TraversLinkStack(Oprt);
				printf(" ");
				printf("		运算数栈：");
				TraversLinkStack2(Num); 
				printf("\n");
			}
			else {
				switch (Prior(Oprt->data, Expression[j]))
				{
					case '<':
						PushLinkStack(&Oprt, Expression[j]);
						printf("	运算符栈：");
						TraversLinkStack(Oprt);
						printf(" ");
						printf("		运算数栈：");
						TraversLinkStack2(Num); 
						printf("\n");
						break;
					case '=':
						PopLinkStack(&Oprt);
						printf("	运算符栈：");
						TraversLinkStack(Oprt);
						printf(" ");
						printf("		运算数栈：");
						TraversLinkStack2(Num); 
						printf("\n");
						break;
					case '>':
						char Op = GetLinkStackTop(Oprt);
						PopLinkStack(&Oprt);
						float rigth = GetLinkStackTop2(Num);
						PopLinkStack2(&Num);
						float left = GetLinkStackTop2(Num);
						PopLinkStack2(&Num);
						pan = CCLT2(left, rigth, Op);
						PushLinkStack2(&Num, CCLT(left, rigth, Op));
						if (!pan) {
							printf("输入不合法！\n");
							PushLinkStack2(&Num, 0.00000);
						}
						printf("	运算符栈：");
						TraversLinkStack(Oprt);
						printf(" ");
						printf("		运算数栈：");
						TraversLinkStack2(Num); 
						printf("\n");
						j--;
						break;
				}
				j++;
			}
		/*	if (j >= strlen(Expression))
				break;*/
		}
		printf("\n");
		printf("	%s结果为：%.2f\n\n", Expression, GetLinkStackTop2(Num));
		
		printf("	继续吗？(1/0)\n");
		int YN;
		scanf("%d", &YN);
		if (YN == 1)
			continue;
		if (YN == 0)
			return 0;
	}
}
