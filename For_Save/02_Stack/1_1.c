#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
	int Data;
	struct _NODE *Next;
}NODE;

NODE *head,*ptrNode,*end;

void Initialize(void);
void Push(int);
int Pop(void);
void DisplayStack(void);

void Initialize(void)
{
	
	head = (NODE *)malloc(sizeof(NODE));
	end = (NODE *)malloc(sizeof(NODE));
	
	head->Next= end;
	end->Next = end;
}
void Push(int num)
{
	ptrNode = (NODE *)malloc(sizeof(NODE));
	ptrNode->Data = num;
	ptrNode->Next = head->Next;
	head->Next = ptrNode;
		
}
int Pop(void)
{
	int ret;
	ptrNode = head->Next;
	ret = ptrNode->Data;
	head->Next = ptrNode->Next;
	
	free(ptrNode);
	return ret;
}
void DisplayStack(void)
{
	NODE *IndexNode;
	for(IndexNode = head; IndexNode != end; IndexNode = IndexNode->Next)
	{	
		if((IndexNode != head) && (IndexNode != end))
		{	
			printf("%d",IndexNode->Data);
			if(IndexNode->Next != end) printf("-> ");
			
		}
	}
	
	
}
void main()
{
	Initialize();
	
	printf("\nBefore Push :");
	DisplayStack();
	
	Push(1);
	Push(2);
	Push(3);
	Push(4);
	Push(5);
	printf("\nAfter Push: ");
	DisplayStack();

	printf("\nAfter Pop :");
	printf("\nPop : %d",Pop());
	printf("\nPop : %d",Pop());
	printf("\nPop : %d\n",Pop());
	
	DisplayStack();
	
}
