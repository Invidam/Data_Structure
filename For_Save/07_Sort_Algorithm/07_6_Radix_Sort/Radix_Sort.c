#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
#define MAXINDEX 10

typedef struct _NODE
{
	int Data;
	struct _NODE *Next;
}NODE;

NODE *ptrNode;
NODE *Rear[MAX];
NODE *Front[MAX];
int Buffer[MAXINDEX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void RadixSort(int);
void DisplayBuffer(void);
int FindDigit(int , int);
int FindMAXDigit(void);
void InitializeQueue(void);
void Put(int,int);
int Get(int);


int main(void)
{
	InitializeQueue();
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	RadixSort(FindMAXDigit());
	puts("\n=======after========");
	DisplayBuffer();
}
void MakeRandomArray(void)
{
	int i = 0, index;
	int temp;
	srand((unsigned)time(NULL));
	while(i<MAXINDEX)
	{
		temp = rand() % MAX;
		if(!IsNumExit(i,temp))
		{
			Buffer[i] = temp;
			i++;
			//printf("%d->%d    ",i,Buffer[i-1]);
		}
	}
	
}
int IsNumExit(int index, int num)
{
	for(int i=0; i<index; i++)
	{
		if(Buffer[i]== num) return TRUE;
	}
	return FALSE;
}
void RadixSort(int MAXdigit)
{
	int num;
	int cnt = 0;
	for(int i=1; i<=MAXdigit; i++)
	{
		cnt = 0;
		for(int j=0; j<MAXINDEX; j++)
		{
			
			Put(FindDigit(Buffer[j],i),Buffer[j]);
			//index,num을 넣는다. index= Buf[j]의 i번째 수.
		}		
		printf("\nDigit%d :\n",i);
		for(int k=0;k<10; k++)
		{
			printf("\n%d: ",k);
			while(1)
			{
				num = Get(k);
				if(num == -1) break;
				else
				{
					printf("%3d ",num);
					Buffer[cnt++] = num;
				}
			}			
		}

		DisplayBuffer();
	}
}
void DisplayBuffer(void)
{
	for(int i=0; i<MAXINDEX; i++)
	{
		if(i%10 == 0) printf("\n");
		printf("%3d ",Buffer[i]);
	}
}
int FindDigit(int num, int digit)
{
	int n1 =1 ,n2 = 1;
	for(int i=0;i<digit;i++)
	{
		n1 *=10;
	}
	for(int i=0;i<digit-1;i++)
	{
		n2 *=10;
	}
	
	return (num % n1 / n2);
}
int FindMAXDigit(void)
{
	int n=1,digit = 1;
	for(int cnt = MAX;cnt>=10; cnt /=10) digit++;
	for(int i=0;i<digit-1;i++)
	{
		n *=10;
	}
	if(MAX-n == 0) return digit-1;
	return digit;
	
}
void InitializeQueue(void)
{
	int MAXdigit = FindMAXDigit();	
	for(int i=0; i<10; i++)
	{
		Front[i] = (NODE *)malloc(sizeof(NODE));
		Rear[i] = (NODE *)malloc(sizeof(NODE));
		
		Front[i]->Next = Rear[i];
		Rear[i]->Next = Rear[i];
	}
	
}
void Put(int index,int num)
{
	ptrNode = (NODE *)malloc(sizeof(NODE));
	
	ptrNode->Data = num;
	
	if(Front[index]->Next == Rear[index])
	{
		Front[index]->Next = ptrNode;
		ptrNode->Next = Rear[index];
		Rear[index]->Next = ptrNode;
	}
	else
	{
		Rear[index]->Next->Next = ptrNode;
		ptrNode->Next = Rear[index];
		Rear[index]->Next = ptrNode;
	}
}
int Get(int index)
{
	int ret;
	NODE *Deleteptr;
	
	if(Front[index]->Next == Rear[index]) return -1;
	else
	{
		Deleteptr = Front[index]->Next;
		ret =Deleteptr->Data;
		Front[index]->Next = Deleteptr->Next;
		
		free(Deleteptr);
	}
	return ret;
}
