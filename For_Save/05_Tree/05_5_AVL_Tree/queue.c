#include "node.h"
#define MAX 100

NODE *Queue[MAX];
int Front,Rear;

void InitializeQueue(void);
void Put(NODE *);
NODE *Get(void);
int IsQueueEmpty(void);


void InitializeQueue(void)
{
	Rear = Front = 0;
}
void Put(NODE *ptrNode)
{
	Queue[Rear++] = ptrNode;
	Rear = Rear % MAX;
}
NODE *Get(void)
{
	NODE *ptrNode;
	if(!IsQueueEmpty())
	{
	ptrNode = Queue[Front++];
	Front  = Front % 100;
		
	return ptrNode;

	}
	//else return NULL;
}
int IsQueueEmpty(void)
{
	if (Rear == Front)
	{
		return TRUE;
		
	}
	else return FALSE;
	
	
}