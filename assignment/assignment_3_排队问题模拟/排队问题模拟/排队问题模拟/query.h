#pragma once
typedef struct TimeData
{
	int Arrive; //����ʱ��
	int Wait;	//�ȴ�ʱ��
	int Leave;	//�뿪ʱ��
	int Serve;	//����ҵ��ʱ��
	int Start;	//��ʼ����ʱ��
}TimeData;				//���нڵ�����(ÿ���û���ʱ������)

typedef struct SqQueue {		//ѭ�����ж���
	TimeData* base;
	int front;			//ͷָ��
	int rear;			//βָ��
}SqQueue;


// query
int InitQueue(SqQueue* Q);
int QueueLength(SqQueue Q);
int GetShortestQueue(SqQueue* Q);
int InQueue(SqQueue* Q, TimeData e);
int IsEmpty(SqQueue Q);
TimeData* RemoveIdxQueue(SqQueue*);
int DeleteQueue(SqQueue* q);
