#include "query.h"
#include "header.h"
# define MAXQSIZE 50 //等待队列最多排50人;

int InitQueue(SqQueue* Q) //循环队列初始化
{
	(*Q).base = (TimeData*)malloc(sizeof(TimeData) * MAXQSIZE);
	if (!(*Q).base)
		exit(0);
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

int QueueLength(SqQueue Q) //循环队列长度
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

int InQueue(SqQueue* q, const TimeData e) //循环队列入队
{
	if ((q->rear + 1) % MAXQSIZE == q->front)
		return ERROR;
	q->base[q->rear] = e;
	q->rear = (q->rear + 1) % MAXQSIZE;
	return OK;
}

int IsEmpty(const SqQueue q) //判断队列为空
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
