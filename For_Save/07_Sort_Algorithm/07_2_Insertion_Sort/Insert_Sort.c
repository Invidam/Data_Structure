#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
int Buffer[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void InsertionSort(void);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	InsertionSort();
	puts("\n=======after========");
	DisplayBuffer();
	
}


void MakeRandomArray(void)
{
	int i = 0, index;
	int temp;
	srand((unsigned)time(NULL));
	while(i<MAX)
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
void InsertionSort(void)
{
	int dummy,j;
	for(int i=0; i<MAX; i++)
	{
		dummy = Buffer[i];
		j=i;
		while(Buffer[j-1] > dummy)
		{
			Buffer[j] = Buffer[j-1];
			j--;
		}
		Buffer[j] = dummy;
	}
}
void DisplayBuffer(void)
{
	for(int i=0; i<MAX; i++)
	{
		if(i%10 == 0) printf("\n%d :",i/10);
		printf("%3d ",Buffer[i]);
	}
}