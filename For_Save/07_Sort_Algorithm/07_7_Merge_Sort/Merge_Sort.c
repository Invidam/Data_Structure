#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
#define MAXINDEX 10

int Buffer[MAX];
int temp[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void MergeSort(int data[], int Left, int Right);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	MergeSort(Buffer,0,MAXINDEX-1);
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
void MergeSort(int data[], int Left, int Right)
{
	int i,j,k,Middle;
	if(Left < Right)
	{	
		Middle = (Right + Left ) / 2;
		MergeSort(data,Left,Middle);
		MergeSort(data,Middle +1,Right);
		for(i = Middle+1; i > Left; i--)
		{
			temp[i-1] = data[i-1];	
		}
		for(j = Middle; j < Right; j++)
		{
			temp[Right + Middle -j] = data[j+1];
		}
		for(k = Left; k <= Right; k++)
		{
			data[k] = (temp[i] < temp[j]) ? temp[i++]:temp[j--] ;
		}
	}
}
void DisplayBuffer(void)
{
	for(int i=0; i<MAXINDEX; i++)
	{
		if(i%10 == 0) printf("\n%d :",i/10);
		printf("%3d ",Buffer[i]);
	}
}