//..............Nevyvazeny binarny vyhladavaci strom.......................................................
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct u_bin_tree {
	int value;
	struct u_bin_tree *left;
	struct u_bin_tree *right;
} UNBALANCED_BIN_TREE;

unsigned long operacie_ubt = 0;

// funkcia na vkladanie prvkov do binarneho stromu
UNBALANCED_BIN_TREE *u_bin_tree_insert(struct u_bin_tree *to_add, int value_to_add) {

	// vytvorime node ak dosiahneme koniec vetvy stromu
	if (to_add == NULL) {
		operacie_ubt++;
		struct u_bin_tree *to_add = (struct u_bin_tree *)malloc(sizeof(UNBALANCED_BIN_TREE));
		to_add->value = value_to_add;
		to_add->left = NULL;
		to_add->right = NULL;
		return to_add;
	}
	// ak je pridavany prvok mensi, tak sa presunieme do lavej vetvy
	if (value_to_add < to_add->value) {
		operacie_ubt++;
		to_add->left = u_bin_tree_insert(to_add->left, value_to_add);
	}
	// ak je pridavany prvok vacsi, tak sa presunieme do pravej vetvy
	else {
		operacie_ubt++;
		to_add->right = u_bin_tree_insert(to_add->right, value_to_add);
	}
	return to_add;
}


// funkcia na vyhladavanie v binarnom strome
UNBALANCED_BIN_TREE *u_bin_tree_find(struct u_bin_tree *to_find, int value_to_find) {

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
		operacie_ubt++;
		//printf("Going left, curr value: %d\n", to_find->value);
		return  u_bin_tree_find(to_find->left, value_to_find);
	}
	// ak je hladany prvok vacsi, tak sa presunieme do pravej vetvy
	else {
		operacie_ubt++;
		//printf("Going right, curr value: %d\n", to_find->value);
		return u_bin_tree_find(to_find->right, value_to_find);
	}
}



//..................main............................................
void u_bin_tree_main() {
	int val, find, num, random, min = 0, max = 0, min2;
	int *rand_arr;
	char choice;
	double runtime;
	clock_t time;
	struct u_bin_tree *root = NULL, *item = NULL;

	printf("\nUnbalanced binary search tree\n");
	printf("1 - insert node\n2 - search node\n3 - random vstup\n4 - postupnost vstup\n5 - quit\n");

	while (1) {
		scanf("%c", &choice);

		if (choice == '5')
			break;

		switch (choice) {
		case '1':
			//printf("Zadaj hodnotu: ");
			scanf("%d", &val);
			root = u_bin_tree_insert(root, val);
			break;
		case '2':
			operacie_ubt = 0;
			if (max == 0) {
				time = clock();
				for (int i = 0; i < num; i++)
					item = u_bin_tree_find(root, min2++);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_ubt);
			}
			else {
				time = clock();
				for (int i = 0; i < num; i++)
					item = u_bin_tree_find(root, rand_arr[i]);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", operacie_ubt);
			}
			//printf("Zadaj hodnotu: ");
			//scanf("%d", &find);
			//item = u_bin_tree_find(root, find);
			break;
		case '4':
			operacie_ubt = 0;
			printf("Zadaj pocet prvkov v strome: ");
			scanf("%d", &num);
			printf("Zadaj velkost prveho: ");
			scanf("%d", &min);
			min2 = min;
			time = clock();
			for (int i = 0; i < num; i++) {
				//printf("%d ", i);
				root = u_bin_tree_insert(root, min);
				min++;
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_ubt);
			break;
		case '3':
			operacie_ubt = 0;
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
				root = u_bin_tree_insert(root, rand_arr[i]);
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", operacie_ubt);
			break;
		}
	}
	return;
}