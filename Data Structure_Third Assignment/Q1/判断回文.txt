//120211080526 计算机2105 张烁
/*
*      Q1: 写程序，进行回文判断（要求：定义链队和链栈）；
*/
/*	测试样例
        样例1     11111111111
        样例2     12321
        样例3     asc12321cba
        样例4     !@!@!@!@!
        样例5     d5z2q7q2z5d
        样例6     !@#$%^&*()(*&^%$#@!
        样例7     _+{}:"<><":}{+_
        样例7     [];',./.,';][
        样例8     /*-+-*/
//      样例9     ...qaq...
//      样例10    @!=!@
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

                                                        //链栈操作
typedef struct StackNode
{
    char data;
    struct StackNode* next;
}SNode, * LinkStack;

int InitLinkStack(LinkStack* S)
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

char GetLinkStackTop(LinkStack S)
{
    if (S == NULL)
        return 0;
    return S->data;
}

int PushLinkStack(LinkStack* S, char c)
{
    LinkStack p = (LinkStack)malloc(sizeof(SNode));
    if (p == NULL)
        return 0;
    p->data = c;
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

int ClearLinkStack(LinkStack* S) {
    LinkStack p = (*S)->next;
    while (p) {
        p = p->next;
        PopLinkStack(S);
    }
    return 1;
}

                                                        //链队操作
typedef struct QNode
{
    char data;
    struct QNode* next;
}QNode, * QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue* Q)
{
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front)
        exit(0);
    Q->front->next = NULL;
    return 1;
}

int LinkQueueLength(LinkQueue Q) {
    QueuePtr p = Q.front->next;
    int n = 0;
    if (Q.front == Q.rear)
        return 0;
    while (p) {
        n++;
        p = p->next;
    }
    return n;
}

char GetLinkQueueTop(LinkQueue Q)
{
    if (Q.front == Q.rear)
        return 0;
    return  Q.front->next->data;;
}

int AppendQueue(LinkQueue* Q, char e)
{
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
        exit(0);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return 1;
}

int DeQueue(LinkQueue* Q)
{
    if (Q->front == Q->rear)
        return 0;
    QueuePtr p = Q->front->next;
    Q->front->next = p->next;

    if (Q->rear == p)
        Q->rear = Q->front;

    free(p);
    return 1;
}

int ClearQueue(LinkQueue *Q)
{
    Q->front = Q->rear;
    return 1;
}

                                                      //判断回文
int Palindrome(LinkStack S, LinkQueue Q)
{
    if (LinkStackLength(S) != LinkQueueLength(Q))
        return 0;
    while (!IsLinkStackEmpty(S))
    {
        char e1, e2;
        if (GetLinkStackTop(S) != GetLinkQueueTop(Q))
            return 0;
        else {
            PopLinkStack(&S);
            DeQueue(&Q);
        }
    }
    return 1;
}

void PrintMenu()
{
    printf("\n");
    printf("        ******************************************\n");
    printf("        *                回文判断                *\n");
    printf("        ******************************************\n");
}

int main()
{
    PrintMenu();
    while (1) {
        LinkStack S;
        LinkQueue Q;
        InitLinkStack(&S);
        InitQueue(&Q);
        printf("        请输入一串字符：");
        char P[50];
        int i;
        scanf("%s", P);
        for (i = 0; P[i] != '\0'; i++) {
            PushLinkStack(&S, P[i]);
            AppendQueue(&Q, P[i]);
        }
        if (Palindrome(S, Q))
            printf("    ——————————%s是回文数！\n",P);
        else
            printf("    ——————————%s不是回文数！\n",P);

        int YN;
        printf("    继续吗？(1/0)\n     ");
        scanf("%d", &YN);
        printf("\n");
        if (YN == 1)
            continue;
        else if (YN == 0)
            return 0;
    }
}
