#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
int Buffer[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void QuickSort(int *data, int, int);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	QuickSort(Buffer,0,MAX-1);
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
void QuickSort(int *data, int Left, int Right)
{
	int i,j,temp,num;
	if(Right > Left)
	{
		i = Left-1;
		j = Right;
		num = data[Right];
		while(1)
		{
			while(data[++i] < data[Right]);
				while(data[--j] > data[Right]);
					if(i >= j) break;
			temp = data[i];
			data[i] = data[j];
			data[j] = temp;	
		}
		temp = data[i];
		data[i] = data[Right];
		data[Right] = temp;

		QuickSort(data,Left,i-1);
		QuickSort(data,i+1,Right);
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