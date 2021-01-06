#include "node.h"

void IntializeTree(void);
void MakeTree(void);
void Recursive_Traverse(NODE *);
void Visit(NODE *);
void Stack_Traverse(NODE *);

extern void InitializeStack(void);
extern void Push(NODE *);
extern NODE *Pop(void);
extern int IsStackEmpty(void);

void IntializeTree(void)
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
	NODE *Parent, *LeftChild, *RightChild;

	
	Parent = (NODE *)malloc(sizeof(NODE));
	Parent->Data = 'A';
		
	LeftChild = (NODE *)malloc(sizeof(NODE));
	LeftChild->Data = 'B';
	
	RightChild = (NODE *)malloc(sizeof(NODE));
	RightChild->Data = 'C';
	
	
	Parent->Left = LeftChild;
	Parent->Right = RightChild;
	
	HeadNode->Left = Parent;
	HeadNode->Right = Parent;
	
	Parent = Parent->Left;	

	
	LeftChild = (NODE *)malloc(sizeof(NODE));
	LeftChild->Data = 'D';
	LeftChild->Left = EndNode;
	LeftChild->Right = EndNode;
	
	RightChild = (NODE *)malloc(sizeof(NODE));
	RightChild->Data = 'E';
	RightChild->Left = EndNode;
	RightChild->Right = EndNode;
	
	Parent->Left = LeftChild;
	Parent->Right = RightChild;
	
	Parent = HeadNode->Left->Right;
	
	LeftChild = (NODE *)malloc(sizeof(NODE));
	LeftChild->Data = 'F';
	LeftChild->Left = EndNode;
	LeftChild->Right = EndNode;
	
	RightChild = (NODE *)malloc(sizeof(NODE));
	RightChild->Data = 'G';
	RightChild->Left = EndNode;
	RightChild->Right = EndNode;
	
	Parent->Left = LeftChild;
	Parent->Right = RightChild;
	
}
void Recursive_Traverse(NODE *ptr)
{
	if(ptr->Left != EndNode) Recursive_Traverse(ptr->Left);
	Visit(ptr);
	if(ptr->Right != EndNode) Recursive_Traverse(ptr->Right);
	
}
void Visit(NODE *ptr)
{
	printf("%2c ->",ptr->Data);
	
}
void Stack_Traverse(NODE *ptrNode)
{
	do 
	{
		while(ptrNode != EndNode)
		{
			Push(ptrNode);
			ptrNode = ptrNode->Left;
		}
		if(!IsStackEmpty())
		{
			ptrNode = Pop();
			Visit(ptrNode);
			ptrNode = ptrNode->Right;			
		}
		else break;

				
	}
	while(1);
}


int main(void)
{
	IntializeTree();
	MakeTree();
	printf("Recursive_Traverse :");
	Recursive_Traverse(HeadNode->Left);
	puts("End");
	
	printf("Stack_Traverse :");
	Stack_Traverse(HeadNode->Left);
	puts("End");	
	
	
	
}