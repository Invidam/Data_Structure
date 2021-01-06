include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY 3
#define Buf_MAX 100
#define Hit_MAX 50

typedef struct _NODE
{
	int key[KEY]; //3
	int Counter;
}NODE;

NODE Hit[Hit_MAX];//50
int Buf[Buf_MAX];
void Initialize(void)
{
	int i;
	for(i=0; i<Buf_MAX; i++)
	{
		Buf[i] = -1;
	}
	for(i=0; i<Hit_MAX; i++)
	{
		for(int j=0; j<KEY; j++)
		{
			Hit[i].key[j] = -1;
		}
		Hit[i].Counter = 0;
	}
}
void MakeRandomNumber_overlapped(void)
{
	int i=0, num, index;
	srand((unsigned)time(NULL));
	while(i < 50)
	{
		num = rand() % 100;
		Buf[num]= num;
		index = num % 50;
		if(Hit[index].Counter >= 3) 
			printf("\nOverFlow");
		else
			Hit[index].key[Hit[index].Counter++] = num;
		i++;
	}
}
int IsNumberExit(int number)
{
	return (Buf[number] == number);
}
void MakeRandomNumber_non_overlapped(void)
{
	int i=0, num, index;
	srand((unsigned)time(NULL));
	while(i < 50)
	{
		num = rand() % 100;
		if(!IsNumberExit(num))
		{
			Buf[num]= num;
			index = num % 50;
			if(Hit[index].Counter >= 3) 
				printf("\nOverFlow");
			else
				Hit[index].key[Hit[index].Counter++] = num;
			i++;
		}
	}
}
void DisplayBuffer(void)
{
	int i;
	for(i=0; i<Buf_MAX; i++)
	{
		if(i % 10 == 0) puts("");
		printf("%3d",Buf[i]);
	}
}
void DisplayHitBuffer(void)
{
	int i;
	for(i=0; i<Hit_MAX; i++)
	{
		if(i % 5 == 0) puts("");
		switch(Hit[i].Counter)
		{
			case 0:
				
			case 1:
				printf("%10d",Hit[i].key[0]);
				break;
			case 2:
				printf("(%4d,%4d)",Hit[i].key[0],Hit[i].key[1]);
				break;
			case 3:
				printf("(%2d,%2d,%2d)",Hit[i].key[0],Hit[i].key[1],Hit[i].key[2]);
				break;
		}
		if(i % 5 -1 != 0)printf(",");
	}
	
}
void DisplayHitCounter(void)
{
	int sum = 0;
	for(int i=0; i<Hit_MAX; i++)
	{
		if(i % 5 == 0) puts("");
		printf("%2d",Hit[i].Counter);
		sum += Hit[i].Counter;
		if(Hit[i].Counter >= 10) printf("sum: %d",sum); 

	}	
}

void main(void)
{

	printf("\n=======Initialize======\n");
	Initialize();
	MakeRandomNumber_non_overlapped();
	printf("\n=======DisplayBuffer======\n");
	DisplayBuffer();

	
	printf("\n=======DisplayHitBuffer======\n");
	DisplayHitBuffer();
	printf("\n=======DisplayHitCounterr======\n");

	DisplayHitCounter();	
	puts("");
}