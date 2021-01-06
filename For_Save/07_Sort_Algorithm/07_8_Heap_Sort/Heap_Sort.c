#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define MAX_INT 65536
#define MAX 100
#define MAXINDEX 10

int Buffer[MAX];
int Data[MAX] = {100,79,1,77,63,41,72,29,44,39};
void MakeRandomArray(void);
int IsNumExit(int , int);
void SelectionSort(void);
void DisplayBuffer(int []);
void HeapSort();
void Upheap(int);
void Downheap(int);
void InsertData(int);
int RemoveData(void);
int NUM;
int main(void)
{
	NUM = MAXINDEX;
	//MakeRandomArray();
	puts("\n=======before========");
	DisplayBuffer(Data);
	HeapSort();
	puts("\n=======after========");
	DisplayBuffer(Data);
}


void MakeRandomArray(void)
{
	int i = 0, index;
	int temp;
	Data[i++] = 100;
	srand((unsigned)time(NULL));
	while(i<MAXINDEX)
	{
		temp = rand() % MAX;
		if(!IsNumExit(i,temp))
		{
			Data[i] = temp;
			i++;
			//printf("%d->%d    ",i,Buffer[i-1]);
		}
	}
	
}
int IsNumExit(int index, int num)
{
	for(int i=0; i<index; i++)
	{
		if(Data[i]== num || num ==0 ) return TRUE;
	}
	return FALSE;
}
void DisplayBuffer(int arr[])
{
	for(int i=0; i<MAXINDEX*2; i++)
	{
		if(i%10 == 0) printf("\n%d :",i/10);
		printf("%3d ",arr[i]);
	}
}
void HeapSort(void)
{
	int i;
	for(i=0; i < MAXINDEX; i++)
	{
		InsertData(Data[i]);
		Data[0] = 1;
	}
	puts("\n=======Aft Insert Buf  ========");
	printf("NUM : %d",NUM);
	DisplayBuffer(Buffer);
	DisplayBuffer(Data);
	for (i = MAXINDEX -1; i >= 0; i--)
	{
		Data[i] = RemoveData();
		//printf("\n==AFT i = %d, ==\n",i);
		//DisplayBuffer(Data);
		//puts("");
	}
}
void Upheap(int k)
{
	int v,numb;
	numb = k;
	v= Buffer[k];
	Buffer[0] = MAX_INT;

	while(Buffer[k/2] <= v)
	{
		Buffer[k] = Buffer[k/2];
		k = k/2;
	}
	Buffer[k] = v;
	//printf("====aft insert Buf[%d] : %d",numb,v);
	//DisplayBuffer(Buffer);

}
void Downheap(int k)
{
	//k = 1 
	int i,v;
	v = Buffer[k];
	while(k <= NUM / 2)
	{
		i = 2 * k;
		printf("\nIn while, k : %d i : %d",k,i);
		if(i < NUM && Buffer[i] < Buffer[i+1])
		{
	
			i++;
			printf("\ni++\n i = %d",i);
		}
		if(v>= Buffer[i])
		{
			
			printf("\nbreak, v : %d i : %d Buffer[i] : %d",v,i,Buffer[i]);
			break;
		}
		printf("\nBuffer[%d] : %d Buffer[%d] : %d",k,Buffer[k],i,Buffer[i]);
		Buffer[k] = Buffer[i];
		k = i;
	}
	Buffer[k] = v;
	printf("\nk : %d i : %d ",k,i);
	DisplayBuffer(Buffer);
}
void InsertData(int v)
{	
	Buffer[++NUM] = v;
	//printf("\n\n\nBuf[%d] = %d = %d",NUM,Buffer[NUM],v);
	//DisplayBuffer(Buffer);
	//printf("\n->\n");
	Upheap(NUM);

}
int RemoveData(void)
{
	int v = Buffer[1];
	Buffer[1] = Buffer[NUM --];
	printf("\n\nNUM was : %d buf[1] : %d\n",NUM+1,Buffer[1]);
	Downheap(1);
	return v;
}