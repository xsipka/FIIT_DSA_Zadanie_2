//..............Vyvazeny binarny vyhladavaci strom (AVL - moj).............................................
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct avl_tree {
	int value;
	int height;
	struct avl_tree *left;
	struct avl_tree *right;
} AVL_TREE;

unsigned long operacie_avl = 0;


// zisti vysku daneho podstromu
int get_height(struct avl_tree *node) {

	if (node == NULL) {
		return 0;
	}
	else {
		return node->height + 1;
	}
}


// porovnava vysku laveho a praveho podstromu a vrati vacsiu z nich
int max_height(int left, int right) {

	if (left > right) {
		return left;
	}
	else {
		return right;
	}
}



//....Funkcie na rotaciu..................................................
AVL_TREE *left_left_rotation(struct avl_tree *node) {
	struct avl_tree *x;
	struct avl_tree *y;
	int left_h, right_h;

	x = node->right;	// pravy prvok pod nevyvazenym prvkom
	y = x->left;	//	lavy podstrom predchadzajuceho prvku

	x->left = node;	// nasmerujeme koren nalavo od jeho praveho dietata
	node->right = y;	// lavy podstrom noveho korena nasmerujeme napravo od stareho korena

	//printf("Hodnoty: %d %d\n", node->value, x->value);
	//printf("%d %d\n", node->height, x->height);
	left_h = get_height(node->left);
	right_h = get_height(node->right);
	node->height = max_height(left_h, right_h);

	left_h = get_height(x->left);
	right_h = get_height(x->right);
	x->height = max_height(left_h, right_h);
	//printf("%d %d\n", node->height, x->height);

	return x;
}


AVL_TREE *right_right_rotation(struct avl_tree *node) {
	struct avl_tree *x;
	struct avl_tree *y;
	int left_h, right_h;

	x = node->left;
	y = x->right;

	x->right = node;
	node->left = y;

	//printf("Hodnoty: %d %d\n", node->value, x->value);
	//printf("%d %d\n", node->height, x->height);
	left_h = get_height(node->left);
	right_h = get_height(node->right);
	node->height = max_height(left_h, right_h);

	left_h = get_height(x->left);
	right_h = get_height(x->right);
	x->height = max_height(left_h, right_h);
	//printf("%d %d\n", node->height, x->height);

	return x;
}


AVL_TREE *left_right_rotation(struct avl_tree *node) {
	node->left = left_left_rotation(node->left);
	return right_right_rotation(node);
}


AVL_TREE *right_left_rotation(struct avl_tree *node) {
	node->right = right_right_rotation(node->right);
	return left_left_rotation(node);
}
//........................................................................


// pridavanie rovnake ako u nevyvazenych stromov, ale neskor treba spravit rotaciu
AVL_TREE *avl_tree_insert(struct avl_tree *node, int value_to_add) {
	int left_h, right_h;
	int balance_factor;

	// vytvorime node ak dosiahneme koniec vetvy stromu
	if (node == NULL) {
		operacie_avl++;
		struct avl_tree *to_add = (struct avl_tree *)malloc(sizeof(AVL_TREE));
		to_add->value = value_to_add;
		to_add->height = 0;
		to_add->left = NULL;
		to_add->right = NULL;
		return to_add;
	}
	// ak je pridavany prvok mensi, tak sa presunieme do lavej vetvy
	if (value_to_add < node->value) {
		operacie_avl++;
		node->left = avl_tree_insert(node->left, value_to_add);
	}
	// ak je pridavany prvok vacsi, tak sa presunieme do pravej vetvy
	else if (value_to_add > node->value) {
		operacie_avl++;
		node->right = avl_tree_insert(node->right, value_to_add);
	}
	// ak je pridavany prvok rovnaky, tak funkciu ukoncime
	else {
		return node;
	}


	//....Zistuje vacsiu z dvoch vysok..........................................
	left_h = get_height(node->left);
	right_h = get_height(node->right);
	node->height = max_height(left_h, right_h);
	operacie_avl++;
	balance_factor = left_h - right_h;
	//printf("%d - %d = %d\n", left_h, right_h, left_h - right_h);
	//printf("val: %d height: %d fact: %d\n", node->value, node->height, balance_factor);


	//....Podmienky rotacii.....................................................
	if ((balance_factor < -1) && (node->right->value < value_to_add)) {
		operacie_avl++;
		//printf("LL rotation\n");
		return left_left_rotation(node);
	}
	else if ((balance_factor > 1) && (node->left->value > value_to_add)) {
		operacie_avl++;
		//printf("RR rotation\n");
		return right_right_rotation(node);
	}
	else if ((balance_factor > 1) && (node->left->value < value_to_add)) {
		operacie_avl++;
		//printf("LR rotation\n");
		return left_right_rotation(node);
	}
	else if ((balance_factor < -1) && (node->right->value > value_to_add)) {
		operacie_avl++;
		//printf("RL rotation\n");
		return right_left_rotation(node);
	}
	else if (balance_factor >= -1 && balance_factor <= 1) {
		//printf("Strom je vyvazeny.\n");
	}
	return node;
}


// vyhladavanie rovnake ako pri nevyvazenych stromoch
AVL_TREE *avl_tree_find(struct avl_tree *to_find, int value_to_find) {

	// vrati NULL, ak sa prvok v strome nenachadza, inac vrati najdeny prvok
	if (to_find == NULL || to_find->value == value_to_find) {
		if (to_find == NULL);
			//printf("Prvok nenajdeny...\n");
		else;
			//printf("Prvok najdeny: %d\n", to_find->value);
		return to_find;
	}
	// ak je hladany prvok mensi, tak sa presunieme do lavej vetvy
	if (value_to_find < to_find->value) {
		operacie_avl++;
		//printf("Going left, curr value: %d\n", to_find->value);
		return  avl_tree_find(to_find->left, value_to_find);
	}
	// ak je hladany prvok vacsi, tak sa presunieme do pravej vetvy
	else {
		operacie_avl++;
		//printf("Going right, curr value: %d\n", to_find->value);
		return avl_tree_find(to_find->right, value_to_find);
	}
}


// testovacia funkcia, zistuje balance factor pre kazdy node
// ak je strom vyvazeny, tak vrati nulu, inac vrati pocet nevyvazenych prvkov
int avl_test(struct avl_tree *node, static int error) {
	int left_h, right_h, balance_factor;

	if (node == NULL)
		return;

	avl_test(node->left, error);

	left_h = get_height(node->left);
	right_h = get_height(node->right);
	balance_factor = left_h - right_h;

	if (balance_factor < -1 && balance_factor > 1) {
		error++;
	}

	avl_test(node->right, error);

	return error;
}


//..................main............................................
void avl_tree_main() {
	int val, f_val, num, random, min = 0, max = 0, min2;
	int *rand_arr;
	char choice;
	double runtime;
	clock_t time;
	struct avl_tree *root = NULL, *item = NULL;

	printf("\nAVL tree\n");
	printf("1 - insert node\n2 - search node\n3 - random vstup\n4 - test spravnosti\n5 - postupnost vstup\n6 - koniec\n");

	while (1) {
		scanf("%c", &choice);

		if (choice == '6')
			break;

		switch (choice) {
		case '1':
			//printf("Zadaj hodnotu: ");
			scanf("%d", &val);
			root = avl_tree_insert(root, val);
			break;
		case '2':
			operacie_avl = 0;
			//printf("Zadaj hodnotu: ");
			//scanf("%d", &f_val);
			if (max == 0) {
				time = clock();
				for (int i = 0; i < num; i++)
					item = avl_tree_find(root, min2++);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_avl);
			}
			else {
				time = clock();
				for (int i = 0; i < num; i++)
					item = avl_tree_find(root, rand_arr[i]);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_avl);
			}
			break;
		case '4':
			if (avl_test(root, 0) == 0) {
				printf("Vsetko OK.\n");
			}
			else {
				printf("Uf, zle... \n");
			}
			break;
		case '3':
			operacie_avl = 0;
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
				random = (rand() % (max - min + 1)) + min;
				root = avl_tree_insert(root, rand_arr[i]);
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_avl);
			break;
		case '5':
			operacie_avl = 0;
			printf("Zadaj pocet prvkov v strome: ");
			scanf("%d", &num);
			printf("Zadaj velkost prveho: ");
			scanf("%d", &min);
			min2 = min;
			time = clock();
			for (int i = 0; i < num; i++) {
				root = avl_tree_insert(root, min);
				min++;
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_avl);
			break;
		}
	}
	return;
}