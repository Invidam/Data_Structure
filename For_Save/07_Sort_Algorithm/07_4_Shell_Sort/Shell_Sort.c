#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TRUE 1
#define FALSE 0
int Buffer[MAX];
void MakeRandomArray(void);
int IsNumExit(int , int);
void ShellSort(void);
void DisplayBuffer(void);

int main(void)
{
	MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer();
	ShellSort();
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
void ShellSort(void)
{
	int i,j,v,h;
	for(int h=0; h<MAX; h = 3*h+1);
	for(;h>0;h /=3)
	{
		for(i=0;i<MAX;i++)
		{
			j=i;
			v=Buffer[i];
			while(j>=h && Buffer[j-h]>v)
			{
				Buffer[j] = Buffer[j-h]; 
				j -=h;
			}
			Buffer[j] = v;
		}
	}

}
void DisplayBuffer(void)
{
	for(int i=0; i<MAX; i++)
	{
		if(i%10 == 0) printf("\n!%d :",i/10);
		printf("%3d ",Buffer[i]);
	}
}