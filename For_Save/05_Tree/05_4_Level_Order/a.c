#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

typedef struct _NODE {
	int Data;
	struct _NODE *Left;
	struct _NODE *Right;
	
} NODE;

void InitializeQueue(void);
void Put(NODE *);
NODE *Get(void);
int IsQueueEmpty(void);
void InitializeTree(void);
void MakeTree(int d1, int d2);
void Visit(NODE *);
void Reset_Stack(void);
NODE *Search_Tree(int);
NODE *Search_Parent(int);
void Level_Traverse(NODE *ptrNode);

NODE *Queue[MAX];
int Rear, Front;


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



NODE *HeadNode,*EndNode;
void InitializeTree(void)
{
	HeadNode = (NODE *)malloc(sizeof(NODE));
	EndNode = (NODE *)malloc(sizeof(NODE));
	
	HeadNode->Left = EndNode;
	HeadNode->Right = EndNode;
	
	EndNode->Left = EndNode;
	EndNode->Right = EndNode;
}
void MakeTree(int d1, int d2)
{
	NODE *Parent, *LeftChild, *RightChild;
	NODE *ptrNode;
	int Parent_Data,Child_Data;
	if(d1 == 1)
	{
		Parent_Data = d1;
		Child_Data = d2;
	}
	else if(d2 == 1)
	{
		Parent_Data = d2;
		Child_Data = d1;
	}
	else(Search_Tree(d1) != EndNode)
	{
		Parent_Data = d1;
		Child_Data = d2;
	}
	else
	{
		Parent_Data = d2;
		Child_Data = d1;
	}
	Parent = Search_Tree(Parent_Data);
	if(Parent->Left == EndNode)
	{
		LeftChild = (NODE *)malloc(sizeof(NODE));
		LeftChild->Data = Child_Data;
		LeftChild->Left = EndNode;
		LeftChild->Right = EndNode;	
		Parent->Left = LeftChild;
	}
	else
	{	
		RightChild = (NODE *)malloc(sizeof(NODE));
		RightChild->Data = d3;
		RightChild->Left = EndNode;
		RightChild->Right = EndNode;	
		Parent->Right = RightChild;		
	}
	
}
NODE *Search_Tree(int c)
{
	NODE *PutNode;
	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		if(ptrNode->Data == c) return ptrNode;
		if(ptrNode->Left != EndNode) Put(ptrNode->Left);	
		if(ptrNode->Right != EndNode)Put(ptrNode->Right);	
	}
	return EndNode;
}
NODE *Search_Parent(int c)
{
	NODE *PutNode;
	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		if(ptrNode->Left->Data == c) return ptrNode;
		if(ptrNode->Right->Data == c) return ptrNode;
		if(ptrNode->Left != EndNode) Put(ptrNode->Left);	
		if(ptrNode->Right != EndNode)Put(ptrNode->Right);	
	}
	return EndNode;
}
void Level_Traverse(NODE *ptrNode)
{
	NODE *PutNode;
	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		Visit(ptrNode);
		if(ptrNode->Left != EndNode) Put(ptrNode->Left);	
		if(ptrNode->Right != EndNode)Put(ptrNode->Right);	
	}
}
int main(void)
{
	int Node_Size;
	char Data1,Data2;
	/*
	7
	1 6
	6 3
	3 5
	4 1
	2 4
	4 7
	*/
	InitializeQueue();
	InitializeTree();
	scanf("%d",&Node_Size);
	for(int i=0; i<Node_Size; i++)
	{
		scanf(" %c %c",&Data1,&Data2);
		MakeTree(Data1,Data2);
	}
	for(int i = 2; i<=Node_Size; i++)
	{
		puts("%d",Search_Parent(i)->Data);
	}
	
	return 0;
	
}