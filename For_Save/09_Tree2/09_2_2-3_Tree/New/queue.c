#include "23tree.h"
#define MAX 5000


NODE *Queue[MAX];
int Rear, Front;

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
	NODE *Indexptr;
	
	Indexptr = Queue[Front++];
	
	Front = Front % MAX;
	
	return Indexptr;
	
}
int IsQueueEmpty(void)
{
	return (Rear == Front);
}


