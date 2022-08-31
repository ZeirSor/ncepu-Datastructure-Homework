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
int InQueue(SqQueue* q, TimeData e);
int IsEmpty(SqQueue q);
int PopQueue(SqQueue*, TimeData* r);
int DeleteQueue(SqQueue* q);
