#include <stdio.h>
#define MAX 100

int Queue[MAX];

int rear,front;

void InitializeQueue(void);
void Put(int);
int Get(void);
void DisplayQueue(void);

void InitializeQueue(void)
{
	rear = front = 0;
}
void Put(int n)
{
	Queue[rear++] = n;
	if(rear >= MAX) rear = 0;
}
int Get(void)
{
	int ret;
	ret = Queue[front++];
	
	if(front >=MAX) front = 0;
	
	return ret;
}
void DisplayQueue(void)
{
	int i;
	printf("front->");
	for(i = front; i < rear; i++ )
	{
		printf("%d->",Queue[i]);
	}
	printf("rear");
}


void main(void)
{
	InitializeQueue();
	
	Put(1);
	Put(2);
	Put(3);
	Put(4);
	DisplayQueue();
	
	puts("");
	printf("Get : %d\n",Get());
	printf("Get : %d\n",Get());
	printf("Get : %d\n",Get());
	
	DisplayQueue();
}