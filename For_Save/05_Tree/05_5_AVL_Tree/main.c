#include "node.h"

#define RR 1
#define LL 2

extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);

void InitializeTree(void);
void MakeTree(void);
void Level_Traverse(NODE *);
void Visit(NODE *);

void InsertNode(int);
int IsBalance(void);
void RRroute(void);
void LLroute(void);

NODE *LeftNode, *RightNode;
NODE *HeadNode;
NODE *GrandNode, *ParentNode, *ChildNode, *BigNode;
void InitializeTree(void)
{
	HeadNode = (NODE *)malloc(sizeof(NODE));
	
	HeadNode->Left = HeadNode;
	HeadNode->Right = HeadNode;
	
}

void Level_Traverse(NODE *ptrNode)
{
	InitializeQueue();

	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		Visit(ptrNode);
		if (ptrNode->Left != HeadNode)
			Put(ptrNode->Left);
		if (ptrNode->Right != HeadNode)
			Put(ptrNode->Right);
	}
}
void Visit(NODE *ptrNode)
{
	printf("%2d %d ->",ptrNode->Data,ptrNode->Balance);	
}

void InsertNode(int Data)
{
	NODE *tmpNode;
	NODE *ptrNode = (NODE *)malloc(sizeof(NODE));
	
	ptrNode->Right = HeadNode;
	ptrNode->Left = HeadNode;
	ptrNode->Data = Data;
	ptrNode->Balance = 0;
	
	if (HeadNode->Right == HeadNode)
	{
		HeadNode->Left = ptrNode;
		HeadNode->Right = ptrNode;
	}
	else
	{
		GrandNode = HeadNode;
		ParentNode = HeadNode;
		ChildNode = HeadNode->Right;
		tmpNode = HeadNode->Right;
		while(tmpNode != HeadNode)
		{
			ChildNode = tmpNode;
			
			if(ChildNode->Data > ptrNode->Data)
			{
				tmpNode = tmpNode->Left;
			}
			else
			{
				tmpNode = tmpNode->Right;
			}		
			BigNode = GrandNode;
			GrandNode = ParentNode;
			ParentNode = ChildNode;	
		}
		ChildNode = ptrNode;
		if(ParentNode->Data > ChildNode->Data)
		{
			ParentNode->Left = ChildNode;
			printf("\n==In put %d==\n",ChildNode->Data);
			printf("P%d +",ParentNode->Data);
			ParentNode->Balance++;
			
			if (GrandNode != HeadNode)
				GrandNode->Balance++;
				printf("G%d +",GrandNode->Data);
		}
		else
		{
			printf("\n==In put %d==\n",ChildNode->Data);
			ParentNode->Right = ChildNode;
			
			ParentNode->Balance--;
			printf("P%d -",ParentNode->Data);
			if (GrandNode != HeadNode)
			{
				
			
				GrandNode->Balance--;	
				printf("P%d -",GrandNode->Data);
				
			}
		}
		switch(IsBalance())
		{
			case RR :
				printf("\nRR\n");
				RRroute();
				break;
			case LL :
				printf("\nLL\n");
				LLroute();
				break;
			default :
				break;
				
		}
		
	}
	
	
}
int IsBalance(void)
{
	NODE *ptrNode;
	ptrNode = HeadNode->Right;
	int ret = 0;
	InitializeQueue();
	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		if (ptrNode->Balance > 1)
		{
			printf("riched LL ");
			ret = LL;
			break;
		}
		if (ptrNode->Balance < -1)
		{	
			ret = RR;
			break;
		}

		if (ptrNode->Left != HeadNode)
			Put(ptrNode->Left);
		if (ptrNode->Right != HeadNode)
			Put(ptrNode->Right);	
	}
	return ret;
}
void RRroute(void)
{
	ParentNode = GrandNode->Right;
	ChildNode = ParentNode->Right;
	if (GrandNode->Balance == -2)
	{
		BigNode->Right = ParentNode;
		ParentNode->Left = GrandNode;
		GrandNode->Right = HeadNode;
		GrandNode->Left = HeadNode;
	}
	BigNode->Balance++;
	ParentNode->Balance = 0;
	GrandNode->Balance = 0;
	ChildNode->Balance = 0;
	
}
void LLroute(void)
{
	ParentNode = GrandNode->Left;
	ChildNode = ParentNode->Left;
	if (GrandNode->Balance == 2)
	{
		BigNode->Left = ParentNode;
		ParentNode->Right = GrandNode;
		GrandNode->Right = HeadNode;
		GrandNode->Left = HeadNode;
	}
	BigNode->Balance--;
	ParentNode->Balance = 0;
	GrandNode->Balance = 0;
	ChildNode->Balance = 0;
	
}


void main(void)
{
	InitializeTree();
	
	puts("\n======\n30 20 40 10 insert");

	InsertNode(30);
	printf("Level_Traverse :");
	Level_Traverse(HeadNode->Right);
	InsertNode(20);
	printf("Level_Traverse :");
	Level_Traverse(HeadNode->Right);
	InsertNode(40);
	printf("Level_Traverse :");
	Level_Traverse(HeadNode->Right);
	InsertNode(10);
	printf("Level_Traverse :");
	Level_Traverse(HeadNode->Right);
	
	InsertNode(5);
	printf("Level_Traverse :");
	Level_Traverse(HeadNode->Right);

}