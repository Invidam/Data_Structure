#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "234Tree.h"
#include "Common.h"

struct tree_node {
	struct tree_node *child[4];
	int key[3];
};


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

static inline int count_key(struct tree_node *node) // I & D 
{
	if (node == NULL) return -1;
	return (node->key[0] >= 0) ? ((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1) : 0;
	//((node->key[2] >= 0) ? 3 : 2) 에서, key2가 있으면 3 없으면 2가 저장. 이를 x1이라고 한다.
	//((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1)에서, key1가 있으면  x1, 없으면 1을 저장 (x2)
	//(node->key[0] >= 0) ? ((node->key[1] >= 0) ? ((node->key[2] >= 0) ? 3 : 2) : 1) : 0;
	//에서 key0ㅇ 있으면 x2, 없으면 0을 저장.
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
	int last_idx;
	struct tree_node *grown_node = NULL;

	// count_key(parent->child[child_idx]) == 1

	// Try to get a key from the siblings
	if (child_idx - 1 >= 0 && (last_idx = count_key(parent->child[child_idx - 1])) >= 2) {
		// left to right
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
		parent->child[child_idx]->key[1] = parent->key[child_idx];
		parent->key[child_idx] = parent->child[child_idx + 1]->key[0];
		parent->child[child_idx]->child[2] = parent->child[child_idx + 1]->child[0];

		shift_left(parent->child[child_idx + 1], 0);

		grown_node = parent->child[child_idx];
	}
	else if (child_idx - 1 >= 0 && parent->child[child_idx - 1] != NULL) {
		struct tree_node *left;
		struct tree_node *right;

		// merge left node, parent node, current node into single node (child_idx - 1)
		if (count_key(parent) == 1) {
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
		else {
			//     0,1               0   
			//  1   2   3   ==>  1       2,1,3
			// a,b c,d e,f      a,b     c,d,e,f
			left = parent->child[child_idx - 1];
			right = parent->child[child_idx];

			parent->child[child_idx] = left; // will be shifted

			left->key[1] = parent->key[child_idx - 1];
			parent->key[child_idx - 1] = -1;

			left->key[2] = right->key[0];

			left->child[2] = right->child[0];
			left->child[3] = right->child[1];

			free(right);

			shift_left(parent, child_idx - 1);

			grown_node = left;
		}
	}
	else if (child_idx + 1 <= 3 && parent->child[child_idx + 1] != NULL) {
		struct tree_node *left;
		struct tree_node *right;

		if (count_key(parent) == 1) {
			left = parent->child[child_idx];
			right = parent->child[child_idx + 1];

			parent->key[1] = parent->key[0];
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

static inline void split_node(struct tree_node *parent, int key_idx, struct tree_node *node) // insert
{
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
	}
	else {
		// Find the proper position in the parent node by sorting the keys.
		shift_right(parent, key_idx);

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

	if (count_key(iterator) == 3)
		split_node(NULL, -1, iterator);

	while (iterator) {
		if (key == iterator->key[0] || key == iterator->key[1] || key == iterator->key[2]) return -1;
		
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
	}

	return 0;
}
static inline void swap(int *a,int *b)
{
	int *tmp;
	&tmp = &a;
	&a = &b;
	&b = &tmp;
}


// During finding a successor,
// current "node" can be changed because of growing node operation.
// @return parent node of the successor
static inline int find_successor(struct tree_node **node, int *key_idx, struct tree_node **parent, struct tree_node **successor, int *o_idx) //del
{
	int left_idx;
	int right_idx;
	int again;
	int key;
	struct tree_node *tmp_node;
	int i;

	do {
		again = 0;
		left_idx = *key_idx;
		right_idx = left_idx + 1;
		key = (*node)->key[left_idx];

		*successor = *node;
		*o_idx = *key_idx;

		if (right_idx < 4 && (*node)->child[right_idx] != NULL) {
			tmp_node = (*node)->child[right_idx];

			if (count_key(tmp_node) == 1) {
				struct tree_node *grown_node;
				
				grown_node = grow_node(*node, right_idx);
				if (grown_node == NULL) {
					printf("Exception\n");
					return -1;
				}

				if (grown_node == *node) {
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
			} // move to the right child node

			// find the smallest key which is larger than given key from the tree.
			*parent = *node;
			*successor = tmp_node;
			*o_idx = 0;

			while ((*successor)->child[0] != NULL) {
				if (count_key((*successor)->child[0]) == 1) {
					tmp_node = grow_node(*successor, 0);
					if (tmp_node == *successor) {
						continue;
					}
				}

				*parent = *successor;
				*successor = (*successor)->child[0];
			}
		}
		else if (left_idx >= 0 && (*node)->child[left_idx] != NULL) {
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
			*o_idx = count_key(*successor) - 1;

			while ((*successor)->child[(*o_idx) + 1] != NULL) {
				if (count_key((*successor)->child[(*o_idx) + 1]) == 1) {
					tmp_node = grow_node(*successor, (*o_idx) + 1);
					if (tmp_node == *successor) {
						*o_idx = count_key(*successor) - 1;
						continue;
					}
				}

				*parent = *successor;
				*successor = (*successor)->child[(*o_idx) + 1];
				*o_idx = count_key(*successor) - 1;
			}
		}
	} while (again);

	return 0;
}

int tree_remove(struct tree_node **root, int key)
{
	struct tree_node *iterator;
	struct tree_node *successor;
	struct tree_node *parent;
	struct tree_node *tmp_node;
	int o_i;
	int i;

	parent = NULL;
	iterator = *root;
	while (iterator) {
		for (i = 0; i < 3; i++) {
			if (iterator->key[i] < 0) break;
			else if (key == iterator->key[i]) {
				find_successor(&iterator, &i, &parent, &successor, &o_i);

				iterator->key[i] = successor->key[o_i];

				// Now remove the successor->key[o_i];
				if (count_key(successor) > 1) {
					shift_left(successor, o_i);
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
					int c_i;

					for (c_i = 0; c_i < 4; c_i++) {
						if (parent->child[c_i] == successor) break;
					}

					if (c_i == 4) {
						printf("Exception\n");
						return -1;
					}

					struct tree_node *tmp_node;

					// successor has only an item. successor must has to be grown up.
					tmp_node = grow_node(parent, c_i);
					if (tmp_node == parent) {
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
					shift_left(successor, i);
					iterator = NULL;
				}

				break;
			}
		}

		// If the iterator is null, the node what we want to delete is deleted.
		if (iterator == NULL) break;

		if (key < iterator->key[0]) {
			tmp_node = iterator->child[0];

			if (count_key(tmp_node) == 1) {
				tmp_node = grow_node(iterator, 0);
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
				if (tmp_node == iterator) {
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


struct tree_node *tree_search(struct tree_node *root, int key)
{
	struct tree_node *iterator;

	iterator = root;
	while (iterator) {
		if (key < iterator->key[0]) {
			iterator = iterator->child[0];
		}
		else if (iterator->key[0] == key) {
			break;
		}
		else if (iterator->key[1] < 0 || key < iterator->key[1]) {
			iterator = iterator->child[1];
		}
		else if (iterator->key[1] == key) {
			break;
		}
		else if (iterator->key[2] < 0 || key < iterator->key[2]) {
			iterator = iterator->child[2];
		}
		else if (iterator->key[2] == key) {
			break;
		}
		else {
			iterator = iterator->child[3];
		}
	}

	return iterator;
}
