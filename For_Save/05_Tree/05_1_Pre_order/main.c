#include "node.h"

extern void InitializeStack(void);
extern void Push(NODE *);
extern NODE *Pop(void);
extern int IsStackEmpty(void);

void InitializeTree(void);
void MakeTree(void);
void Stack_Traverse(NODE *);
void Recursive_Traverse(NODE *);
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
void Stack_Traverse(NODE *ptrNode)
{
	
	Push(ptrNode)
	while(!IsStackEmpty())
	{
		ptrNode = Pop();
		Visit(ptrNode);
		
		if(ptrNode->Right != EndNode) Push(ptrNode->Right);
		if(ptrNode->Left != EndNode) Push(ptrNode->Left);
	}

}
void Recursive_Traverse(NODE *ptrNode)
{
	
	if(ptrNode->Left != EndNode) Recursive_Traverse(ptrNode->Left);
	if(ptrNode->Right != EndNode) Recursive_Traverse(ptrNode->Right);
	Visit(ptrNode);
	
}
void Visit(NODE *ptrNode)
{
	printf("%2c ->",ptrNode->Data);	
}


void main(void)
{
	InitializeStack();
	InitializeTree();
	MakeTree();
	puts("Recursive_Traverse");
	Recursive_Traverse(HeadNode->Left);
	puts("End\nStack_Traverse");
	Stack_Traverse(HeadNode->Left);
	puts("End");
	
}