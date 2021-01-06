#include "node.h"
#define MAX 5000

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
	
	if(Top >= MAX) Top = Top % MAX;
}
NODE *Pop(void)
{
	return Stack[--Top];
	
}
int IsStackEmpty(void)
{
	return !Top;
	
}