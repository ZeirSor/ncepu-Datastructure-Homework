// 120211080526 张烁 20220407
/*
*	Q4：写程序，进行排队问题模拟（要求：定义循环队列）。
*	
*						****银行排队问题简单模拟****
*		基本假设：
*			1. 银行有三个窗口
*			2. 每个用户服务时长为0-30min
*			3. 每0-20分钟内会随机来一个用户
*			4. 将银行关门时，在排队的用户继续服务，不接受新来的客户
*	
*		操作：
*			1. 银行服务时长（min）自己输入
*			2. 用户由随机数生成来模拟
*			3. 定义循环队列及其基本操作
*/
/*	测试样例
		总服务时长（min）
			30
			60
			120
			240
			480
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

#define MAXQSIZE 20		//每个窗口最多排10人

typedef struct 
{
	int Arrive; //到达时间
	int Wait;	//等待时间
	int Leave;	//离开时间
	int Serve;	//办理业务时间
	int Start;	//开始办理时间
}TimeData;				//队列节点类型(每个用户的时间数据)

typedef struct {		//循环队列定义
	TimeData* base;
	int front;			//头指针
	int rear;			//尾指针
}SqQueue;

SqQueue Win[3];			//三个窗口
const char *Cl = "客户编号";
const char *Sw = "服务窗口";
const char *Bt = "开始办理时间";
const char *At = "到达时间";
const char *Wt = "等待时间";
const char *St = "服务时间";
const char *Lt = "离开时间";
int ServeTime, WaitTime;
int TotalTime, NowTime = 0;
int LeaveTime[3] = { 0, 0, 0 };
int RespectiveWinSum[3] = { 0, 0, 0 };
int Close = 1;
int TotalWaitTime = 0;
int TotalClient = 0;
int OpenTime;
int OffTime;
int j;
int RandServeTime;
int IntervalTime;

int InitQueue(SqQueue* Q)				//循环队列初始化
{
	(*Q).base = new TimeData[MAXQSIZE];
	if (!(*Q).base)
		exit(0);
	(*Q).front = (*Q).rear = 0;
	return 1;
}

int IsEmpty(SqQueue Q)					//判断队列为空
{
	if (Q.front + 1 == Q.rear)
		return 1;
	else 
		return 0;
}

int QueueLength(SqQueue Q)				//循环队列长度
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

int EnQueue(SqQueue* Q, TimeData e)		//循环队列入队
{
	if ((Q->rear + 1) % MAXQSIZE == Q->front)
		return 0;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXQSIZE;
	return 1;
}

int DeQueue(SqQueue* Q)					//循环队列出队
{
	if (Q->front + 1 == Q->rear)
		return 0;
	Q->front = (Q->front + 1) % MAXQSIZE;
	return 1;
}

TimeData GetHead(SqQueue Q)				//循环队列取对头元素
{
	if (Q.front + 1 != Q.rear)
		return Q.base[Q.front];
}

int DisplayQueue(SqQueue Q) {
	printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Cl, Sw, Bt, At, Wt, St, Lt);

}

int GetShortestQueue(SqQueue* Q) {
	int min = 20;
	int i;
	for (i = 0; i < 3; i++) {
		if (QueueLength(Q[i]) < i)
			i = QueueLength(Q[i]);
	}
	return i;
}

void ClientIn(SqQueue *Q) {
	int shortest ;
	GetRandTime();
	LeaveQueueRes();
	LeaveQueueRes();
	LeaveQueueRes();
	shortest = GetShortestQueue(Q);
	if (Close) {
		TimeData* data = (TimeData*)malloc(sizeof(TimeData));
		data->Arrive = NowTime;
		data->Serve = RandServeTime;
		if (LeaveTime[shortest] == 0 || NowTime > LeaveTime[shortest]) {
			data->Leave = NowTime + RandServeTime;
			data->Wait = RandServeTime;
			data->Start = NowTime;
		}
		else {
			data->Leave = LeaveTime[shortest] + RandServeTime;
			data->Wait = LeaveTime[shortest] -NowTime + RandServeTime;
			data->Start = LeaveTime[shortest];
		}
		LeaveTime[shortest] = data->Leave;
		RespectiveWinSum[shortest] = RespectiveWinSum[shortest] + 1;
		EnQueue(&Win[shortest], *data);
	}
}

void LeaveQueueRes() {
	int i;
	for (i = 0; i < 3; i++) {
		if (Close) {
			if (!IsEmpty(Win[i])) {
				if (LeaveQueue(&Win[i], i)) {
					RespectiveWinSum[i]--;
					TotalClient++;
				}
			}
		}
	}
}

int LeaveQueue(SqQueue* q, int i) {
	SqQueue *CLeaTime = &(q[q->front]);
	int sum = 0;
	int Window = i + 1;
	int upStart;
	int wait;
	int start = 0;
	int leave = 0;
	int leave1 = 0;
	int wait1 = 0;
	int serve = 0;
	int AriTime = 0;
	int LeaTime = 0;
	int Start = 0;
	if (CLeaTime->rear != q->rear) {
		start = CLeaTime->base->Arrive;
		AriTime = OpenTime + start;

		leave1 = CLeaTime->base->Leave;
		leave = OpenTime + leave1;

		wait1 = CLeaTime->base->Wait;
		serve = CLeaTime->base->Serve;

		upStart = CLeaTime->base->Start;
		serve = OpenTime + upStart;

		printf("\t银行关门前已经在办理业务的:\n");
		printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Cl, Sw, Bt, At, Wt, St, Lt);
		printf("\t%d\t%d\t%d\t%d\t%d\t%d\t%d", j, Window, start, AriTime, wait1, serve, LeaTime);
		TotalWaitTime = TotalWaitTime + wait;
		if (IsEmpty(*q)) {
			return 0;
		}
		if (QueueLength(*q) == 1) {
			q->front = q->rear - 1;
			return 1;
		}
		q->front = (q->front + 1) % MAXQSIZE;
		return 1;
	}
	return 0;
}

void DisplayQueue(SqQueue* q, int i) {
	SqQueue* CLeaTime = &(q[q->front]);
	int sum = 0;
	int Window = i + 1;
	int upStart;
	int wait;
	int start = 0;
	int leave = 0;
	int leave1 = 0;
	int wait1 = 0;
	int serve = 0;
	int AriTime = 0;
	int LeaTime = 0;
	int Start = 0;
	while (CLeaTime->rear != q->rear) {
		start = CLeaTime->base->Arrive;
		AriTime = OpenTime + start;

		leave1 = CLeaTime->base->Leave;
		leave = OpenTime + leave1;

		wait1 = CLeaTime->base->Wait;
		serve = CLeaTime->base->Serve;

		upStart = CLeaTime->base->Start;
		serve = OpenTime + upStart;
		sum++;
		if (CLeaTime->base->Leave <= NowTime) {
			printf("\t银行关门前已经在办理业务的:\n");
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Cl, Sw, Bt, At, Wt, St, Lt);
			wait = CLeaTime->base->Wait;
			leave = CLeaTime->base->Leave;
			printf("\t%d\t%d\t%d\t%d\t%d\t%d\t%d", j, Window, start, AriTime, wait1, serve, LeaTime);
		}
		else {
			printf("银行关门后还在排队的\n");
			wait = TotalTime - CLeaTime->base->Arrive;
			leave = TotalTime;
			printf("\t%s\t%s\t%s\t%s\t%s\t%s\t%s", Cl, Sw, Bt, At, Wt, St, Lt);
			printf("\t%d\t%d\t%d\t%d\t%d\t%d\t%d", j, Window, start, AriTime, wait1, serve, LeaTime);
		}
	}
}

int main()
{
	printf("\t请输入服务总时间：");
	scanf("%d", &TotalTime);
	
	int i;						//三个窗口初始化
	for (i = 0; i < 3; i++) {
		InitQueue(&Win[i]);
	}

	printf("\t关门前的用户：");
	while (TotalTime > NowTime) {
		ClientIn(Win);
	}

	printf("\t关门不再接收的用户：");
	for (i = 0; i < 3; i++) {
		DisplayQueue(Win[i]);
	}
	printf("平均时间为%.2f min", (float)TotalWaitTime / TotalClient);
	return 0;
}