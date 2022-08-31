#include "query.h"
#include "header.h"
# define MAXQSIZE 50 //�ȴ����������50��;

int InitQueue(SqQueue* Q) //ѭ�����г�ʼ��
{
	(*Q).base = (TimeData*)malloc(sizeof(TimeData) * MAXQSIZE);
	if (!(*Q).base)
		exit(0);
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

int QueueLength(SqQueue Q) //ѭ�����г���
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

int GetShortestQueue(SqQueue* Q)
{
	int min = 20;
	int idx = 0;
	for (int i = 0; i < 3; i++)
	{
		if (QueueLength(Q[i]) < min)
		{
			min = QueueLength(Q[i]);
			idx = i;
		}
	}
	return idx;
}

int InQueue(SqQueue* q, const TimeData e) //ѭ���������
{
	if ((q->rear + 1) % MAXQSIZE == q->front)
		return ERROR;
	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXQSIZE;
	return OK;
}

int IsEmpty(const SqQueue q) //�ж϶���Ϊ��
{
	if (q.front == q.rear)
		return TURE;
	return FALSE;
}

int PopQueue(SqQueue* q, TimeData* r)
{
	if (q->rear + 1 == q->front)
	{
		return ERROR;
	}
	*r = q->base[q->front];

	q->front = (q->front + 1) % MAXQSIZE;
	return OK;
}

int DeleteQueue(SqQueue* q)
{
	free(q->base);
	return OK;
}
