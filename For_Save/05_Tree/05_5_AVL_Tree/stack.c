#include "node.h"
#define MAX 100

NODE *Stack[MAX];
int Top;

void InitializeStack(void);
void Push(NODE *);
NODE *Pop(void);
int IsStackEmpty(void);


void InitializeStack(void)
{
	Top = 0;	
}
void Push(NODE *ptrNode)
{
	Stack[Top++] = ptrNode;
	
	Top = Top % MAX;
}
NODE *Pop(void)
{
	NODE *ptrNode;
	
	while(!IsStackEmpty()) {
		//return Stack[--Top];
		
		
		ptrNode = Stack[--Top];
		return ptrNode;
		
	}
	
	return NULL;
}
int IsStackEmpty(void)
{
	if(Top == 0) return TRUE;
	else return FALSE;
		
}