static inline int find_successor(struct tree_node **node, int *key_idx, struct tree_node **parent, struct tree_node **successor, int *o_idx) //del
{
	int left_idx;
	int right_idx;
	int again;
	int key;
	struct tree_node *tmp_node;
	int i;

	do {
		//key_idx 대신에 i로 갖고놀다가(for문) 리턴하거같은건 key_idx로 다룬다.
		again = 0;
		left_idx = *key_idx;
		right_idx = left_idx + 1;
		key = (*node)->key[left_idx];

		*successor = *node;
		*o_idx = *key_idx;

		if (right_idx < 4 && (*node)->child[right_idx] != NULL) {
			//R_idx가 마지막이 아니고 오른쪽이 있으면 거기로 이동
			tmp_node = (*node)->child[right_idx];
			if (count_key(tmp_node) == 1) {
				struct tree_node *grown_node;
				
				grown_node = grow_node(*node, right_idx);
				//suc중에 grow가 발견되면 키워주고, suc을 다시 찾는다.
				if (grown_node == NULL) { 	//리프 노드이다.
					//
					printf("Exception\n");
					return -1;
				}

				if (grown_node == *node) {
					//노드의 자식들중에 한 곳에서 후임을 찾는데, 그 과정에서 grow를 시켰을 때
					//grow된 위치가 노드일때.
					//즉, 자기 자식을 grow했는데 자기랑 병합했을 때 이다. 자식의 좌or우형제가 2n이고, 부모도 2n일 때
					for (i = 0; i < count_key(grown_node); i++) { //
						if (grown_node->key[i] == key) {//여기도 가보기. 그로우가 일어났는데, 그자리에잇을때
							//즉 자기 아래 아래에서 일어났을때 
							//노드의 자식이 노드랑 병합했을 때, 즉 노드의 위치(KEY를 가지고 있는 지점)를 
							//특정할 수가 없게되어 컨티뉴해서 다시찾는다 ㅠㅠ
							*key_idx = i; //컨티뉴했을 때 특정짓기 위해 key_idx를 i로 ㅎ준다.
							again = 1;
							break;
						}
					}

					if (again == 1) continue;

					printf("Exception\n");
					return -1;
				}

				// if the grown node has a key, we have to restart this again from that node.
				for (i = 0; i < 3; i++) {
					if (grown_node->key[i] == key) {
						*key_idx = i;
						*parent = *node;
						*node = grown_node;
						again = 1;
						break;  
					}
				}
				if (again == 1) continue;

				tmp_node = grown_node;
				
			} // move to the right child node

			// find the smallest key which is larger than given key from the tree.
			//후임 찾기 시작.
			*parent = *node;
			*successor = tmp_node;
			*o_idx = 0; // 밑의 함수들에서 변경이 없을 경우 suc->k[o_i] == key임을 의미

			while ((*successor)->child[0] != NULL) {
				if (count_key((*successor)->child[0]) == 1) {
					tmp_node = grow_node(*successor, 0);
					if (tmp_node == *successor) { //현재의 후임의 자식이 후임이랑 병합했을 때, 즉 찐 후임의위치를 
													//특정할 수가 없게되어 컨티뉴해서 다시찾는다 ㅠㅠ
						continue;
					}
				}

				*parent = *successor;
				*successor = (*successor)->child[0];
			}
		}
		else if (left_idx >= 0 && (*node)->child[left_idx] != NULL) {
		//L_idx가 처음이 아니고 왼쪽이 있으면 거기로 이동 (뎁스가 1이 아니면 다 있지않나..?싶음ㅎ)

			tmp_node = (*node)->child[left_idx];

			if (count_key(tmp_node) == 1) {
				struct tree_node *grown_node;

				grown_node = grow_node(*node, left_idx);
				if (grown_node == NULL) {
					printf("Exception\n");
					return -1;
				}

				if (grown_node == *node) {
					int i;
					for (i = 0; i < count_key(grown_node); i++) {
						if (grown_node->key[i] == key) {
							*key_idx = i;
							again = 1;
							break;
						}
					}

					if (again == 1) continue;

					printf("Exception\n");
					return -1;
				}

				// if the grown node has a key, we have to restart this again from that node.
				for (i = 0; i < 3; i++) {
					if (grown_node->key[i] == key) {
						*key_idx = i;
						*parent = *node;
						*node = grown_node;
						again = 1;
						break;
					}
				}
				if (again == 1) continue;

				tmp_node = grown_node;
			}

			// find the smallest key from the tree.
			*parent = *node;
			*successor = tmp_node;
			*o_idx = count_key(*successor) - 1; // last_idx와 같은 개념

			while ((*successor)->child[(*o_idx) + 1] != NULL) {
				if (count_key((*successor)->child[(*o_idx) + 1]) == 1) {
					tmp_node = grow_node(*successor, (*o_idx) + 1);
					if (tmp_node == *successor) {
						*o_idx = count_key(*successor) - 1;
						continue;
					}
				}
				//for문돌려서 일일이 하는게 아니라  count해서 마지막것들에서만 후임을 찾는다.
				*parent = *successor;
				*successor = (*successor)->child[(*o_idx) + 1];
				*o_idx = count_key(*successor) - 1;
			}
		}
	} while (again); //again을 매개변수로 하여 do-while문이 작동한다.

	return 0;
}






int tree_remove(struct tree_node **root, int key)
{
	struct tree_node *iterator;
	struct tree_node *successor;
	struct tree_node *parent;
	struct tree_node *tmp_node;
	int o_i; //old_i 의 줄임말일듯?
	int i;

	parent = NULL;
	iterator = *root;
	while (iterator) {
		for (i = 0; i < 3; i++) {
			if (iterator->key[i] < 0) break; // 키가 차있을때만 아래로 간다.
			else if (key == iterator->key[i]) { // 키가 일치하경우 
				find_successor(&iterator, &i, &parent, &successor, &o_i);

				iterator->key[i] = successor->key[o_i];

				// Now remove the successor->key[o_i];
				if (count_key(successor) > 1) {
					shift_left(successor, o_i); // 이 함수로 제거.
					iterator = NULL;
					break;
				}
				else if (parent == NULL) {
					// Root node is deleted
					if (iterator != *root)
						printf("Exception");
					free(*root);
					*root = NULL;
					iterator = NULL;
					break;
				}
				else {
					int c_i; //child_i 

					for (c_i = 0; c_i < 4; c_i++) {
						if (parent->child[c_i] == successor) break;
					}	//parent가 suc의 부모임을 확인바람

					if (c_i == 4) {
						printf("Exception\n");
						return -1;
					}

					struct tree_node *tmp_node;

					// successor has only an item. successor must has to be grown up.
					tmp_node = grow_node(parent, c_i);
					if (tmp_node == parent) {
						//부모로 병합
						// If the successor is merged into the parent node,
						// we have to use the parent node as a successor.
						successor = parent;
						// also, we need to find an index of key again.
						for (i = 0; i < 3; i++) {
							if (successor->key[i] == key) break;
						}

						if (i == 3) {
							printf("Exception\n");
							return -1;
						}
					}

					// remove the key from the successor node.
					shift_left(successor, i); //i가 먼지 모르겟음 ㅋ
					iterator = NULL;
				}

				break;
			}
		}
		//모든 키가 일치하지않으므로 아래로 내려간다
		// If the iterator is null, the node what we want to delete is deleted.
		if (iterator == NULL) break;

		if (key < iterator->key[0]) { // key가 노드 사이에 있을 경우
			tmp_node = iterator->child[0];

			if (count_key(tmp_node) == 1) { // key가 가야할 노드가 1개의 키를 가질 때
				tmp_node = grow_node(iterator, 0); //grow(현재노드,c[n]에서의 n)
				if (tmp_node == iterator) {
					// Find the key from the interator again, it is grown up.
					continue;
				}
			}
			
			parent = iterator;
			iterator = tmp_node;
		}
		else if (iterator->key[1] < 0 || key < iterator->key[1]) {
			tmp_node = iterator->child[1];

			if (count_key(tmp_node) == 1) {
				tmp_node = grow_node(iterator, 1);
				if (tmp_node == iterator) {
					continue;
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
		else if (iterator->key[2] < 0 || key < iterator->key[2]) {
			tmp_node = iterator->child[2];

			if (count_key(tmp_node) == 1) {
				tmp_node = grow_node(iterator, 2);
				if (tmp_node == iterator) {	//이게 아닌상황은 무엇일까?
					continue;
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
		else {
			tmp_node = iterator->child[3];

			if (count_key(tmp_node) == 1) {
				tmp_node = grow_node(iterator, 3);
				if (tmp_node == iterator) {
					continue;
				}
			}
			parent = iterator;
			iterator = tmp_node;
		}
	}

	return 0;
}