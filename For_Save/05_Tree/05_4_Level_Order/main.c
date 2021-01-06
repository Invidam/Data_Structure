#include "node.h"

extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);
void InitializeTree(void);
void MakeTree(void);
void Queue_Traverse(NODE *);
void Visit(NODE *);

NODE *Parent, *LeftNode, *RightNode;
NODE *HeadNode, *EndNode;

void InitializeTree(void)
{
	HeadNode = (NODE *)malloc(sizeof(NODE));
	EndNode = (NODE *)malloc(sizeof(NODE));
	
	HeadNode->Left = EndNode;
	HeadNode->Right = EndNode;
	
	EndNode->Left = EndNode;
	EndNode->Right = EndNode;
}
void MakeTree(void)
{
	Parent = (NODE *)malloc(sizeof(NODE));
	Parent->Data = 'A';
	
	LeftNode = (NODE *)malloc(sizeof(NODE));
	LeftNode->Data = 'B';
	
	RightNode = (NODE *)malloc(sizeof(NODE));
	RightNode->Data = 'C';
	
	Parent->Left = LeftNode;
	Parent->Right = RightNode;
	
	HeadNode->Left = Parent;
	HeadNode->Right = Parent;
	
	Parent = Parent->Left;
	
	
	LeftNode = (NODE *)malloc(sizeof(NODE));
	LeftNode->Data = 'D';
	LeftNode->Left = EndNode;
	LeftNode->Right = EndNode;
	
	RightNode = (NODE *)malloc(sizeof(NODE));
	RightNode->Data = 'E';
	RightNode->Left = EndNode;
	RightNode->Right = EndNode;
	
	
	Parent->Left = LeftNode;
	Parent->Right = RightNode;	
	
	Parent = HeadNode->Right->Right;
	
	LeftNode = (NODE *)malloc(sizeof(NODE));
	LeftNode->Data = 'F';
	LeftNode->Left = EndNode;
	LeftNode->Right = EndNode;
	
	RightNode = (NODE *)malloc(sizeof(NODE));
	RightNode->Data = 'G';
	RightNode->Left = EndNode;
	RightNode->Right = EndNode;	

	Parent->Left = LeftNode;
	Parent->Right = RightNode;	

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
void Visit(NODE *ptrNode)
{
	printf("%2c ->",ptrNode->Data);	
}


void main(void)
{
	InitializeQueue();
	InitializeTree();
	MakeTree();
	
	Level_Traverse(HeadNode->Left);
	
	
}