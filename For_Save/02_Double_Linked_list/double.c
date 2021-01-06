#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE {
	char Data;
	struct _NODE *Prev;
	struct _NODE *Next;
}NODE;

NODE *head,*temp,*end;
NODE *temp1,*temp2,*temp3,*temp4;

void Initialize(void);
void InsertNode(NODE *);
void DeleteNode(NODE *);
void PrintList(void);

void Initialize(void)
{
	NODE *ptr;
	
	head = (NODE *)malloc(sizeof(NODE));
	end = (NODE *)malloc(sizeof(NODE));
	
	temp1 = (NODE *)malloc(sizeof(NODE));
	temp1->Data = 'A';
	temp1->Prev = head;
	temp1->Next = end;
	head->Next= temp1;
	end->Prev = temp1;
	ptr = temp1;
	
	temp2 = (NODE *)malloc(sizeof(NODE));
	temp2->Data = 'B';
	temp2->Prev = ptr;
	temp2->Next = end;
	end->Prev = temp2;
	ptr = temp2;
	
	temp3 = (NODE *)malloc(sizeof(NODE));
	temp3->Data = 'D';
	temp3->Prev = ptr;
	temp3->Next = end;
	end->Prev = temp3;
	ptr = temp2;
	
	temp4 = (NODE *)malloc(sizeof(NODE));
	temp4->Data = 'E';
	temp4->Prev = ptr;
	temp4->Next = end;
	end->Prev = temp4;
	ptr = temp4;
	
}
void InsertNode(NODE *ptr)
{
	NODE *IndexNode;
	
	for(IndexNode = head; IndexNode != end; IndexNode = IndexNode->Next)
	{
		if((IndexNode->Data < ptr->Data) && (IndexNode->Next->Data > ptr->Data)
		   {
			   break;
		   }
	}
	
	IndexNode->Next->Prev = ptr;
	ptr->Next = IndexNode->Next;
	IndexNode->Next = ptr;
	ptr->Prev = IndexNode;
		   
}
void DeleteNode(NODE *ptr)
{
	NODE *IndexNode;
	NODE *DeleteNode;
	
	for(IndexNode = head; IndexNode != end; IndexNode = IndexNode->Next)
	{
		if(IndexNode->Next->Data == ptr->Data)
		   {
			   DeleteNode = IndexNode->Next;
			   break;
		   }
	}
	
	IndexNode->Next = IndexNode->Next->Next;
	IndexNode->Next->Prev = IndexNode;
	free(DeleteNode);
				   
			   
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

int main(void)
{
	temp = (NODE *)malloc(sizeof(NODE));
	temp->Data = 'C';
	
	Initialize();
	
	printf("\nBefore Insert :");
	PrintList();
	
	InsertNode(temp);
	printf("\nAfter Insert :");
	PrintList();

	DeleteNodeNode(temp);
	printf("\nAfter Delete :");
	PrintList();
	
	
}
