#include <stdio.h>
#include <stdlib.h>
#include "234tree.h"

#define KEY 3
#define LINK 4

typedef struct _NODE NODE;
struct _NODE {
	
	int key[3];
	struct _NODE *child[4];
};
static inline NODE *grow_node(NODE *parent, int child_idx);
NODE *node_create(int key0, int key1, int key2)
{
	NODE *ptrNode;
	
	ptrNode = malloc(sizeof(NODE));
	
	ptrNode->child[0] = NULL;
	ptrNode->child[1] = NULL;
	ptrNode->child[2] = NULL;
	ptrNode->child[3] = NULL;
	
	ptrNode->key[0] = key0;
	ptrNode->key[1] = key1;
	ptrNode->key[2] = key2;	
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
		for(int i=0; i < LINK; i++)
		{
			if(ptrNode->child[i] != NULL)
				Put(ptrNode->child[i]);
		}	
	}
}
void Visit(NODE *ptrNode)
{
		for(int i=0; i < KEY; i++)
		{
			if(ptrNode->key[i] >0)
				printf("%d(%d)",ptrNode->key[i],i);
		}
}
static inline int count_key(NODE *node)
{
	if(node == NULL) return -1;
	return (node->key[0] >= 0) ? ((node->key[1] >= 0) ?((node->key[2] >= 0) ? 3 : 2) : 1 ) : 0;			//((node->key[2] >= 0) ? 3 : 2) 에서, key2가 있으면 3 없으면 2가 저장. 이를 x1이라고 한다.
	//((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1)에서, key1가 있으면  x1, 없으면 1을 저장(x2)
	//(node->key[0] >= 0) ? ((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1) : 0;
	//에서 key0이 있으면 x2, 없으면 0을 저장.
	//즉, key(n)까지 있으면 (n+1)을 저장한다. 
}
static inline int shift_right(NODE *node, int key_idx)
{//인덱스를 기준점으로 하여 좌측 것들을  우측으로 이동. 
	// 0 1 2
	//0 1 2 3	/모양을 기준으로한다
	do // 얘네를 switch로 안한 이유는 순서 때문.
	{
		node->key[2] = -1;
		node->child[3] = NULL;
		if(key_idx ==2) break;
		
		node->key[2] = node->key[1];
		node->child[3] = node->child[2];
		
		if(key_idx ==1) break;
		
		node->key[1] = node->key[0];
		node->child[2] = node->child[1];
		
		node->child[1] = node->child[0];
		
		node->key[0] = -1;
		node->child[0] = NULL;
	}while(0);
}
static inline int shift_left(NODE *node, int key_idx)
{//인덱스를 시작점으로 하여 우측것들을 좌측으로 이동. 
	// 0 1 2
	//0 1 2 3    /모양을 기준으ㅗ한다.
	switch(key_idx)
	{
		case 0:
			node->child[0] = node->child[1];
			node->key[0] = node->key[1];
		case 1:
			node->child[1] = node->child[2];
			node->key[1] = node->key[2];	
		case 2:
			node->child[2] = node->child[3];
			node->key[2] = -1;
			node->child[3] = NULL;	
			break;
	}
}
static inline void swap(int *a,int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static inline void split_node(NODE *parent,int key_idx,NODE *node)
{// idx= n, k[n]과 c[n+1]을 shift를 통해 비워준다. 그후 그자리에 스플릿을 한다
	NODE *right;
	right = node_create(node->key[2],-1,-1);
	right->child[0] = node->child[2];
	right->child[1] = node->child[3];
	
	if(parent == NULL)
	{
		NODE *left;
		left = node_create(node->key[0],-1,-1);
		left->child[0] = node->child[0];
		left->child[1] = node->child[1];
		
		node->child[0] = left;
		node->child[1] = right;
		
		node->key[0] = node->key[1];
		//삽입을 통해 레벨이 증가한다면, c[0,1]은 L가, c[2,3]은 R이 가져가며, k[1]이 부모가 된다.
	}
	else
	{
		shift_right(parent,key_idx);
		parent->key[key_idx] = node->key[1];
		parent->child[key_idx+1] = right;
		parent->child[key_idx] = node; // 원래 이상태이지 않나..? 
		
	}
	node->key[1] = -1;
	node->key[2] = -1;
	
	node->child[2] = NULL;
	node->child[3] = NULL;
}



static inline NODE *grow_node(NODE *parent, int child_idx)
{
	/*
	grow는 succ을 찾는 과정에서 count가 1인 노드를 찾아 키워주는 함수이다.
	그 과정은 다음과 같다.
	parent->child[child_idx]를 기준으로 하여, 이 노드의
	1. 좌형제의 키가 2개 이상
	2. 우형제의 키가 2개 이상
	3. 좌형제의 키가 있긴 할 때
	4. 우형제의 키가 있긴 할 때
	1.2번 과정은 간단히 가져오면 되지만
	3,4번 과정은 힘들게 형제 부모와 병합해야한다.
	
	*/
	int last_idx;
	NODE *grown_node = NULL;
	
	
	if(child_idx >= 1 && (last_idx = count_key(parent->child[child_idx - 1 ])) >= 2)
	{
		//맨왼쪽이 아니고 왼쪽이 3n일 때
		//왼쪽이 3n이상일때	
		// 	  1                    3
		// 2,3    4   ->       2      1,4 이 된다.
		//a,b,c  d,e          a,b    c,d,e
		shift_right(parent->child[child_idx], 0);
		parent->child[child_idx]->key[0] = parent->key[child_idx - 1];
		parent->key[child_idx - 1] = parent->child[child_idx - 1]->key[last_idx - 1];
		//last가 left의 인덱스의 갯수이다.
		parent->child[child_idx]->child[0] = parent->child[child_idx - 1]->child[last_idx];
		
		parent->child[child_idx - 1]->key[last_idx - 1] = -1;
		parent->child[child_idx - 1]->child[last_idx] = NULL;
		
		grown_node = parent->child[child_idx];

	}
	else if(child_idx <= 4 && count_key(parent->child[child_idx+1]) >= 2)
	{
		//맨오른쪽이 아니고 오른쪽이 3n일 때
		//오른쪽이 3n이상일때
		// 	  1                    3
		// 2,3    4   <-       2      1,4 이 된다.
		//a,b,c  d,e          a,b    c,d,e	
		parent->child[child_idx]->key[1] = parent->key[child_idx];
		parent->key[child_idx] = parent->child[child_idx + 1]->key[0];
		parent->child[child_idx]->child[1] = parent->child[child_idx]->child[0];
		
		parent->child[child_idx]->key[0] = -1;
		parent->child[child_idx]->child[0] = NULL;
		
		shift_left(parent->child[child_idx + 1], 0);
	
		grown_node = parent->child[child_idx];

	}
	else if (child_idx >= 1 && parent->child[child_idx -1 ] != NULL)
	{	//pa->ch[ch_idx]가 왼쪽형제이 있긴할때
		//이걸 물어보는 이유는 병합할때 좌측을 할건지 우측으 할건지 정해야 하기 때문
		//대부분 좌측이 존재할텐데 ( 왜냐면 0,1,2의 key가 있기 때문)
		//k = 0일때에만 좌측은 없고 우측만 있을 것
		//자식들은 크기에 따라 이동시킨다.
		NODE *left;
		NODE *right;
		if(count_key(parent) == 1)// 부모를 내린다.
		{
			// use the parent node
			//      0        
			//  1       2   ==>  1,0,2    
			// a,b     c,d      a,b,c,d
			
			left = parent->child[child_idx - 1];
			right = parent->child[child_idx];
			
			parent->child[child_idx - 1 ] = NULL;
			parent->child[child_idx] = NULL;
			
			parent->key[1] = parent->key[0];
			parent->key[0] = -1;
			
			parent->key[0] = left->key[0];
			parent->child[0] = left->child[0];
			parent->child[1] = left->child[1];
			free(left);	
			parent->key[2] = right->key[0];
			parent->child[2] = right->child[0];
			parent->child[3] = right->child[1];
			free(right);
			//0,1인 이유는 카운트가 1이라서, 2,3은 잇을수가없다.
			grown_node = parent;
			
		}
		else
		{	//부모를 내리는데 뎁스는 그대로
			//     0,1               0   
			//  1   2   3   ==>  1       2,1,3
			// a,b c,d e,f      a,b     c,d,e,f
			left = parent->child[child_idx - 1];
			right = parent->child[child_idx];
			
			parent->child[child_idx] = left;
			left->key[1] = parent->key[child_idx - 1 ];
			parent->key[child_idx - 1 ] = -1; //굳이 필요한가? 설명 위한건가?
			left->key[2] = right->key[0];
			left->child[2] = right->child[0];
			left->child[3] = right->child[1];
			
			free(right);
			
			shift_left(parent,child_idx-1);
			
			grown_node = left;
			
		}
	}
	else if (child_idx <= 2 && parent->child[child_idx + 1 ] != NULL)
	{		//노드의 맨왼쪽을 그로우 시킬때이다.
		NODE *left;
		NODE *right;
		if(count_key(parent) == 1)// 부모를 내린다.
		{
			// use the parent node
			//      0        
			//  1       2   ==>  1,0,2    
			// a,b     c,d      a,b,c,d
			
			left = parent->child[child_idx];
			right = parent->child[child_idx + 1];
			
			parent->key[1] = parent->key[0];
			parent->key[0] = -1;
			
			parent->key[0] = left->key[0];
			parent->child[0] = left->child[0];
			parent->child[1] = left->child[1];
			free(left);	
			parent->key[2] = right->key[0];
			parent->child[2] = right->child[0];
			parent->child[3] = right->child[1];
			free(right);
			//0,1인 이유는 카운트가 1이라서, 2,3은 잇을수가없다.
			grown_node = parent;
			
		}
		else
		{	//부모를 내리는데 뎁스는 그대로
			//     0,1'               0   
			//  1   2   3   ==>  1,2,1'    3
			// a,b c,d e,f      a,b,c,d   e,f
			left = parent->child[child_idx];
			right = parent->child[child_idx + 1];
			
			parent->child[child_idx + 1] = left;
			left->key[1] = parent->key[child_idx];
			//parent->key[child_idx - 1 ] = -1; //굳이 필요한가? 설명 위한건가?
			left->key[2] = right->key[0];
			
			left->child[2] = right->child[0];
			left->child[3] = right->child[1];
			
			free(right);
			
			shift_left(parent,child_idx);
			
			grown_node = left;
		}
	}
	else
	{
		printf("\nIn find_successor, It's leaf node.");
	}
	return grown_node;
}
int InsertNode(NODE **root,int key)
{
	NODE *iterator;
	NODE *leaf;
	
	if(*root == NULL)
	{
		*root = node_create(key,-1,-1);
		return 0;
	}
	iterator = *root;
	
	if(count_key(iterator) == 3)
	{
		split_node(NULL,-1,iterator);
	}
	while(iterator)
	{
		if(key < iterator->key[0])
		{
			if(count_key(iterator->child[0]) == 3)
			{
				split_node(iterator,0,iterator->child[0]);
				continue;
			}
			leaf = iterator;
			iterator = iterator->child[0];
		}
		else if(iterator->key[1] < 0 || key < iterator->key[1])
		{
			if(count_key(iterator->child[1]) == 3)
			{
				split_node(iterator,1,iterator->child[1]);
				continue;
			}
			leaf = iterator;
			iterator = iterator->child[1];	
		}
		else if(iterator->key[2] < 0 || key < iterator->key[2])
		{
			if(count_key(iterator->child[2]) == 3)
			{
				split_node(iterator,2,iterator->child[2]);
				continue;
			}
			leaf = iterator;
			iterator = iterator->child[2];
		}
		else//( key> iterator->key[2])
		{
			if(count_key(iterator->child[3]) == 3)
			{
				//@note
				//it가 3node고 c[3]도 3node일수는 없음 
				//
				split_node(iterator,0,iterator->child[0]);
				continue;
				
			}
			leaf = iterator;
			iterator = iterator->child[3];	
		}
		
	}
	
	int i;
	int tmp;
	tmp = key;
	for(i=0;i<KEY||tmp>=0;i++) //새로운 활용임
	{
		if(leaf->key[i]<0 || leaf->key[i] > tmp ) swap(leaf->key + i , &tmp);
		
	}
	return 0;
}
static inline int is_empty(NODE *ptrNode)
{
	return (ptrNode->key[0] <0 ) && (ptrNode->key[1] < 0);
}
static inline int is_full(NODE *ptrNode)
{
	return (ptrNode->key[0] >=0 ) && (ptrNode->key[1] >=0);
}
static inline int find_successor(NODE **node, int *key_idx, NODE **parent, NODE **successor, int *o_idx)
{
	int left_idx;
	int right_idx;
	int again;
	int key;
	NODE *tmp_node;
	int i;
	/*
	par= 부모
	nod = 자기
	tmp = 후임 확인하는 중인 곳
	gro = 성장한 곳
	suc = 후임후보로 확인된 곳
	*/
	do
	{		//key_idx 대신에 i로 갖고놀다가(for문) 리턴하거같은건 key_idx로 다룬다.
		again = 0;
		left_idx = *key_idx;
		right_idx = left_idx + 1;
		key = (*node)->key[left_idx];//**node.key[]임
		*successor = *node;
		*o_idx = *key_idx;
		if(right_idx <= 4 && (*node)->child[right_idx] != NULL)
		{//R_idx가 마지막이 아니고 오른쪽이 있으면 거기로 이동
			tmp_node = (*node)->child[right_idx];
			if(count_key(tmp_node) == 1)
			{
				NODE *grown_node;
				grown_node = grow_node(*node,right_idx);
				//suc중에 grow가 발견되면 키워주고, suc을 다시 찾는다.
				if (grown_node == NULL) 	//리프 노드이다.
				{
					return -1;
				}
				if(grown_node == *node)
				{//노드의 자식들중에 한 곳에서 후임을 찾는데, 그 과정에서 grow를 시켰을 때
				//grow된 위치가 노드일때.
				//즉, 자기 자식을 grow했는데 자기랑 병합했을 때 이다.
					for (i = 0; i < count_key(grown_node); i++)
					{
						if (grown_node->key[i] == key)
						{ 
							//노드의 자식이 노드랑 병합했을 때, 즉 키의 위치가 변하였다.
							*key_idx = i; //바뀐 키의 위치에 따른 바뀐 후임들의 위치를 지정하기 위해 컨티뉴한다.
											//키값의 위치를 특정짓기 위해 key_idx를 i로 ㅎ준다.
							again = 1;	//del함수에서도 key값의 위치를 이 함수에서 넘겨준 node와 i를 통해 찾는다.
							break;
						}
					}
					if(again == 1) continue;
					return -1; //exception
				}
				for(i=0;i < 3;i++)
				{
					if(grown_node->key[i] == key)	
					{	//키 값이 자식으로 넘어갔을 때,
						//노드는 키값이 있는 자식(grown_node)이 되고 key_idx도 자식에서 다시 찾아 컨티뉴 한다.
						
						*parent = *node;
						*node = grown_node;
						*key_idx = i;
						again = 1;
						break;
					} //여기 안걸리면 자식으로 키가 안간거임
				}
				if(again == 1) continue;
				
				tmp_node = grown_node;// 노드에 키가 있고, tmp는 후임들이 위치한 곳.
										// 성장하여, tmp의 위치도 바뀌었ㄴ을 수도 있으니 새로 지정.
				
			}
			//후임 찾기 시작~!
			*parent = *node; // 한칸 내려간다
			*successor = tmp_node; //tmp는 후임들이 위치한 곳
			*o_idx = 0;  // suc->k[o_i]이 key와 가장 유사함
			
			while((*successor)->child[0] != NULL)
			{
				if(count_key((*successor)->child[0]) == 1)
				{
					tmp_node = grow_node((*successor),0);
					if(tmp_node == (*successor))
					{//현재의 후임의 자식이 후임이랑 병합했을 때, 즉 맞 후임의위치를 
					 //특정할 수가 없게되어 컨티뉴해서 다시 맞후임의 위치를 찾는다 ㅠㅠ
						continue;
					}
				}
				
				*parent = (*successor);
				(*successor) = (*successor)->child[0];
			}
		}
		else if(left_idx >= 0 && (*node)->child[left_idx] != NULL)			
		{//L_idx가 처음이 아니고 왼쪽이 있으면 거기로 이동 (뎁스가 1이 아니면 다 있지않나..?싶음ㅎ)
			tmp_node = (*node)->child[left_idx];
			if(count_key(tmp_node) == 1)
			{
				NODE *grown_node;
				grown_node = grow_node(*node,left_idx);
				if(grown_node == NULL) return -1;
				if(grown_node == *node)//노드에 키가아직잇을떄
				{
					int i;
					for(i=0; i<count_key(grown_node);i++) 
					{
						if(key == grown_node->key[i])
						{
							again = 1;
							*key_idx = i;
							break;
						}
						
					}
					if(again == 1) continue;
				}
				for(i=0; i<count_key(grown_node);i++) //노드의 왼쪽에 키가 옮겨졋을때
				{
					if(key == grown_node->key[i])
					{
						*parent = *node;
						*node = grown_node;
						again = 1;
						*key_idx = i;
						break;
					}
				}
				if(again == 1) continue;
				
				tmp_node = grown_node; // 성장하여, tmp의 위치도 바뀌었ㄴ을 수도 있으니 새로 지정.
			}
			
			*parent = *node;
			*successor = tmp_node;
			*o_idx = count_key((*successor)) -1; //last idx와 같은 개념ㅇㅁ. suc의 최대 키값
			while((*successor)->child[(*o_idx) + 1 ] != NULL) // 맨 오른쪽 자식이 널인지 확인 자식이없는거 아니면 참
			{
				if(count_key((*successor)->child[*o_idx + 1]) == 1)
				{
					tmp_node = grow_node(*successor, (*o_idx )+ 1);
					if(tmp_node == *successor)
					{
						*o_idx = count_key((*successor)) -1; // 후임과 병합하여, suc의 요소의 갯수가 달라진걸고려.
															//위에선 무조건 idx가 0이엇지만 이번에는 변수니까 고려.
						continue;
					}
				}
				*parent = *successor;
				*successor = (*successor)->child[(*o_idx)+1];
				*o_idx = count_key((*successor)) -1;
			}
		}
		else
		{
		}
	} while (again);
	return 0;
}

int DeleteNode(NODE **root,int key)
{
	NODE *iterator;
	NODE *successor;
	NODE *parent;
	NODE *tmp_node;
	
	int o_i;
	int i;
	int cnt = 0;
	parent = NULL;
	iterator = *root;
	int stop = 1;
	while(iterator && stop)
	{

		for(i = 0; i< 3; i++)
		{
			if(iterator->key[i] < 0) break;
			else if(key == iterator->key[i])
			{
				find_successor(&iterator, &i, &parent, &successor, &o_i);
				iterator->key[i] = successor->key[o_i];
				if(count_key(successor) > 1)
				{
					shift_left(successor,o_i);
					stop = 0;
					break;
				}
				else if(parent == NULL) //루트 노드인 경우 + 카운트가 1인 경우 = 유일한 수 일때
				{
					free(*root);
					*root = NULL;
					stop = 0;
					break;
				}
				else //count_key == 1일떄 ~! 
				{
					int c_i; //child_idx
					for(c_i = 0; c_i < 4; c_i++)
					{
						if(parent->child[c_i] == successor) break;
					} //c_i를 지정.
					
					NODE *tmp_node;
					tmp_node = grow_node(parent,c_i); // successor은 항상 리프노드이다.
					if(tmp_node == parent)
					{
						successor = parent;
						for(i = 0; i<3; i++)
						{
							if(successor->key[i] == key) break;
						}
					}
					shift_left(successor,i); //이거ㅗㄹ 제거 i는 suc->[i] == 맞후임.
					stop = 0;
				}
				break; //키 일치한경우 제거다햇으니 브레이크 
				
			}
		}
	 //키가 일치할 때
		//앞으로는 모든 키가 일치하지 않았을 때 (it->key[n] != key or it->key[n] < 0 일 때이다.)
		int i_i;
		if(key < iterator->key[0])
		{
			i_i = 0;

			tmp_node = iterator->child[i_i];
			if(count_key(tmp_node) == 1)
			{
				tmp_node = grow_node(iterator,i_i);
				if(tmp_node == iterator)
				{//병합되어 올라왔을 때
					continue; //같은 노드에 대해서다시 while문 실행
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
		else if(key < iterator->key[1] || iterator->key[1] < 0) 
		{
			i_i = 1;

			tmp_node = iterator->child[i_i];
			if(count_key(tmp_node) == 1)
			{
				tmp_node = grow_node(iterator,i_i);
				if(tmp_node == iterator)
				{//병합되어 올라왔을 때
					continue; //같은 노드에 대해서다시 while문 실행
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
		else if(key < iterator->key[2] || iterator->key[2] < 0) 
		{
			i_i = 2;

			tmp_node = iterator->child[i_i];
			if(count_key(tmp_node) == 1)
			{
				tmp_node = grow_node(iterator,i_i);
				if(tmp_node == iterator)
				{//병합되어 올라왔을 때
					continue; //같은 노드에 대해서다시 while문 실행
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
		else if(key < iterator->key[3] || iterator->key[3] < 0) 
		{
			i_i = 3;

			tmp_node = iterator->child[i_i];
			if(count_key(tmp_node) == 1)
			{
				tmp_node = grow_node(iterator,i_i);
				if(tmp_node == iterator)
				{//병합되어 올라왔을 때
					continue; //같은 노드에 대해서다시 while문 실행
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
	}
	return 0;
}	
	
	
	

