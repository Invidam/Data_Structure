struct tree_node *node_create(int key0, int key1, int key2)
{
	struct tree_node *node;

	node = malloc(sizeof(*node));
	if (!node) return NULL;

	node->child[0] = NULL;
	node->child[1] = NULL;
	node->child[2] = NULL;
	node->child[3] = NULL;

	node->key[0] = key0;
	node->key[1] = key1;
	node->key[2] = key2;

	return node;
}
static inline void split_node(struct tree_node *parent, int key_idx, struct tree_node *node) // insert
{ // idx= n, k[n]과 c[n+1]을 shift를 통해 비워준다. 그후 그자리에 스플릿을 한다.
	struct tree_node *right;

	right = node_create(node->key[2], -1, -1);
	right->child[0] = node->child[2];
	right->child[1] = node->child[3];

	// 0 , 1, 2
	if (parent == NULL) {
		struct tree_node *left;

		left = node_create(node->key[0], -1, -1);
		left->child[0] = node->child[0];
		left->child[1] = node->child[1];

		node->child[0] = left;
		node->child[1] = right;

		node->key[0] = node->key[1];
		//삽입을 통해 레벨이 증가한다면, c[0,1]은 L가, c[2,3]은 R이 가져가며, k[1]이 부모가 된다.
	}
	else {
		// Find the proper position in the parent node by sorting the keys.
		shift_right(parent, key_idx);
		//idx부터 우측이동 ex) idx =n,  k[n],c[n+1]부터 우측이동시킴. 
		parent->key[key_idx] = node->key[1];
		parent->child[key_idx + 1] = right;
		parent->child[key_idx] = node;
	}

	node->key[1] = -1;
	node->key[2] = -1;
	node->child[2] = NULL;
	node->child[3] = NULL;
}
int tree_insert(struct tree_node **root, int key)
{
	struct tree_node *iterator;
	struct tree_node *leaf = NULL;

	if (*root == NULL) {
		*root = node_create(key, -1, -1);
		return 0;
	}

	iterator = *root;

	if (count_key(iterator) == 3) // 3개 다 차있으면 스플릿한다.
		split_node(NULL, -1, iterator);

	while (iterator) { //3개다 차있지 않은 경우, 밑으로 갈수도 있고 옆으로 갈 수도 있다.
		if (key == iterator->key[0] || key == iterator->key[1] || key == iterator->key[2]) return -1;
		//있는거면 종료
		if (key < iterator->key[0]) {
			if (count_key(iterator->child[0]) == 3) {
				split_node(iterator, 0, iterator->child[0]);
				continue;
			}

			leaf = iterator;
			iterator = iterator->child[0];
		}
		else if (iterator->key[1] < 0 || key < iterator->key[1]) {
			if (count_key(iterator->child[1]) == 3) {
				split_node(iterator, 1, iterator->child[1]);
				//P->k[idx]를 우측이동시켜, 스플릿시에 그 공간에 child's key가 들어가게 한다.
				//모든 idx에 대해 마찬가지.
				continue;
			}

			leaf = iterator;
			iterator = iterator->child[1];
		}
		else if (iterator->key[2] < 0 || key < iterator->key[2]) {
			if (count_key(iterator->child[2]) == 3) {
				split_node(iterator, 2, iterator->child[2]);
				continue;
			}

			leaf = iterator;
			iterator = iterator->child[2];
		}
		else {
			if (count_key(iterator->child[3]) == 3) {
				// @note
				// iterator is 4-node and child is also 4-node?
				// This case cannot be exist in 2-3-4 tree.
				split_node(iterator, 3, iterator->child[3]);
				continue;
			}

			leaf = iterator;
			iterator = iterator->child[3];
		}
	}

	if (leaf == NULL) return -1;

	int i;
	int tmp = key;

	// insertion sort
	for (i = 0; i < 3 && tmp >= 0; i++) {
		if (leaf->key[i] < 0 || leaf->key[i] > tmp) swap(leaf->key + i, &tmp);
	} // 65의 경우 두번스왑해서 (i=0, i =1일때 ) 65,70이 저장된다.
	//while문이 종료되었을 때의 최좋leaf가 진짜 leaf고 it는 리프의 자식을 가르킨다.

	return 0;
}
