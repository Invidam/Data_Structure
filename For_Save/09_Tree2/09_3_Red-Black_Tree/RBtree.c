/*
https://plzrun.tistory.com/entry/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EB%AC%B8%EC%A0%9C%ED%92%80%EC%9D%B4PS-%EC%8B%9C%EC%9E%91%ED%95%98%EA%B8%B0
http://gujoron.com/xe/gangron/445860
*/
#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"
enum color_tree {RED = 0, BLACK};
typedef struct _NODE NODE;
struct _NODE {
	
	int key;
	struct _NODE *left;
	struct _NODE *right;
	struct _NODE *parent;
	enum color_tree color;
};

static inline int Insert_Repair_Tree(NODE *node);
static inline void InsertCase4_Step2(NODE *node);
static inline void DeleteCase1(NODE *node);
static inline void DeleteCase2(NODE *node);
static inline void DeleteCase3(NODE *node);
static inline void DeleteCase4(NODE *node);
static inline void DeleteCase5(NODE *node);
static inline void DeleteCase6(NODE *node);
NODE *node_create(int key)
{
	NODE *ptrNode;
	
	ptrNode = (NODE *)malloc(sizeof(NODE));
	
	ptrNode->key = key;
	ptrNode->parent = NULL;
	ptrNode->left = NULL;
	ptrNode->right = NULL;
	ptrNode->color = RED;
	return ptrNode;
}

void Level_Traverse(NODE *ptrNode)
{
	puts("");
	InitializeQueue();
	if
		(ptrNode != NULL) Put(ptrNode);
	else 
		printf("NULL");
	while(!IsQueueEmpty())
	{
		ptrNode = Get();
		Visit(ptrNode);
		printf(" -> ");
		if(ptrNode->left != NULL) Put(ptrNode->left);
		if(ptrNode->right != NULL) Put(ptrNode->right);
	}
}
void Visit(NODE *ptrNode)
{

	if(ptrNode->key > 0)
		printf("%d(%d)",ptrNode->key,ptrNode->color);

}
static inline NODE *GetParent(NODE *n)
{
	return (n == NULL) ? NULL : n->parent; 
	//n이 널이면 널 아니면 부모
}
static inline NODE *GetGrandParent (NODE *n)
{
	return GetParent(GetParent(n));
	
}
static inline NODE *GetSibling(NODE *n)
{
	NODE *p = GetParent(n);
	if(p == NULL) return NULL;
	if(p->left == n) return p->right;
	else return p->left;
}
static inline NODE *GetUncle(NODE *n) 
{
	NODE *p = GetParent(n);
	return GetSibling(p);	
}
static inline int Rotate_Left(NODE *n) 
{
/*

\  ->   \
		/
		
/  ->    /  
\		/
트리의 위치만 고려하면 이렇고, 실제는 부모 자식이 바뀔수도 있으며 위 두가지 경우가 아닐 때에는 /\ 꼴이 될수도 있따.

*/
	NODE *p = n->parent;
	NODE *nnew = n->right;//n을 대채
	
	n->right = nnew->left;
	if(n->right != NULL)
		n->right->parent = n;

	n->parent = nnew;
	nnew->left = n;
	nnew->parent = p;
	
	if(p == NULL) return 0;
	
	if(p->left == n)
		p->left = nnew;
	else
		p->right = nnew;
	return 0;
}
static inline int Rotate_Right(NODE *n)
{
/*


 /  ->  /
/		\
		
/  ->   \  
\		 \

트리의 위치만 고려하면 이렇고, 실제는 부모 자식이 바뀔수도 있으며 위 두가지 경우가 아닐 때에는 /\ 꼴이 될수도 있따.
*/
	NODE *p = GetParent(n);
	if(n->left == NULL) return 0;
	NODE *nnew = n->left;//n을 대채
	
	n->left = nnew->right;
	if(n->left != NULL)
		n->left->parent = n;
	
	nnew->right = n;
	n->parent = nnew;
	nnew->parent = p;
	
	if(p == NULL) return 0;
	
	if(p->right == n)
		p->right = nnew;
	else
		p->left = nnew;
	return 0;
	
}
static inline int Insert_Recurse(NODE *root, NODE *node)
{
	if(root == NULL) return 0;
	else if(root->key > node->key)
	{
		if(root->left != NULL)
		{
			Insert_Recurse(root->left,node);
			return 0;
		}
		else
		{
			root->left = node;
		}
	}
	else
	{
		if(root->right != NULL)
		{
			Insert_Recurse(root->right,node);
			return 0;
		}
		else
		{
			root->right = node;
		}
	}
	node->parent = root;
	//printf("\n insert_recurse %d end",node->key);
	return 0;
}

static inline void InsertCase1(NODE *node)
{
	node->color = BLACK;
}
static inline void InsertCase2(NODE *node)
{
	//아무것도 안해도 된다. n->c = R; 인 경우.
}
static inline void InsertCase3(NODE *node)
{
	GetParent(node)->color = BLACK;
	GetUncle(node)->color = BLACK;
	GetGrandParent(node)->color = RED;
	
	Insert_Repair_Tree(GetGrandParent(node));
	//이 코드의 경우는 손자까지 딸린 노드가 새로 생성되었다고 생각하면 된다. 이전까지의 상황과 독립적인 상황이다.
}   // Case3까지는 색깔만 바꿔도 특성들을 만족시킨다. #Insert_Repair_Tree(GetGrandParent)인 것을 고려하지 않았을 경우

static inline void InsertCase4(NODE *node)
{
	NODE *g =  GetGrandParent(node);
	NODE *p =  GetParent(node);
	
	if(g->left == p && p->right == node) 
	{
		Rotate_Left(p);
		node = node->left; //노드가 p와 바뀜 바뀐 p를 노드로 지정.
	}
	else if(g->right == p && p->left == node)
	{
		Rotate_Right(p);
		node = node->right; //노드가 p와 바뀜 바뀐 p를 노드로 지정.	
	}
	InsertCase4_Step2(node);
}
static inline void InsertCase4_Step2(NODE *node)
{
	NODE *g =  GetGrandParent(node);
	NODE *p =  GetParent(node);	
	if(p->left == node)
	{
		Rotate_Right(g);
	}
	else
	{	
		Rotate_Left(g);
	}
	
	g->color = RED;
	p->color = BLACK;
	
}
static inline int Insert_Repair_Tree(NODE *node)
{
	if(GetParent(node) == NULL)
		InsertCase1(node);
	else if(GetParent(node)->color == BLACK)
		InsertCase2(node);	
	else if(GetUncle(node) != NULL && GetUncle(node)->color == RED)
		InsertCase3(node);
	else
	{
		 InsertCase4(node);
	}
}

NODE *InsertNode(NODE *root,int key)
{
	
	NODE *node = node_create(key);
	Insert_Recurse(root,node);
	Insert_Repair_Tree(node);
	
	
	root = node;
	while(root->parent != NULL)
	{
		root = root->parent;
	}
	return root;
	//루트가 바뀌었을 수도 있으니 찾아보고 갱신한다.
//예전꺼는 root의 주소를 넘겨받으며 함수간의 root의 정보를 갱신했는데
//이번꺼는 root를 리턴하며 갱신함

	return 0;
}
static inline NODE *find_node(NODE *root, int key)
{
	if(root->key == key)
		return root;
	return (root->key > key) ? (find_node(root->left, key)) : (find_node(root->right, key));
}
static inline NODE *find_successor(NODE *node)
{
	int key = node->key;
	if(node->left != NULL)
	{
		node = node->left;
		while(node->right != NULL)
		{
			node = node->right;
		}
	}
	else if(node->right != NULL)
	{
		node = node->right;
		while(node->left !=NULL)
		{
			node = node->left;
		}
	}
	//else	if(node->right == NULL && node->left == NULL)
		 //leaf일 때.
	return node;
}
static inline void replace_node(NODE *node,NODE *child)
{ 
	child->parent = node->parent;
	if(node->parent != NULL)
	{
		if(node->parent->left == node)
		{
			node->parent->left = child;
		}
		else
		{
			node->parent->right = child;
		}		
	}
	//node의 자식들은 아직도 node를 부모로 가르키고 있지 않나?
	//그렇지 않음 왜냐면, node는 있어봤짜 자식이 하나고 그 자식이 child이기 때문에 그렇지 않음.
	//이 함수 이후, 어느것도 node를 가르키고 있지 않다.
	node->parent = child;
}
static inline void change_key(NODE *node,NODE *successor)
{
	int tmp_key;
	
	tmp_key = node->key;
	node->key = successor->key;
	successor->key = tmp_key;
	
}
static inline void DeleteCase1(NODE *node)
{	//기존의 child가 node라는 변수로 들어온다. (위치는 노드와 같지만, leaf이다.)
	if(node->parent != NULL) //다행히 기존 노드의 부모를 부모로 가지고 왓따.
		DeleteCase2(node);
	
	//root노드가 제거되었을 때 -> 아무것도 안해도 된다.

}
static inline void DeleteCase2(NODE *node)
{
	//삭제하기 편한 형태로 고친다. (완성X)
	NODE *p = node->parent;
	NODE *s = GetSibling(node);
	if(s->color == RED)
	{
		p->color = RED;
		s->color = BLACK;
		if(p->left = node)
		{
			Rotate_Left(p);
		}
		else
		{
			Rotate_Right(p);	
		}
	}
	DeleteCase3(node);
}
static inline void DeleteCase3(NODE *node)
{	
	NODE *s = GetSibling(node);
	if((node->parent->color == BLACK) && (s->color == BLACK) && (s->left == NULL || s->left->color == BLACK ) && (s->right == NULL || s->right->color == BLACK))
	{
		s->color = RED;
		DeleteCase1(node->parent);
	}
	else
		DeleteCase4(node);
}
static inline void DeleteCase4(NODE *node)
{
	NODE *s = GetSibling(node);
	//(node->parent->color == RED) && (s->color == BLACK) && (s->left->color == BLACK || s->left == NULL) && (s->right->color == BLACK || s->right == NULL)
	if((node->parent->color == RED) && (s->color == BLACK)&& (s->left == NULL || s->left->color == BLACK ) && (s->right == NULL || s->right->color == BLACK))
	{
		s->color = RED;
		node->parent->color = BLACK;
	}
	else
	{
		DeleteCase5(node);
	}
}
static inline void DeleteCase5(NODE *node)
{
	NODE *s = GetSibling(node);
	
	if(node == node->parent->left &&  s->left->color == RED && (s->right == NULL || s->right->color == BLACK))
	{
		s->color = RED;
		s->left->color = BLACK;
		Rotate_Right(s);
	}
	else if(node == node->parent->right && s->right->color == RED && (s->left == NULL || s->left->color == BLACK ))
	{
		s->color = RED;
		s->right->color = BLACK;
		Rotate_Left(s);
		
	}	
	DeleteCase6(node);
}
static inline void DeleteCase6(NODE *node)
{
	NODE *s = GetSibling(node);
	s->color = node->parent->color;
	node->parent->color = BLACK;
	if(node == node->parent->left)
	{
		s->right->color = BLACK;
		Rotate_Left(node->parent);
		
	}
	else //n == n->parent->right
	{
		s->left->color = BLACK;
		Rotate_Right(node->parent);
	}
}


static inline int DeleteOneChild(NODE *node)
{
	NODE *parent;
	NODE *child;
	NODE *LEAF;
	if(node->left == NULL && node->right == NULL)
	{
		LEAF = malloc(sizeof(NODE));
		LEAF->color = BLACK;
		node->left = LEAF;
		node->right = LEAF;
		LEAF->parent = node;
		LEAF->left = NULL;
		LEAF->right = NULL;
	}
	child = (node->right == LEAF) ? (node->left) : (node->right);
	replace_node(node,child); 
	//관계를 바꾼다. (위치를 바꾼다)

	
	if(node->color == BLACK)
	{
		if(child->color == RED)
		{
			child->color == BLACK;

		}
		else
		{
			DeleteCase1(child); //노드가 아니라 child에 대해 실행한다.
		}
	}
	free(node);
	parent = LEAF->parent;
	if(parent != NULL)
	{
		if(LEAF == parent->left)
		{
			parent->left = NULL;
		}
		else //leaf= parent->right
		{
			parent->right = NULL;
		}
	}
	else
	{ 	
		free(LEAF);
		return -1;
	}
	free(LEAF);
	//색깔 검사.
	/*
	In delete case,
	노드가 검정, 자식이 검정인 경우(노드의 자식이 둘다 리프임)
	->case3에서 걸린다
	->그후 부모가 case2에 걸려 바뀌게 된다.
	*/
	return 0;
}


NODE *DeleteNode(NODE *root, int key)
{
	NODE *node = find_node(root, key);
	NODE *successor = find_successor(node);
	change_key(node,successor);
	//node와 suc은 키만 바꾸고, suc에 대해 삭제를 진행하는데 node는 이제 신경쓰지 않는다.
	key = DeleteOneChild(successor);
	if(key == -1) root = NULL;
	/*
	case2 통과후 N,S는 모두 검
	P, S_L, S_R에 대해
	  색상	해결되는 케이스
	  
	검 검 검		 3
	빨 검 검		 4
	검 빨 검		 5
	빨 빨 검		 5
	검 검 빨		 6
	빨 검 빨		 6
	검 빨 빨		 6
	빨 빨 빨		 6
	*/
	return root;
}

