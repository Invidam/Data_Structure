static inline int count_key(struct tree_node *node) // I & D 
{
	if (node == NULL) return -1;
	return (node->key[0] >= 0) ? ((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1) : 0;
}

static inline void shift_right(struct tree_node *node, int key_idx) // I  & D 
{
	do {
		//  0,1,2
		// 0,1,2,3
		node->key[2] = -1;
		node->child[3] = NULL;

		if (key_idx == 2) break;

		node->key[2] = node->key[1];
		node->child[3] = node->child[2];

		if (key_idx == 1) break;

		node->key[1] = node->key[0];
		node->child[2] = node->child[1];

		node->child[1] = node->child[0];

		node->key[0] = -1;
		node->child[0] = NULL;
	} while (0);
}

static inline void shift_left(struct tree_node *node, int key_idx)
{
	//  0,1,2
	// 0,1,2,3
	switch (key_idx) {
	case 0:
		node->child[0] = node->child[1];
		node->key[0] = node->key[1];
	case 1:
		node->child[1] = node->child[2];
		node->key[1] = node->key[2];
	case 2:
		node->child[2] = node->child[3];
		node->key[2] = -1;
		node->child[3] = NULL;
		break;
	}
}

// returns moved key of the parent node
static inline struct tree_node *grow_node(struct tree_node *parent, int child_idx) // I & D
{
	/*
	grow는 succ을 찾는 과정에서 count가 1인 노드를 찾아 키워주는 함수이다.
	그 과정은 다음과 같다.
	1. 좌형제의 키가 2개 이상
	2. 우형제의 키가 2개 이상
	3. 좌형제의 키가 있긴 할 때
	4. 우형제의 키가 있긴 할 때
	1.2번 과정은 간단히 가져오면 되지만
	3,4번 과정은 힘들게 형제 부모와 병합해야한다.
	
	*/
	int last_idx;
	struct tree_node *grown_node = NULL;

	// count_key(parent->child[child_idx]) == 1

	// Try to get a key from the siblings
	if (child_idx - 1 >= 0 && (last_idx = count_key(parent->child[child_idx - 1])) >= 2) {
		// left to right
		//맨왼쪽이 아니고 왼쪽이 3n일 때
		//왼쪽이 3n이상일때
		shift_right(parent->child[child_idx], 0);

		parent->child[child_idx]->key[0] = parent->key[child_idx - 1];
		parent->key[child_idx - 1] = parent->child[child_idx - 1]->key[last_idx - 1];
		parent->child[child_idx]->child[0] = parent->child[child_idx - 1]->child[last_idx];

		parent->child[child_idx - 1]->key[last_idx - 1] = -1;
		parent->child[child_idx - 1]->child[last_idx] = NULL;

		grown_node = parent->child[child_idx];
	}
	else if (child_idx + 1 <= 3 && count_key(parent->child[child_idx + 1]) >= 2) {
		// right to left
		//오른쪽이 3n이상일때
		parent->child[child_idx]->key[1] = parent->key[child_idx];
		parent->key[child_idx] = parent->child[child_idx + 1]->key[0];
		parent->child[child_idx]->child[2] = parent->child[child_idx + 1]->child[0];

		shift_left(parent->child[child_idx + 1], 0);

		grown_node = parent->child[child_idx];
	}
	else if (child_idx - 1 >= 0 && parent->child[child_idx - 1] != NULL) {
		//왼쪽이 있긴할때
		//이걸 물어보는 이유는 병합할때 좌측을 할건지 우측으 할건지 정해야 하기 때문
		//대부분 좌측이 존재할텐데 ( 왜냐면 0,1,2의 key가 있기 때문)
		//k = 0일때에만 좌측은 없고 우측만 있을 것
		struct tree_node *left;
		struct tree_node *right;

		// merge left node, parent node, current node into single node (child_idx - 1)
		if (count_key(parent) == 1) { // 부모를 내린다. 나머지ㅡㄹ 올리는거지
			// use the parent node
			//      0        
			//  1       2   ==>  1,0,2    
			// a,b     c,d      a,b,c,d
			left = parent->child[child_idx - 1];
			right = parent->child[child_idx];

			parent->child[child_idx - 1] = NULL;
			parent->child[child_idx] = NULL;

			parent->key[1] = parent->key[0];
			parent->key[0] = -1;

			parent->key[0] = left->key[0];
			parent->child[0] = left->child[0];
			parent->child[1] = left->child[1];
			free(left);

			parent->key[2] = right->key[0];
			parent->child[2] = right->child[0];
			parent->child[3] = right->child[1];
			free(right);

			grown_node = parent;
		}
		else {//부모를 내리는데 뎁스는 그대로
			//     0,1               0   
			//  1   2   3   ==>  1       2,1,3
			// a,b c,d e,f      a,b     c,d,e,f
			left = parent->child[child_idx - 1];
			right = parent->child[child_idx];

			parent->child[child_idx] = left; // will be shifted

			left->key[1] = parent->key[child_idx - 1];
			parent->key[child_idx - 1] = -1;

			left->key[2] = right->key[0];
//2-3보다 간편해진 이유 저장공간이 많아져서 여러가지 상황을 고려하지 않고 쉬운 상황만 고려해도 병합이 가능함.
			//즉 늘어난 용량으로 인한 간단한 병합이 가능.
			left->child[2] = right->child[0];
			left->child[3] = right->child[1];

			free(right);

			shift_left(parent, child_idx - 1);

			grown_node = left;
		}
	}
	else if (child_idx + 1 <= 3 && parent->child[child_idx + 1] != NULL) {
		//노드의 맨왼쪽을 그로우 시킬때이다.
		struct tree_node *left;
		struct tree_node *right;

		if (count_key(parent) == 1) {
			left = parent->child[child_idx];
			right = parent->child[child_idx + 1];

			parent->key[1] = parent->key[0];
			//여기는왜 null이나 -1로 만드는게 없을까? 없어도 상관없는듯
			parent->key[0] = left->key[0];
			parent->child[0] = left->child[0];
			parent->child[1] = left->child[1];
			free(left);

			parent->key[2] = right->key[0];
			parent->child[2] = right->child[0];
			parent->child[3] = right->child[1];
			free(right);

			grown_node = parent;
		}
		else {
			left = parent->child[child_idx];
			right = parent->child[child_idx + 1];

			parent->child[child_idx + 1] = left; // will be shifted

			left->key[1] = parent->key[child_idx];
			left->key[2] = right->key[0];

			parent->key[child_idx] = -1;

			left->child[2] = right->child[0];
			left->child[3] = right->child[1];
			free(right);

			shift_left(parent, child_idx);

			grown_node = left;
		}
	}
	else {
		printf("Is this a leaf node?\n");
	}

	return grown_node;
}