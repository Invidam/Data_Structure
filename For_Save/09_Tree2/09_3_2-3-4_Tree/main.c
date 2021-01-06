//2-3-4 만들기!!
/*
삽입 과정은 2-3과 비슷하다

삭제 과정은 successor을 찾으러 가는 과정에서 depth를 줄이기 위해 병합되기에 2-3과 다르다.
1 4 5 9 8 6 12 13 10 2

insert는 다했고 10~100.

del도 간단해 보인다.
어려운건 grow고 나머지는 ㄱㅊ아보임 ㅎㅎ

삭제과정에서 예시를 들 때,
부모에서 가져오기
형제에서 가져오기
그밖(병합 이라는데 잘모르겟다)
루트 삭제

우형제가 2개있을 때 어떻게 할지를 보기 /햇음
+루트일때도 보기. 1o 2o / 했음
suc을 통한 grow도 해보기. // 했음

+successor활용도 한번해보기. /안했음.
한번만해보기 교체말고 딱히 하는 일이 없음
이게 더 쉽네 은근히 ㅇㅇ;

Q1. 전부다 2node이면 어떻게 되나? 병합해서 depth가 줄겠지 그 과정은 한번 해보기.
그럴 경우, 루트를 빌려주며 위에서부터 2node를 만회하며, 루트에서 뎁스가 줄어든다.
Q2. 이때 루트가 사라지는게 코드에 있나?

suc만드는거 계속하기. 후임찾기랑 else if도 하기 그리구 delete도 만들구 ...끗!!

*/




#include <stdio.h>
#include <stdlib.h>
#include "234tree.h"
/*
https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
- rb트리 구현 -
https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC#%EC%82%AD%EC%A0%9C(Removal)
- rb트리 위키백과(코드 참고용)-
https://coyagi.tistory.com/entry/c-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EB%A0%88%EB%93%9C%EB%B8%94%EB%9E%99-%ED%8A%B8%EB%A6%AC?category=613391
-rb c++-
https://ddmix.blogspot.com/2015/02/cppalgo-19-red-black-tree.html
-영상-
http://nlp.jbnu.ac.kr/DS/ch13.pdf
https://ferrante.tistory.com/46
https://zeddios.tistory.com/237

2-3-4 tree를 이진트리로 구현한게 rb트리이므ㅗ
2-3-4 tree를 먼저 공부한 후 공부할 것.

https://nicesj.com/article/calendar/3251
ㄴ 234 그 사람꺼임
https://www.cs.usfca.edu/~galles/visualization/BTree.html
*/


int main(void)
{
	NODE *root = NULL;
	int x;
	
	int arr[] = {30,10,40,60,70,80};
	for(int i=0; i<sizeof(arr)/sizeof(int); i++)
	{
		x = arr[i];
		printf("\n==Insert %d",x);
		InsertNode(&root,x);
		Level_Traverse(root);
	}
	for(int i=sizeof(arr)/sizeof(int); i>0; i--)
	{
		x = arr[i-1 ];
		printf("\n==Delete %d",x);
		DeleteNode(&root,x);
		Level_Traverse(root);
	}
	puts("");
	return 0;
}