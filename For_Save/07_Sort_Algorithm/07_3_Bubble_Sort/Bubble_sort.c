#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define TRUE 1
#define FALSE 0
int Buffer[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void BubbleSort(void);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	BubbleSort();
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
void BubbleSort(void)
{
	int dummy;
	int index;
	for(int i=MAX-1; i>=0; i--)
	{
		index = i;
		for(int j = 0; j<i; j++)
		{
			if(Buffer[j+1] < Buffer[j])
			{
				dummy = Buffer[j];
				Buffer[j] = Buffer[j+1];
				Buffer[j+1] = dummy;
			}
		}
		DisplayBuffer();
		
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