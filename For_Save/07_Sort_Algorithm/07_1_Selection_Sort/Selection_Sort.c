#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
int Buffer[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void SelectionSort(void);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	SelectionSort();
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
void SelectionSort(void)
{
	int temp;
	int min;
	for(int i=0; i<MAX; i++)
	{
		min = i;
		for(int j=i; j<MAX; j++)
		{
			if(Buffer[j] < Buffer[min])
			{
				min = j;
			}
		}
		temp = Buffer[min];
		Buffer[min] = Buffer[i];
		Buffer[i] = temp;
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