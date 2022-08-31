//120211080526 计算机2105 张烁
/*
*      Q2: 写程序，实现括号匹配（提示：首先定义并实现顺序栈）；
*/
/*	测试样例
        样例1     (){}[]
        样例2     {[()]}
        样例3     {{{{{{}2727()()][]
        样例4     {654*8-96+454}*(666-66)
        样例5     [[]]{{{}}}(({{[]}}))
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                //定义并实现顺序栈
typedef struct Stack{
    char Bracket[100];
    int top = -1;
    int StackSize = 100;
}Sqstack;

int Empty(Sqstack S) {
    if (S.top == -1)
        return 1;
    else return 0;
}

int Push(Sqstack *S, char bra) {
    if  (S->StackSize == S->top + 1)
        return 0;
    S->top++;
    S->Bracket[S->top] = bra;
    return 1;
}

char Pop(Sqstack *S) {
    char e;
    if (S->top == -1)
        return 0;
    else {
        e = S->Bracket[S->top--];
        return e;
    }
}

char GetTop(Sqstack S) {
    if (S.top == -1)
        return 0;
    return S.Bracket[S.top];
}

                                //定义并实现顺序栈

void PrintMenu()
{
    printf("        ******************************************\n");
    printf("        *                括号匹配                *\n");
    printf("        ******************************************\n");
}

int main()
{
    PrintMenu();
    char arr[100];
    while (1)
    {
        printf("-----------请输入一串字符，包含括号：\n");
        scanf("%s", arr);
        Sqstack S;
        int i;
        int state = 0;
        for (i = 0; i < 100 && arr[i] != '\0'; i++) {
            if (arr[i] == '{' || arr[i] == '(' || arr[i] == '[') {
                Push(&S, arr[i]);
                state++;
            }
            if (arr[i] == ')') {
                if (GetTop(S) == '(') {
                    Pop(&S); 
                }
                else {                 
                    break;
                }
            }
            if (arr[i] == ']') {
                if (GetTop(S) == '[') {
                    Pop(&S);  
                }
                else {                
                    break;
                }
            }
            if (arr[i] == '}') {
                if (GetTop(S) == '{') {
                    Pop(&S);
                }
                else {
                    break;
                }
            }
        }
        if (Empty(S) && state) {
            printf("匹配！\n");
        }
        else {
            printf("不匹配！\n");
        }
        int YN;
        printf("继续吗？(1/0)\n");
        scanf("%d", &YN);
        printf("\n");
        if (YN == 1)
            continue;
        else if (YN == 0)
            return 0;
    }
}

