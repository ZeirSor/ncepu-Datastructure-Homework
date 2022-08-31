#include "query.h"
#include "header.h"
constexpr auto MAXQSIZE = 20;		//每个窗口最多排10人;

int InitQueue(SqQueue* Q)				//循环队列初始化
{
	(*Q).base = (TimeData*)malloc(sizeof(TimeData) * MAXQSIZE);
	if (!(*Q).base)
		exit(0);
	(*Q).front = 0;
	(*Q).rear = 0;
	return OK;
}

int QueueLength(SqQueue Q)				//循环队列长度
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

int InQueue(SqQueue* Q, TimeData e)		//循环队列入队
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return OK;

}

int IsEmpty(SqQueue Q)					//判断队列为空
{
	if (Q.front == Q.rear)
		return TURE;
	else
		return FALSE;
}
TimeData*
RemoveIdxQueue(SqQueue* q)
{
	if (q->front + 1 == q->rear)
		return NULL;
	q->front = (q->front + 1) % MAXQSIZE;
	return &q->base[q->front];
}

int DeleteQueue(SqQueue *q)
{
	free(q->base);
}
//int LeaveQueue(SqQueue* q, int i)
//// TODO: 更改逻辑
//{
//	SqQueue* CLeaTime = &(q[q->front]);
//	int sum = 0;
//	int Window = i + 1;
//	int upStart;
//	int wait;
//	int start = 0;
//	int leave = 0;
//	int leave1 = 0;
//	int wait1 = 0;
//	int serve = 0;
//	int AriTime = 0;
//	int LeaTime = 0;
//	int Start = 0;
//	if (CLeaTime->base->Leave <= NowTime)
//	{
//		start = CLeaTime->base->Arrive;
//		AriTime = OpenTime + start;
//
//		leave = CLeaTime->base->Leave;
//		leave = OpenTime + leave1;
//
//		wait = CLeaTime->base->Wait;
//		serve = CLeaTime->base->Serve;
//
//		upStart = CLeaTime->base->Start;
//		serve = OpenTime + upStart;
//
//		printf("\t%-15d%-15d%-15d%-15d%-15d%-15d%-15d\n", j, Window, start, AriTime, wait1, serve, LeaTime);
//		TotalWaitTime = TotalWaitTime + wait;
//		if (IsEmpty(*q))
//		{
//			return 0;
//		}
//		if (q->front == q->rear)
//		{
//			q->front = q->rear == NULL;
//			return 1;
//		}
//		CLeaTime = &(q[q->front]);
//		q->front = (q->front + 1) % MAXQSIZE;
//		return 1;
//	}
//	return 0;
//}
//
//void LeaveQueueRes(SqQueue* Q)
//{
//	int i;
//	for (i = 0; i < 3; i++)
//	{
//		if (!Close)
//		{
//			if (!IsEmpty(Q[i]))
//			{
//				if (LeaveQueue(&Q[i], i))
//				{
//					RespectiveWinSum[i]--;
//					TotalClient++;
//					j++;
//				}
//			}
//		}
//	}
//}