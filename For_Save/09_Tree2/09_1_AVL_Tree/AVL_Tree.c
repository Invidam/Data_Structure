
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
//http://egloos.zum.com/printf/v/913998 보고 수정하기 hegiht, 구하기, RL , LR 수식, isbal->RR,RL등등으로 가ㅡㄴ 조건 고민해보기. 

extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);

void Level_Traverse(NODE *ptrNode);
void Visit(NODE *);
NODE *InsertNode(NODE *, int Data);
NODE *DeleteNode(NODE *, int Data);
NODE *Rotate_Right(NODE *);
NODE *Rotate_Left(NODE *);
NODE *RR_Rotate(NODE *);
NODE *LL_Rotate(NODE *);
NODE *LR_Rotate(NODE *);
NODE *RL_Rotate(NODE *);
int GetHeight(NODE *);
int BalanceFactor(NODE *);

int main(void)
{
	NODE *Root = NULL;
	int x,op;
	do
	{
		printf("\n1) Create Tree");
		printf("\n2) Insert Tree");
		printf("\n3) Delete Tree");
		printf("\n4) Display Tree");
		printf("\n5) Quit");
		printf("\n\nEnter your choice :");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1: 
				printf("\nEnter Data :");
				scanf("%d",&x);
				Root = NULL;
				Root = InsertNode(Root, x);
				break;
			case 2:
				printf("\nEnter Data :");
				scanf("%d",&x);
				Root = InsertNode(Root, x);
				break;
			case 3: 
				printf("\nEnter Data :");
				scanf("%d",&x);
				Root = DeleteNode(Root, x);
				break;
			case 4: 
				Level_Traverse(Root);
				break;
			case 5: 
				break;
				
		}
	}while(op != 5);

	return 0;
}


void Level_Traverse(NODE *ptrNode)
{
	InitializeQueue();
	Put(ptrNode);
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		Visit(ptrNode);
		printf("->");
		
		if(ptrNode->Left != NULL)	Put(ptrNode->Left);
		if(ptrNode->Right != NULL)	Put(ptrNode->Right);
		
	}
}
void Visit(NODE *ptrNode)
{
	printf("%2d(%d)",ptrNode->Data,BalanceFactor(ptrNode));
}

NODE *InsertNode(NODE *ptrNode, int x)
{
	if(ptrNode == NULL)
	{
		ptrNode = (NODE *)malloc(sizeof(NODE));
		ptrNode->Data = x;
		ptrNode->Left = NULL;
		ptrNode->Right = NULL;
	}
	else
	{
		if(ptrNode->Data > x) // ptr->L = x;
		{
			ptrNode->Left  = InsertNode(ptrNode->Left,x);
			if(BalanceFactor(ptrNode) == 2)
			{
				if(x < ptrNode->Left->Data)
				{
					ptrNode = LL_Rotate(ptrNode);
				}
				else
					ptrNode = LR_Rotate(ptrNode);
			}
		}
		else if(ptrNode->Data < x) // ptr->R = x;
		{
			ptrNode->Right  = InsertNode(ptrNode->Right,x);
			if(BalanceFactor(ptrNode) == -2)
			{
				if(x > ptrNode->Right->Data)
				{
					ptrNode = RR_Rotate(ptrNode);
				}
				else
					ptrNode = RL_Rotate(ptrNode);
			}
		}
	}
	ptrNode->Height = GetHeight(ptrNode);
	return ptrNode;
}
NODE *DeleteNode(NODE *ptrNode, int x)
{
	NODE *tmpNode;
	//null = 맨밑 -> return null
	//x < or x > case구분, x= 일때 p에 대해서 실행
	if(ptrNode == NULL)
		return NULL;
	else
	{
		if(ptrNode->Data < x) // R측
		{
			ptrNode->Right = DeleteNode(ptrNode->Right,x);
			if(BalanceFactor(ptrNode)==2)
			{
				if(BalanceFactor(ptrNode->Left) >= 0)
					ptrNode = LL_Rotate(ptrNode);
				else
					ptrNode = LR_Rotate(ptrNode);
			}
		}
		else if(ptrNode->Data > x) // R측
		{
			ptrNode->Left = DeleteNode(ptrNode->Left,x);
			if(BalanceFactor(ptrNode)==-2)
			{
				if(BalanceFactor(ptrNode->Right) <= 0)
					ptrNode = RR_Rotate(ptrNode);
				else
					ptrNode = RL_Rotate(ptrNode);
			}
		}
		else
		{
			if(ptrNode->Right != NULL)
			{
				tmpNode = ptrNode->Right;
				while(tmpNode != NULL)
					tmpNode = tmpNode->Left;
				ptrNode->Data = tmpNode->Data;
				ptrNode->Right = DeleteNode(ptrNode->Right,tmpNode->Data);
				if(BalanceFactor(ptrNode)==2)
				{
					if(BalanceFactor(ptrNode->Left) >= 0)
						ptrNode = LL_Rotate(ptrNode);
					else
						ptrNode = LR_Rotate(ptrNode);
				}
			}
			else
				return ptrNode->Left;
		}
	}
	ptrNode->Height = GetHeight(ptrNode);
	return ptrNode;
}
NODE *Rotate_Right(NODE *x)
{
	NODE *y;
	y= x->Left;
	x->Left = y->Right;
	y->Right = x;
	x->Height = GetHeight(x);
	y->Height = GetHeight(y);
	return y;
}
NODE *Rotate_Left(NODE *x)
{
	NODE *y;
	y= x->Right;
	x->Right = y->Left;
	y->Left = x;
	x->Height = GetHeight(x);
	y->Height = GetHeight(y);
	return y;
	
}
NODE *LL_Rotate(NODE *ptrNode)
{
	ptrNode = Rotate_Right(ptrNode);
	return ptrNode;
}
NODE *RR_Rotate(NODE *ptrNode)
{
	ptrNode = Rotate_Left(ptrNode);
	return ptrNode;
	
}NODE *LR_Rotate(NODE *ptrNode)
{
	ptrNode->Left = Rotate_Right(ptrNode->Left);
	ptrNode = Rotate_Left(ptrNode);
	return ptrNode;
	
}NODE *RL_Rotate(NODE *ptrNode)
{
	ptrNode->Right = Rotate_Left(ptrNode->Right);
	ptrNode = Rotate_Right(ptrNode);
	return ptrNode;
	
}
int GetHeight(NODE *ptrNode)
{
	int lh,rh;
	if(ptrNode == NULL)
	{
		return 0;
	}
	if(ptrNode->Left == NULL)
		lh = 0;
	else 
		lh = 1+ptrNode->Left->Height;
	if(ptrNode->Right == NULL)
		rh = 0;
	else 
		rh = 1+ptrNode->Right->Height;
	if (lh > rh)
		return lh;
	else 
		return rh;
}
int BalanceFactor(NODE *ptrNode)
{
	int lh,rh;
	if(ptrNode == NULL)
	{
		return 0;
	}
	if(ptrNode->Left == NULL)
		lh = 0;
	else 
		lh = 1+ptrNode->Left->Height;
	if(ptrNode->Right == NULL)
		rh = 0;
	else 
		rh = 1+ptrNode->Right->Height;
	return lh-rh;
}
//https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
//정리한거 종이보고 정리하기. bf에 따른 lr , rl 등등의 움직임 정리.
//왜 재긔호출을 하며 포인터를 리턴하는지 고우하기,
//힙정렬 한번 복습하고  del과정에서 비슷한점 찾기.
//rl , lr 회전의 의미와 rotate right등의 의미 이해하기.
	/*
#include<stdio.h>
 
typedef struct node
{
	int data;
	struct node *left,*right;
	int ht;
}node;
 
node *insert(node *,int);
node *Delete(node *,int);
void preorder(node *);
void inorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
 
int main()
{
	node *root=NULL;
	int x,n,i,op;
	
	do
	{
		printf("\n1)Create:");
		printf("\n2)Insert:");
		printf("\n3)Delete:");
		printf("\n4)Print:");
		printf("\n5)Quit:");
		printf("\n\nEnter Your Choice:");
		scanf("%d",&op);
		
		switch(op)
		{
			case 1: printf("\nEnter no. of elements:");
					scanf("%d",&n);
					printf("\nEnter tree data:");
					root=NULL;
					for(i=0;i<n;i++)
					{
						scanf("%d",&x);
						root=insert(root,x);
					}
					break;
				
			case 2: printf("\nEnter a data:");
					scanf("%d",&x);
					root=insert(root,x);
					break;
					
			case 3: printf("\nEnter a data:");
					scanf("%d",&x);
					root=Delete(root,x);
					break;
			
			case 4: printf("\nPreorder sequence:\n");
					preorder(root);
					printf("\n\nInorder sequence:\n");
					inorder(root);
					printf("\n");
					break;			
		}
	}while(op!=5);
	
	return 0;
}
 
node * insert(node *T,int x)
{
	if(T==NULL)
	{
		T=(node*)malloc(sizeof(node));
		T->data=x;
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(x > T->data)		// insert in right subtree
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)
				if(x>T->right->data)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(x<T->data)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)
					if(x < T->left->data)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}
 
node * Delete(node *T,int x)
{
	node *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(x > T->data)		// insert in right subtree
		{
			T->right=Delete(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(x<T->data)
			{
				T->left=Delete(T->left,x);
				if(BF(T)==-2)	//Rebalance during windup
					if(BF(T->right)<=0)
						T=RR(T);
					else
						T=RL(T);
			}
			else
			{
				//data to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					T->data=p->data;
					T->right=Delete(T->right,p->data);
					
					if(BF(T)==2)//Rebalance during windup
						if(BF(T->left)>=0)
						{
							printf("LLLL");
							T=LL(T);
						}
						else
						{
							printf("LRLR");
							T=LR(T);
						}
				}
				else
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
 
int height(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}
 
node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
 
node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	preorder(y);
	inorder(y);
	
	return(y);
}
 
node * RR(node *T)
{
	T=rotateleft(T);
	return(T);
}
 
node * LL(node *T)
{
	T=rotateright(T);
	return(T);
}
 
node * LR(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	
	return(T);
}
 
node * RL(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
 
int BF(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);
}
 
void preorder(node *T)
{
	if(T!=NULL)
	{
		printf("%d(Bf=%d)",T->data,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}
 
void inorder(node *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		printf("%d(Bf=%d)",T->data,BF(T));
		inorder(T->right);
	}
}
*/