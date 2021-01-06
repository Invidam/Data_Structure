//https://www.cs.usfca.edu/~galles/visualization/BTree.html
//https://nicesj.com/article/calendar/3249

//노트 필기는 포기함, 그대신 주석 많이 달았고 a4용지로 끄적인거 참고하기.
#include <stdio.h>
#include <stdlib.h>
#include "23tree.h"



int main(void)
{
	NODE *root = NULL;
	int x;
	
	int arr[] = {30,10,40,60,70,80,20,50,15,45,75,7,17,27,37,47,57,67,77,87,18,28,48,58,78,88};
	for(int i=0; i<sizeof(arr)/sizeof(int); i++)
	{
		x = arr[i];
		printf("\n==Insert %d",x);
		InsertNode(&root,x);
		Level_Traverse(root);
	}
	for(int i=0; i<sizeof(arr)/sizeof(int); i++)
	{
		x = arr[sizeof(arr)/sizeof(int) - i -1 ];
		printf("\n==Delete %d",x);
		DeleteNode(&root,x);
		Level_Traverse(root);
	}
	puts("");
	return 0;
}

//main 23tree 23tree.h queue.c모두 같이 있어야 작동하며 src에 있어야 작동한다.
//delete만 마들기 솔직히 이해는 다했으니 만들기만 하면됨. 메인에서는 arr만들어서 쉽게 제거하기 ㅇㅋ?ㅇㅋ~