//..............Vyvazeny binarny vyhladavaci strom (Red-Black - prevzaty)..................................
#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct __RBTNode
{
	struct __RBTNode* parent;
	struct __RBTNode* left;
	struct __RBTNode* right;

	enum { RED, BLACK } color;

	int key;
	void* data;

} RBTNode;

extern RBTNode* nil;
unsigned long operacie_rb = 0;

RBTNode*	RBT_CreateNode(int key, void* data);
RBTNode*	RBT_SearchNode(RBTNode* tree, int key);
void		RBT_InsertNode(RBTNode** tree, RBTNode* newnode);
void		RBT_InsertNodeHelper(RBTNode** tree, RBTNode* newnode);
void		RBT_RebuildAfterInsert(RBTNode** tree, RBTNode* newnode);
void		RBT_RotateLeft(RBTNode** root, RBTNode* parent);
void		RBT_RotateRight(RBTNode** root, RBTNode* parent);

#endif



RBTNode* RBT_CreateNode(int key, void* data)
{
	RBTNode* newnode = (RBTNode*)malloc(sizeof(RBTNode));
	newnode->parent = NULL;
	newnode->left = NULL;
	newnode->right = NULL;
	
	newnode->key = key;
	newnode->data = data;
	newnode->color = BLACK;

	operacie_rb++;
	return newnode;
}

void RBT_InitNil()
{
	nil = RBT_CreateNode(-1, NULL);
	nil->color = BLACK;
}

RBTNode* RBT_SearchNode(RBTNode* tree, int key)
{
	if (tree == nil) {
		operacie_rb++;
		return NULL;
	}

	if (tree->key > key) {
		operacie_rb++;
		//printf("Going left, curr value: %d\n", tree->key);
		return RBT_SearchNode(tree->left, key);
	}
	else if (tree->key < key) {
		operacie_rb++;
		//printf("Going right, curr value: %d\n", tree->key);
		return RBT_SearchNode(tree->right, key);
	}
	else {
		return tree;
	}
}

void RBT_InsertNode(RBTNode** tree, RBTNode* newnode)
{
	//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
	RBT_InsertNodeHelper(tree, newnode);
	//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);

	newnode->color = RED;
	newnode->left = nil;
	newnode->right = nil;

	//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
	RBT_RebuildAfterInsert(tree, newnode);
	//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
}

void RBT_InsertNodeHelper(RBTNode** tree, RBTNode* newnode)
{
	if ((*tree) == NULL)
		(*tree) = newnode;

	if ((*tree)->key < newnode->key)
	{
		operacie_rb++;
		//printf("viac\n");
		if ((*tree)->right == nil)
		{
			(*tree)->right = newnode;
			newnode->parent = (*tree);
		}
		else
			RBT_InsertNodeHelper(&(*tree)->right, newnode);

	}
	else if ((*tree)->key > newnode->key)
	{
		operacie_rb++;
		//printf("menej\n");
		if ((*tree)->left == nil)
		{
			(*tree)->left = newnode;
			newnode->parent = (*tree);
		}
		else
			RBT_InsertNodeHelper(&(*tree)->left, newnode);
	}
	/*else if ((*tree)->key == newnode->key) {
		return;
	}*/
}

void RBT_RotateRight(RBTNode** root, RBTNode* parent)
{
	RBTNode* leftchild = parent->left;

	parent->left = leftchild->right;

	if (leftchild->right != nil)
		leftchild->right->parent = parent;

	leftchild->parent = parent->parent;

	if (parent->parent == NULL)
		(*root) = leftchild;
	else
	{
		if (parent == parent->parent->left)
			parent->parent->left = leftchild;
		else
			parent->parent->right = leftchild;
	}

	leftchild->right = parent;
	parent->parent = leftchild;
}

void RBT_RotateLeft(RBTNode** root, RBTNode* parent)
{
	RBTNode* rightchild = parent->right;

	parent->right = rightchild->left;

	if (rightchild->left != nil)
		rightchild->left->parent = parent;

	rightchild->parent = parent->parent;

	if (parent->parent == NULL)
		(*root) = rightchild;
	else
	{
		if (parent == parent->parent->left)
			parent->parent->left = rightchild;
		else
			parent->parent->right = rightchild;
	}

	rightchild->left = parent;
	parent->parent = rightchild;
}

void RBT_RebuildAfterInsert(RBTNode** root, RBTNode* x)
{
	while (x != (*root) && x->parent != NULL && x->parent->color == RED)
	{
		if (x->parent == x->parent->parent->left)
		{
			RBTNode* Uncle = x->parent->parent->right;
			if (Uncle->color == RED)
			{
				x->parent->color = BLACK;
				Uncle->color = BLACK;
				x->parent->parent->color = RED;
				operacie_rb++;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					operacie_rb++;
					RBT_RotateLeft(root, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				operacie_rb++;
				RBT_RotateRight(root, x->parent->parent);
			}
		}
		else
		{
			//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
			RBTNode* Uncle = x->parent->parent->left;
			if (Uncle->color == RED)
			{
				//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
				x->parent->color = BLACK;
				Uncle->color = BLACK;
				x->parent->parent->color = RED;
				operacie_rb++;
				x = x->parent->parent;
			}
			else
			{
				//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
				if (x == x->parent->left)
				{
					//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);
					x = x->parent;
					operacie_rb++;
					RBT_RotateRight(root, x);
				}

				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				operacie_rb++;
				RBT_RotateLeft(root, x->parent->parent);
			}
		}
	}
	//printf("[DEBUG] %d:%s\n", __LINE__, __FUNCTION__);

	(*root)->color = BLACK;
}

RBTNode* nil;


void red_black_tree_main()
{
	int num, random, min = 0, max = 0, min2;
	int *rand_arr;
	double runtime;
	clock_t time;

	RBTNode* Tree = NULL;
	RBTNode* Node = NULL;

	nil = RBT_CreateNode(0, NULL);
	nil->color = BLACK;

	printf("\nRed-black tree\n");
	printf("1 - insert node\n2 - search node\n3 - random vstup\n4 - postupnost vstup\n5 - quit\n");


	while (1)
	{
		int  cmd = 0;
		int  param = 0;

		scanf("%d", &cmd);

		if (cmd == 5)
			break;

		switch (cmd)
		{
		case 1:
			printf("Enter parameter: ");
			scanf("%d", &param);
			RBT_InsertNode(&Tree, RBT_CreateNode(param, NULL));
			break;
		case 3:
			operacie_rb = 0;
			printf("Zadaj pocet prvkov v strome: ");
			scanf("%d", &num);
			printf("Zadaj min velkost intervalu: ");
			scanf("%d", &min);
			printf("Zadaj max velkost intervalu: ");
			scanf("%d", &max);
			rand_arr = (int *)malloc(num * sizeof(int));
			for (int i = 0; i < num; i++) {
				random = (rand() % (max - min + 1)) + min;
				rand_arr[i] = random;
			}
			time = clock();
			for (int i = 0; i < num; i++) {
				RBT_InsertNode(&Tree, RBT_CreateNode(rand_arr[i], NULL));
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_rb);
			break;
		case 4:
			operacie_rb = 0;
			printf("Zadaj pocet prvkov v strome: ");
			scanf("%d", &num);
			printf("Zadaj velkost prveho: ");
			scanf("%d", &min);
			min2 = min;
			time = clock();
			for (int i = 0; i < num; i++) {
				RBT_InsertNode(&Tree, RBT_CreateNode(min, NULL));
				min++;
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_rb);
			break;
		case 2:
			operacie_rb = 0;
			if (max == 0) {
				time = clock();
				for (int i = 0; i < num; i++)
					Node = RBT_SearchNode(Tree, min2++);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_rb);
			}
			else {
				time = clock();
				for (int i = 0; i < num; i++)
					Node = RBT_SearchNode(Tree, rand_arr[i]);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_rb);
			}
		}
		printf("\n");
	}
	return;
}