
#include <stdio.h>
#include <stdlib.h>
#include "RBtree.h"
/*
https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
- rb트리 구현 -

https://ferrante.tistory.com/46%20
https://www.youtube.com/watch?v=gF20ZSplxZE&list=PL52K_8WQO5oUuH06MLOrah4h05TZ4n38l&index=25&t=0s%20
https://en.wikipedia.org/wiki/Red%E2%80%93black_tree





https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC#%EC%82%AD%EC%A0%9C(Removal)
- rb트리 위키백과(코드 참고용)-
https://coyagi.tistory.com/entry/c-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EB%A0%88%EB%93%9C%EB%B8%94%EB%9E%99-%ED%8A%B8%EB%A6%AC?category=613391
-rb c++-
https://ddmix.blogspot.com/2015/02/cppalgo-19-red-black-tree.html
-영상-
http://nlp.jbnu.ac.kr/DS/ch13.pdf
https://ferrante.tistory.com/46
https://zeddios.tistory.com/237
*/


int main(void)
{
	NODE *root = NULL;
	int x;
	printf("0 : RED , 1 : BLACK");
	int arr[] = {30,40,10,20,5,3,2,17,43,84,53,11,44,22,33,66,77};
	/*
	Insert
	30		case1
	40,10	case2
	20		case3
	2		case4
	
	*/
	for(int i=0; i<sizeof(arr)/sizeof(int); i++)
	{
		x = arr[i];
		printf("\n==Insert %d",x);
		root = InsertNode(root,x);
		Level_Traverse(root);
	}
	printf("\n0 : RED , 1 : BLACK");
	for(int i=sizeof(arr)/sizeof(int); i>0; i--)
	{
		x = arr[i-1 ];
		printf("\n==Delete %d",x);
		root = DeleteNode(root,x);
		Level_Traverse(root);
	}
	puts("");
	return 0;
}