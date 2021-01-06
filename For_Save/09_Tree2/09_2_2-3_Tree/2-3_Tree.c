//https://www.cs.usfca.edu/~galles/visualization/BTree.html 
//https://woongsin94.tistory.com/25 참고하기. 
//기본적인 것은 다 책에 작성해놨으니 코드작성하고 노트에 정리하기
//avl과는 다르게 인위적으로 예시를 만들수가 없고 그럴 필요도도 낮아 그냥 편하게 만들기. 
//delete과정은 어려울수도 있음
//https://tubuk.tistory.com/8
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);

void Level_Traverse(NODE *ptrNode);
void Visit(NODE *);
void InsertNode(int Data);
void DeleteNode(int Data);
void InitializeTree(void);
void SplitNode(NODE *, NODE *);

NODE *HeadNode;
NODE *ParentNode;

int main(void)
{
	InitializeTree();
	int x;
	
	Level_Traverse(HeadNode->Left);
	x=10;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	x=20;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	x=15;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	x=13;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	x=5;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	x=12;
	printf("\n==Insert %d",x);
	InsertNode(x);
	Level_Traverse(HeadNode->Left);
	DeleteNode(12);
	return 0;
}

void InitializeTree(void)
{
	HeadNode = (NODE *)malloc(sizeof *HeadNode);
	HeadNode->Left = HeadNode;
	HeadNode->Mid = HeadNode;
	HeadNode->Right= HeadNode;
}

void Level_Traverse(NODE *ptrNode)
{
	puts("");
	InitializeQueue();
	Put(ptrNode);
	int cnt = 0;
	while(!IsQueueEmpty())
	{
		cnt++;
		ptrNode = Get();
		Visit(ptrNode);
		printf(" -> ");
		
		if(ptrNode->Left != HeadNode)	
		{
			//printf("llllllllllll");
			Put(ptrNode->Left);
		}
		if(ptrNode->Mid != HeadNode)
		{
			//printf("mmmmmmmmmmmmmmmmmmmm");
			Put(ptrNode->Mid);
		}
		if(ptrNode->Right != HeadNode)
		{
			Put(ptrNode->Right);
			//printf("rrrrrrrrrrrr");
		}
		//printf("cnt : %d .",cnt);
		
	}
}
void Visit(NODE *ptrNode)
{
	printf("%2d(L)",ptrNode->LeftData);
	if(ptrNode->RightData != -1) printf("%2d(R)",ptrNode->RightData);
}

void InsertNode(int Data)
{
	NODE *tmpNode;
	int FlagSplit = 0;
	if(HeadNode->Left == HeadNode)
	{
		NODE *ptrNode;
		ptrNode =  (NODE *)malloc(sizeof(NODE));
		ptrNode->Left = HeadNode;
		ptrNode->Mid = HeadNode;
		ptrNode->Right= HeadNode;
		
		ptrNode->LeftData = Data;
		ptrNode->RightData = -1;
		
		HeadNode->Left = ptrNode;
		HeadNode->Mid = ptrNode;
		HeadNode->Right= ptrNode;
	}
	else
	{
		tmpNode = HeadNode->Left;
		ParentNode = HeadNode;
		while(1)
		{
			if(tmpNode->LeftData < Data)
			{
				if(tmpNode->RightData == -1)
				{
					FlagSplit = 0;
					break;
				}
				else
				{
					FlagSplit = 1;
					if(tmpNode->RightData >Data)
					{
						if(tmpNode->Mid == HeadNode)
						{
							break;//나가서 뭐하냐면 2 - 0 - 1이 되서 스플릿됨
						}
						else
						{
							ParentNode = tmpNode;
							tmpNode = tmpNode->Mid;
						}
					}
					else
					{
						if(tmpNode->Mid == HeadNode)
						{
							break;//나가서 뭐하냐면 2 - 0 - 0 - 1이 되서 스플릿됨
						}
						else
						{
							if(tmpNode->Right == HeadNode)
							{
								
							}
							ParentNode = tmpNode;
							tmpNode = tmpNode->Right;
							
						}	
					}
				}
			}
			else
			{
				if(tmpNode->Left == HeadNode)
				{
					if(tmpNode->RightData == -1)
					{
						FlagSplit = 0;
					}
					else
					{
						FlagSplit = 1;
					}
					break;
				}
				else
				{
					ParentNode = tmpNode;
					tmpNode = tmpNode->Left;
				}
			}
		}
		if(FlagSplit == 0 && tmpNode->RightData == -1)
		{
			if(tmpNode->LeftData < Data)
			{
				tmpNode->RightData = Data;
			}
			else
			{
				tmpNode->RightData = tmpNode->LeftData;
				tmpNode->LeftData = Data;
				
			}
		}
		else if(FlagSplit > 0)
		{
			NODE *ptrNode;
			ptrNode =  (NODE *)malloc(sizeof(NODE));
			ptrNode->Left = HeadNode;
			ptrNode->Mid = HeadNode;
			ptrNode->Right= HeadNode;

			ptrNode->LeftData = Data;
			ptrNode->RightData = -1;
			
			SplitNode(tmpNode,ptrNode);
			tmpNode = ParentNode->Left;
			
			if(ParentNode->RightData == -1)
			{
				ParentNode->RightData = ParentNode->LeftData;
				ParentNode->LeftData = tmpNode->LeftData;
				ParentNode->Right = ParentNode->Mid;
				ParentNode->Mid = tmpNode->Mid;
				ParentNode->Left = tmpNode->Left;
			}
			
		}
		
	}
}
void SplitNode(NODE *tmpNode, NODE *ptrNode)
{
	NODE *NewNode;
	NewNode = (NODE *)malloc(sizeof(NODE));
	NewNode->Left = HeadNode;
	NewNode->Mid = HeadNode;
	NewNode->Right= HeadNode;
	NewNode->RightData = -1;
	if(tmpNode->LeftData < ptrNode->LeftData)
	{
		if(tmpNode->RightData > ptrNode->LeftData)
		{
			NewNode->LeftData = tmpNode->RightData; 
			tmpNode->RightData = -1;
		}
		else
		{
			NewNode->LeftData = ptrNode->LeftData; 
			ptrNode->LeftData = tmpNode->RightData;
			tmpNode->RightData = -1;
		}
	}
	else
	{
		NewNode->LeftData = tmpNode->RightData; 
		tmpNode->RightData = tmpNode->LeftData;
		tmpNode->LeftData = ptrNode->LeftData;
		ptrNode->LeftData = tmpNode->RightData;
		tmpNode->RightData = -1;
	}
	ptrNode->Left = tmpNode;
	ptrNode->Mid = NewNode;
	ParentNode->Left = ptrNode;
	Level_Traverse(HeadNode->Left);
}
void DeleteNode(int Data)
{
	NODE *ptrNode,*ParentNode;
	ParentNode = HeadNode;
	int IsDataLeftData;
	ptrNode = HeadNode->Left;
	while(1)
	{
		if(ptrNode->LeftData > Data) // D L R
		{
			ParentNode = ptrNode;
			ptrNode = ptrNode->Left;
		}
		else if(ptrNode->RightData > Data) // L D R
		{
			ParentNode = ptrNode;
			ptrNode = ptrNode->Mid;
			
		}
		else // L R D
		{
			ParentNode = ptrNode;
			ptrNode = ptrNode->Right;
			
		}
		if(ptrNode->LeftData == Data)
		{
			IsDataLeftData = 1;
			break;
		}
		else if(ptrNode->RightData == Data)
		{
			IsDataLeftData = 0;
			break;
		}
	}
	//parent, ptr 완료
	//while문 이후에 ptrNode의 Left or Right == Data이다.
	while(1)
	{
		if(ptrNode->RightData != -1)
		{
			if(ptrNode->Left == HeadNode)
			{
				if(IsDataLeftData == 1)
				{
					ptrNode->LeftData = ptrNode->RightData;
				}
				else
				{
					ptrNode->RightData = -1;
				}
			}
			else
			{
				if(IsDataLeftData == 1)
				{
					if(ptrNode->Left->RightData == -1)//mm
					{
						
					}
					else//ll
					{
						
					}
				}
				else
				{
					ptrNode->RightData = -1;
				}				
			}
		}
		else
		{

		}		
	}
	
}