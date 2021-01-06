#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
	
	int Data;
	struct _NODE *Next;
	
}NODE;

NODE *head, *temp, *end;

void Initialize(void);
void InsertNode(int);
void DeleteNode(NODE *);
void PrintList(void);
void print_num(int);
void Initialize(void)
{
	NODE *ptr;
	head = (NODE *)malloc(sizeof(NODE));
	end = (NODE *)malloc(sizeof(NODE));
	head->Next = end;
	end->Next = end;
	/*
	temp1 = (NODE *)malloc(sizeof(NODE));
	head->Next = temp1;
	temp1->Next = end;
	end->Next = end;
	temp1->Data = 'A';
	ptr = temp1;
	
	temp2 = (NODE *)malloc(sizeof(NODE));
	ptr->Next= temp2;
	temp2->Data = 'B';
	temp2->Next = end;
	ptr = temp2;
	
	temp3 = (NODE *)malloc(sizeof(NODE));
	ptr->Next= temp3;
	temp3->Data = 'D';
	temp3->Next = end;
	ptr = temp3;
	
	temp4 = (NODE *)malloc(sizeof(NODE));
	ptr->Next= temp4;
	temp4->Data = 'E';
	temp4->Next = end;
	*/
}
void InsertNode(int n)
{
	NODE *Indexptr;
	NODE *NewNode;
	NewNode = (NODE *)malloc(sizeof(NODE));
	Indexptr = head;
	while(Indexptr->Next != end)
	{
		Indexptr = Indexptr->Next;
	}
	NewNode->Data = n;
	Indexptr->Next=NewNode;
	NewNode->Next = end;


}
void DeleteNode(NODE *ptr)
{
	NODE *Indexptr;
	NODE *Deleteptr;
	for(Indexptr = head; Indexptr != end; Indexptr = Indexptr->Next)
	{
		if(Indexptr->Next->Data == ptr->Data) 
		{
			Deleteptr = Indexptr->Next;
			break;
		}
	}		
	Indexptr->Next = Indexptr->Next->Next;
	free(Deleteptr);
	Deleteptr = NULL;
	ptr = NULL;
	
}
void PrintList(void)
{
	NODE *Indexptr;
	for(Indexptr = head; Indexptr != end; Indexptr = Indexptr->Next)
	{
		if((Indexptr != head) && (Indexptr != end))
		{	
			printf("%d->",Indexptr->Data);
			
		}
	}			
}

void print_num(int n)
{

	printf("%d",n);
}

void main()
{
	//<3, 6, 2, 7, 5, 1, 4>
	int num,cycle;
	int cnt = 0;
	Initialize();
	scanf("%d %d",&num, &cycle);
	
	num = 7;
	cycle = 3;
	for(int i=0;i < num; i++)
	{
		InsertNode(i+1);
	}
	printf("<");
	temp = head;
	while(head->Next != end)
	{
		temp = temp->Next;
		cnt++;
		if (cnt % cycle == 2)
		{
			print_num(temp->Next->Data);
			DeleteNode(temp->Next);
			cnt++;
			if (temp->Next = end) temp = head->Next;
			if (head->Next != end) printf(", ");
			
		}
	}
	
	printf(">");
}