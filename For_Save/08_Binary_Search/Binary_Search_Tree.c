#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE 
{
	int key;
	struct _NODE *Left;
	struct _NODE *Right;
}NODE;

void BSTInitialize(int);
void BSTInsert(int, NODE *);
void MakeNode(int , NODE *, NODE *);

int cnt = 0;
NODE *Head,*End;

int main(void)
{
	int n,temp;
	scanf(" %d",&n);
	scanf(" %d",&temp);
	BSTInitialize(temp);
	printf("%d\n",cnt);
	for(int i=1; i< n; i++)
	{
		scanf(" %d",&temp);
		BSTInsert(temp,Head);
		printf("%d\n",cnt);
	}
}
void BSTInitialize(int num)
{
	End = (NODE *)malloc(sizeof *End);
	End->Right = End;
	End->Left = End;
	End->key = -1;
	
	Head = (NODE *)malloc(sizeof *Head);
	Head->Right = End;
	Head->Left = End;
	Head->key = num;
	

}
void BSTInsert(int num, NODE *ptrNode)
{
	cnt++;
	//ptr = head;
	if(num < ptrNode->key)
	{
		if(ptrNode->Left == End) MakeNode(num,ptrNode,ptrNode->Left);
		else BSTInsert(num,ptrNode->Left);
	}
	else
	{
		if(ptrNode->Right == End) MakeNode(num,ptrNode,ptrNode->Right);
		else BSTInsert(num,ptrNode->Right);
		
	}
}
void MakeNode(int num, NODE *p, NODE *x)
{
	x = (NODE *)malloc(sizeof *x);
	x->key = num;
	x->Left = End;
	x->Right = End;
	
	if(num < p->key)
	{
		p->Left = x;
	}
	else
	{
		p->Right = x;
	}
}