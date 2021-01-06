#include "node.h"

extern void InitializeStack(void);
extern void Push(NODE *);
extern NODE *Pop(void);
extern int IsStackEmpty(void);

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

void Recursive_Traverse(NODE *ptrNode)
{
	if (ptrNode != EndNode)
	{
		Recursive_Traverse(ptrNode->Left);
		Recursive_Traverse(ptrNode->Right);
		Visit(ptrNode);
	}
	
}
void Stack_Traverse(NODE *ptrNode)
{

	NODE *Visited, *Poped;
	Poped = ptrNode;
	
	Push(ptrNode);
	
	do
	{
		ptrNode = Pop();
		Poped = ptrNode; 
		if(((ptrNode->Left == EndNode) && (ptrNode->Right == EndNode)))
		{
			Visit(ptrNode);
			Visited = ptrNode;					
		}
		else if((ptrNode == Poped) && ((ptrNode->Left != Visited) && (ptrNode->Right != Visited)))
		{
			Push(ptrNode);
			if(ptrNode->Right != EndNode) Push(ptrNode->Right);
			if(ptrNode->Left != EndNode) Push(ptrNode->Left);
		}
		else
		{
			Visit(ptrNode);
			Visited = ptrNode;			
		}
	}while(!IsStackEmpty());

}
void Visit(NODE *ptrNode)
{
	printf("%2c ->",ptrNode->Data);	
}


void main(void)
{
	printf("!@#");
	InitializeStack();
	InitializeTree();
	MakeTree();
	
	printf("Recursive_Traverse :");
	Recursive_Traverse(HeadNode->Left);
	
	
	printf("Stack_Traverse :");
	Stack_Traverse(HeadNode->Left);
	
}