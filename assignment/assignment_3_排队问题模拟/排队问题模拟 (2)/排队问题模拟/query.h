#pragma once
typedef struct TimeData
{
	int Arrive; //到达时间
	int Wait;	//等待时间
	int Leave;	//离开时间
	int Serve;	//办理业务时间
	int Start;	//开始办理时间
}TimeData;				//队列节点类型(每个用户的时间数据)

typedef struct SqQueue {		//循环队列定义
	TimeData* base;
	int front;			//头指针
	int rear;			//尾指针
}SqQueue;


// query
int InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
int GetShortestQueue(SqQueue* Q);
int InQueue(SqQueue* q, TimeData e);
int IsEmpty(SqQueue q);
int PopQueue(SqQueue*, TimeData* r);
int DeleteQueue(SqQueue* q);
