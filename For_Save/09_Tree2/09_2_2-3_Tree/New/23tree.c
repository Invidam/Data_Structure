#include <stdio.h>
#include <stdlib.h>
#include "23tree.h"

typedef struct _stack_item {
	NODE *node;
	enum {
		LEFT = -1,
		MIDDLE = 0,
		RIGHT = 1,
	} path;
}stack_item;
typedef struct _NODE NODE;

struct _NODE {
	
	int key[2];
	struct _NODE *Left;
	struct _NODE *Mid;
	struct _NODE *Right;
};


NODE *node_create(int key1, int key2)
{
	NODE *ptrNode;
	
	ptrNode = malloc(sizeof(NODE));
	ptrNode->Left =NULL;
	ptrNode->Mid =NULL;
	ptrNode->Right =NULL;
	ptrNode->key[0] =key1;
	ptrNode->key[1] = key2;
	
	return ptrNode;
}

void Level_Traverse(NODE *ptrNode)
{
	puts("");
	InitializeQueue();
	if(ptrNode != NULL) Put(ptrNode);
	else printf("NULL");
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		Visit(ptrNode);
		printf(" -> ");
		
		if(ptrNode->Left != NULL)	
		{
			//printf("llllllllllll");
			Put(ptrNode->Left);
		}
		if(ptrNode->Mid != NULL)
		{
			//printf("mmmmmmmmmmmmmmmmmmmm");
			Put(ptrNode->Mid);
		}
		if(ptrNode->Right != NULL)
		{
			Put(ptrNode->Right);
			//printf("rrrrrrrrrrrr");
		}
		//printf("cnt : %d .",cnt);
		
	}
}
void Visit(NODE *ptrNode)
{
	printf("%2d(L)",ptrNode->key[0]);
	if(ptrNode->key[1] > 0) printf("%2d(R)",ptrNode->key[1]);
}

int InsertNode(NODE **root,int key)
{
	NODE *iterator;
	NODE *new_node;
	stack_item stack[100];
	int key_idx,top=0,i;
	
	new_node = node_create(key,-1);
	if(*root == NULL)
	{
		*root = new_node;
		return 0;
	}
	
	iterator = *root;
	while(iterator != NULL)
	{
		if(key < iterator->key[0]) // X < L
		{
			stack[top].node = iterator;
			stack[top].path = LEFT;
			top++;
			iterator = iterator->Left;

		}
		else if(key < iterator->key[1] || iterator->key[1] < 0 ) // L < X < R
		{
			stack[top].node = iterator;
			stack[top].path = MIDDLE;
			top++;
			iterator = iterator->Mid;
		}
		else													// R < X
		{
			stack[top].node = iterator;
			stack[top].path = RIGHT;
			top++;
			iterator = iterator->Right;

		}
	}
	int ret = 0;
	
	iterator = new_node;
	
	i = top;
	while(--i >= 0)
	{
		if(stack[i].node->key[0] >= 0  && stack[i].node->key[1] >= 0) //3n
		{
			if(stack[i].path == LEFT)
			{
				NODE *right;
				right = node_create(stack[i].node->key[1],-1);
				right->Left = stack[i].node->Mid;
				right->Mid = stack[i].node->Right;

				stack[i].node->key[1] = -1;
				stack[i].node->Left = iterator;
				stack[i].node->Mid = right;
				stack[i].node->Right = NULL;

				iterator = stack[i].node; // it가 상위노드로 이동.

				if( i==0) *root = iterator; //모든 변경이 끝난 후, 바뀐 root를 적용시킨다.
			}
			else if(stack[i].path == MIDDLE)
			{
				NODE *right;
				right =node_create(stack[i].node->key[1],-1);
				right->Left = iterator->Mid;
				right->Mid = stack[i].node->Right;
				stack[i].node->Mid = iterator->Left;
				stack[i].node->Right = NULL;
				
				stack[i].node->key[1] = -1;
				
				iterator->Left = stack[i].node;
				iterator->Mid = right;
				if( i==0) *root = iterator; //모든 변경이 끝난 후, 바뀐 root를 적용시킨다.

			}
			else if(stack[i].path == RIGHT)
			{
				NODE *parent;
				
				parent = node_create(stack[i].node->key[1],-1);
				
				parent->Left = stack[i].node;
				parent->Mid = iterator;
				
				stack[i].node->key[1] = -1;
				stack[i].node->Right = NULL; //원래 없었ㅇ므..;
				if(i==0) *root = parent; //이 경우에는 parent가 iterator의 부모이다.
				else iterator = parent; //변경 주체인 it에 변경된 상위노드인 parent를 저장.
				
			}
		}
		else if(stack[i].node->key[0] >= 0)	//2n
		{
			if(stack[i].path == LEFT)   //	10 	
										//	5,7	20,30일 때, 4추가시 벌어질 상황임. 즉 언밸(+)
			{
				stack[i].node->key[1] = stack[i].node->key[0];
				stack[i].node->key[0] = iterator->key[0];
				stack[i].node->Right = stack[i].node->Mid;
				stack[i].node->Mid = iterator->Mid;
				stack[i].node->Left = iterator->Left;
			}
			else if(stack[i].path == MIDDLE)
			{
				stack[i].node->key[1] = iterator->key[0];
				stack[i].node->Mid = iterator->Left;
				stack[i].node->Right = iterator->Mid;
				
			}
			free(iterator);
			break;
		}
		
	}
}
static inline NODE *find_node(NODE *iterator, int key, int *idx,stack_item *stack,int *top)
{
	int i = *top;
	while(iterator != NULL)
	{
		if(key < iterator->key[0]) // X < L
		{
			stack[i].node = iterator;
			stack[i].path = LEFT;
			i++;
			iterator = iterator->Left;

		}
		else if(key == iterator->key[0])
		{
			*idx = 0;
			break;
		}
		else if(key < iterator->key[1] || iterator->key[1] < 0 ) // L < X < R
		{
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;
			iterator = iterator->Mid;
		}
		else if(key == iterator->key[1])
		{
			*idx = 1;
			break;
		}
		else if(key > iterator->key[1])							// R < X
		{
			stack[i].node = iterator;
			stack[i].path = RIGHT;
			i++;
			iterator = iterator->Right;
		}
	}
	*top = i;
	return iterator;
}
static inline NODE *find_successor(NODE *iterator,int *idx,stack_item *stack,int *top)
{ // *root를 *ite로 받아서, it->key[] 등의 코드로 간편화.
	NODE *successor = NULL;
	int i = *top;
	
	if( *idx == 0)
	{
		if(iterator->Mid != NULL)
		{
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;
			
			iterator = iterator->Mid;
			while(iterator->Left != NULL)
			{
				stack[i].node = iterator;
				stack[i].path = LEFT;
				i++;
				
				iterator = iterator->Left;
			}
			successor = iterator;
		}
		else if(iterator->Left != NULL)
		{
			stack[i].node = iterator;
			stack[i].path = LEFT;
			i++;
			
			iterator = iterator->Left;
			
			while(iterator)
			{
				stack[i].node = iterator;
				//어차피 --i를 호출하므로 i++이 되지않는이상 문제될게 없어, else일 경우에도 실행한다
				if(iterator->Right != NULL)
				{
					stack[i].path = RIGHT;
					i++;
					iterator = iterator->Right;
				}
				else if(iterator->Mid != NULL && iterator->key[1] <0)
				{
					stack[i].path = MIDDLE;
					i++;
					iterator = iterator->Mid;
				}
				else //mid가 비어있으므로, 무조건 it->left-> ... -> left->key[1]이 successor이다.
				{
					break;
				}
			}
			*idx = 1;
			successor = iterator;
		}
		else
		{
			successor = iterator;
		}
	}
	else if (*idx == 1)
	{

		if(iterator->Right != NULL)
		{
			stack[i].node = iterator;
			stack[i].path = RIGHT;
			i++;
			
			iterator = iterator->Right;
			while(iterator->Left != NULL)
			{
				stack[i].node = iterator;
				stack[i].path = LEFT;
				i++;
				
				iterator = iterator->Left;
			}
			successor = iterator;
			*idx = 0;
		}	
		else if(iterator->Mid != NULL)
		{
			stack[i].node = iterator;
			stack[i].path = MIDDLE;
			i++;
			
			iterator = iterator->Mid;
			while(iterator)
			{
				stack[i].node = iterator;
				//어차피 --i를 호출하므로 i++이 되지않는이상 문제될게 없어, else일 경우에도 실행한다
				if(iterator->Right != NULL)
				{
					stack[i].path = RIGHT;
					i++;
					iterator = iterator->Right;
				}
				else if(iterator->Mid != NULL && iterator->key[1] <0)
				{
					stack[i].path = MIDDLE;
					i++;
					iterator = iterator->Mid;
				}
				else //무조건 it->mid->...->mid->key[1] 이 successor이다.
				{
					break;
				}
			}
			successor = iterator;
		}
		else
		{
			successor = iterator;
		}
	}
	*top = i;
	return successor;
}
static inline void shift_left(NODE *node,int new_value,NODE *new_right)
{//오른쪽이 ㅔ벨이 낮아 왼쪽에다가 붙임. sib= 2n, pa = 2n ptr = 2n일때. 밑에도 마찬가지.
	node->Left = node->Mid;
	node->Mid = node->Right;
	node->Right = new_right;
	
	node->key[0] = node->key[1];
	node->key[1] = new_value;
}
static inline void shift_right(NODE *node,int new_value,NODE *new_left)
{//왼쪽이 레벨이 낮아 그때 오른쪽에 왼쪽걸 붙임 그후 상위노드에 sh_L 단, 이걸해도 레벨은 맞지않다.
	node->Right = node->Mid;
	node->Mid = node->Left;
	node->Left = new_left;
	
	node->key[1] = node->key[0];
	node->key[0] = new_value;
}
static inline int is_empty(NODE *ptrNode)
{
	return (ptrNode->key[0] <0 ) && (ptrNode->key[1] < 0);
}
static inline int is_full(NODE *ptrNode)
{
	return (ptrNode->key[0] >=0 ) && (ptrNode->key[1] >=0);
}
int DeleteNode(NODE **root,int key)
{
	NODE *iterator;
	NODE *successor;
	stack_item stack[256];
	int key_idx;
	int top = 0;
	int i;
	iterator = find_node(*root,key,&i,stack,&top);
	if(iterator == NULL) return -1; // root삭제
	key_idx = i;
	//iterator = find_node(*root,key,&key_idx,stack,&top);
	//key_idx , i 차이점은 i는 iterator의 인덱스고 key_idx는 successor의 인덱스.
	successor = find_successor(iterator,&key_idx,stack,&top);
	if(successor == NULL) return -1; // root삭제
	
	iterator->key[i] = successor->key[key_idx];
	successor->key[key_idx] = -1;
	if (key_idx == 1 ) return 0; //key_idx == 1일 때, key[1] = -1시키면 됨 끝임. 왜냐하면 successor->Right이 존재하지 않기에 key_idx 가 1이 된 것이기 때문
	if(successor->key[1] >=0)
	{
		shift_left(successor,-1,NULL);//각각 요소는  shift할 포인터, 우측에 채워질 밸류, 우측에 연결될 포인터
		return 0;
	}
	
	i = top;
	iterator = successor; // 변경된 iterator에 대해 재배치 시작.
	while(--i >= 0)
	{
		if(stack[i].path == LEFT)
		{
			if(is_empty(stack[i].node->Left))
			{
				//왼쪽이 존재했으면(삭제됐으므로 과거형), 중앙은 당연히 존재한다.
				//왼쪽은 자식도 없다.
				if(is_full(stack[i].node->Mid))
				{//mid에서 빌린다.
					stack[i].node->Left->key[0] = stack[i].node->key[0];
					stack[i].node->key[0] = stack[i].node->Mid->key[0];
					stack[i].node->Left->Mid = stack[i].node->Mid->Left;
					//ML은  i<ml<m 였으므로,   i->l   m->i가 됬으므로 ml -> lm이 된다. l<lm<i
					stack[i].node->Mid->Left = stack[i].node->Mid->Mid;
					//비슷한 맥락
					stack[i].node->Mid->Mid = stack[i].node->Mid->Right;
					stack[i].node->Mid->Right = NULL; // 2node됫으니 rigt는 삭제
					stack[i].node->Mid->key[0] = stack[i].node->Mid->key[1];
					stack[i].node->Mid->key[1] = -1;
					break; // break 뜻 : 삭제는 했지만 depth는 그대로다.
				}
				else
				{//mid가 2node일 때
					if(is_full(stack[i].node)) // i가 3node 즉,right도 존재.
					{//i에서 하나 가져오고, R->M, M->L이 된다.
						stack[i].node->Left->key[0] = stack[i].node->key[0];
						stack[i].node->Left->key[1] = stack[i].node->Mid->key[0];
						
						stack[i].node->Mid->key[0] = stack[i].node->key[1];
						stack[i].node->key[1]= -1;
						
						stack[i].node->Left->Mid = stack[i].node->Mid->Left;										//ML은  i<ml<m 였으므로,   i->l   m->i가 됬으므로 ml -> lm이 된다. l<lm<i
						// MR은 없다. 왜냐하면 2node
						stack[i].node->Left->Right = stack[i].node->Mid->Mid;
						
						free(stack[i].node->Mid);
						
						stack[i].node->Mid = stack[i].node->Right;
						stack[i].node->Right = NULL;
						break;

					}
					else // P, Sib === 2node
					{//depth change.
						NODE *left;
						NODE *mid;
						
						left = stack[i].node->Left;
						mid = stack[i].node->Mid;
						
						stack[i].node->key[1] = mid->key[0];
						stack[i].node->Right = mid->Mid;
						stack[i].node->Mid = mid->Left;
						stack[i].node->Left = NULL;
						
						free(left);
						free(mid);
					}
				}
			}
			else // L에서 뺏는데, 하나가 남아있다? 즉 while문이 두번째 실행된경우. depth가 줄어든 경우.
			{
				if(is_full(stack[i].node->Mid))
				{
					NODE *node;
					
					node = node_create(stack[i].node->key[0],-1);
					
					node->Left = stack[i].node->Left;
					stack[i].node->Left = node;
					node->Mid = stack[i].node->Mid->Left;
					
					stack[i].node->key[0] = stack[i].node->Mid->key[0];
					
					shift_left(stack[i].node->Mid,-1,NULL);
					break;
				}
				else
				{
					if(is_full(stack[i].node))
					{
						shift_right(stack[i].node->Mid,stack[i].node->key[0],stack[i].node->Left);
						shift_left(stack[i].node,-1,NULL);
						break;
					}
					else
					{
						NODE *mid;
						mid = stack[i].node->Mid;
						stack[i].node->key[1] = mid->key[0];
						stack[i].node->Right = mid->Mid;
						stack[i].node->Mid = mid->Left;
						
						free(mid);
					}
				}
			}
		}
		else if(stack[i].path == MIDDLE)
		{
			if(is_empty(stack[i].node->Mid)) //비어있으므로 LMR은 leaf이다.
			{
				if(stack[i].node->Left != NULL && is_full(stack[i].node->Left))
				{//P->M , L->P
					stack[i].node->Mid->key[0] = stack[i].node->key[0];
					stack[i].node->key[0] = stack[i].node->Left->key[1];
					stack[i].node->Left->key[1] = -1;
					stack[i].node->Mid->Left = stack[i].node->Left->Right; //M,R은 어차피 leaf다.
					stack[i].node->Left->Right = NULL;
					break;
					
				}
				else if(stack[i].node->Right != NULL && is_full(stack[i].node->Right))
				{
					stack[i].node->Mid->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = stack[i].node->Right->key[0];
					stack[i].node->Mid->Mid = stack[i].node->Right->Left; // 근데 ML이 없는거보면 leaf인듯.
						
					shift_left(stack[i].node->Right,-1,NULL);
					break;
					
				}
				else //L or R 이 2node이다.
				{
					if(is_full(stack[i].node))
					{// Pa = 3n 즉 L이 2n
						free(stack[i].node->Mid); //free된 자리에 무언가는 다시 드어온다.
						stack[i].node->Mid = NULL;
						
						stack[i].node->Left->key[1] = stack[i].node->key[0];
						stack[i].node->Left->Mid = stack[i].node->Mid; //이미 NULL..
						
						stack[i].node->Mid = stack[i].node->Right;
						stack[i].node->Right = NULL;
						
						stack[i].node->key[0] = stack[i].node->key[1];
						stack[i].node->key[1] = -1;
						
						break;
						
						
					}
					else
					{// Par, Mid 다 2n 즉, L도 2n
						NODE *left;
						
						left = stack[i].node->Left;
						free(stack[i].node->Mid);
						stack[i].node->Mid = NULL;
						
						stack[i].node->key[1] = stack[i].node->key[0];
						stack[i].node->key[0] = left->key[0];
						
						stack[i].node->Right = stack[i].node->Mid;
						stack[i].node->Mid = left->Mid;
						stack[i].node->Left = left->Left;
						
						free(left);
					}
				}				
			}
			else // 비어있지 않을 때, unbal한 상황..
			{
				if(stack[i].node->Left != NULL && is_full(stack[i].node->Left))
				{
					NODE *node;
					node =node_create(stack[i].node->key[0],-1);
					stack[i].node->key[0] = stack[i].node->Left->key[1];
					stack[i].node->Left->key[1] = -1;
					node->Left = stack[i].node->Left->Right;
					stack[i].node->Left->Right = NULL;
					node->Mid = stack[i].node->Mid;
					stack[i].node->Mid = node;
					break;
				}
				else if(stack[i].node->Right != NULL && is_full(stack[i].node->Right))
				{
					NODE *node;
					node  = node_create(stack[i].node->key[1],-1);
					stack[i].node->key[1] = stack[i].node->Right->key[0];
					node->Mid = stack[i].node->Right->Left;
					node->Left = stack[i].node->Mid;
					stack[i].node->Mid = node;
					shift_left(stack[i].node->Right,-1,NULL);
					
					break;
				}
				else //L or R 이 2node이다.
				{
					if(is_full(stack[i].node))
					{
						stack[i].node->Left->key[1] = stack[i].node->key[0];
						stack[i].node->Left->Right = stack[i].node->Mid;
						stack[i].node->key[0] = stack[i].node->key[1];
						stack[i].node->key[1] = -1;
						stack[i].node->Mid = stack[i].node->Right;
						stack[i].node->Right = NULL;
						
						break;
					}
					else
					{// Par, Mid 다 2n 즉, L도 2n R은 null
						NODE *left;
						left = stack[i].node->Left;
						
						shift_right(stack[i].node,-1,NULL);
						stack[i].node->key[0] = left->key[0];
						stack[i].node->Left = left->Left;
						stack[i].node->Mid = left->Mid;
						free(left);
						//stack[i]의 height이 감소함.	
					}
				}
			}
		}
		else if(stack[i].path == RIGHT)
		{
			if(is_empty(stack[i].node->Right))
			{
				if(is_full(stack[i].node->Mid))
				{//M->P P->R
					stack[i].node->Right->key[0] = stack[i].node->key[1];
					stack[i].node->key[1] = stack[i].node->Mid->key[1];
					stack[i].node->Mid->key[1] = -1;
					stack[i].node->Right->Left =stack[i].node->Mid->Right;
					stack[i].node->Mid->Right = NULL;
					
					break;	
				}
				else// mid 2n, pa 3n
				{
					stack[i].node->Mid->key[1] = stack[i].node->key[1];
					free(stack[i].node->Right);
					stack[i].node->Right = NULL;
					stack[i].node->key[1] = -1;
					
					break;
					//우측을 아예 삭제함.
				}
			}
			else // R = 3node //   참고) 2node일때에는 맨위에서 걸려짐 ㅇ
			{
				if(is_full(stack[i].node->Mid))
				{
					NODE *node;
					node = node_create(stack[i].node->key[1],-1);
					stack[i].node->key[1] = stack[i].node->Mid->key[1];
					stack[i].node->Mid->key[1] = -1;
					
					node->Left = stack[i].node->Mid->Right;
					stack[i].node->Mid->Right = NULL;
					node->Right = stack[i].node->Right;
					stack[i].node->Right = node;
					
					break;
				}
				else // mid 2n, pa 3n, r 3n.
				{
					stack[i].node->Mid->key[1] = stack[i].node->key[1];
					stack[i].node->key[1] = -1;
					stack[i].node->Mid->Right = stack[i].node->Right;
					stack[i].node->Right = NULL;
					
					break;
				}
			}
		}
	}
	if( i < 0 && is_empty(*root))
	{
		free(*root);
		*root = NULL;
	}
	return 0;
}
