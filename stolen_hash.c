// Zdroj prevzateho kodu...................................................................................
//https://www.tutorialspoint.com/data_structures_algorithms/hash_table_program_in_c.htm


//..............Prevzaty hash..............................................................................
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define SIZE 250


struct DataItem {
	int data;
	int key;
};


struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

unsigned long hash_operacie = 0;


int hashCode(int key) {
	hash_operacie++;
	return key % SIZE;
}


struct DataItem *search(int key) {
	//get the hash 
	int hashIndex = hashCode(key);

	//move in array until an empty 
	while (hashArray[hashIndex] != NULL) {
		hash_operacie++;
		if (hashArray[hashIndex]->key == key) {
			//printf("value: %d\n", hashArray[hashIndex]->key);
			return hashArray[hashIndex];
		}

		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
	}

	return NULL;
}


void insert(int key, int data) {

	struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
	item->data = data;
	item->key = key;

	//get the hash 
	int hashIndex = hashCode(key);
	
	//move in array until an empty or deleted cell
	while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
		//printf("1. index: %d %d %d\n", hashIndex, hashArray[hashIndex]->key, key);
		hash_operacie++;
		//go to next cell
		++hashIndex;

		//wrap around the table
		hashIndex %= SIZE;
		//printf("2. index: %d %d\n", hashIndex, key);
	}

	hashArray[hashIndex] = item;
}


void other_hash_main() {
	dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
	dummyItem->data = -1;
	dummyItem->key = -1;

	int random, num, help = 0, min = 0, max = 0, min2;
	int *rand_arr;
	double runtime;
	char choice;
	clock_t time;
	

	printf("\nPrevzate hashovanie\n");
	printf("1 - search item\n2 - random vstup\n3 - postupnost vstup\n4 - quit\n");

	while (1) {
		scanf("%c", &choice);
		
		if (choice == '4')
			break;

		switch (choice) {
		case '5':
			scanf("%d", &num);
			insert(num, num);
			break;
		case '1':
			hash_operacie = 0;
			if (max == 0) {
				time = clock();
				for (int i = 0; i < num; i++)
					item = search(min2++);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", hash_operacie);
			}
			else {
				time = clock();
				for (int i = 0; i < num; i++)
					item = search(rand_arr[i]);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", hash_operacie);
			}
			//printf("Zadaj hodnotu: ");
			//scanf("%d", &num);
			//item = search(num);
			break;
		case '3':
			hash_operacie = 0;
			printf("Zadaj pocet prvkov: ");
			scanf("%d", &num);
			printf("Zadaj velkost prveho: ");
			scanf("%d", &min);
			min2 = min;
			time = clock();
			for (int i = 0; i < num; i++) {
				insert(min, min);
				min++;
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", hash_operacie);
			break;
		case '2':
			hash_operacie = 0;
			printf("Zadaj pocet pridavanych prvkov: ");
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
				insert(rand_arr[i], rand_arr[i]);
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", hash_operacie);
			break;
		}
	}
	return;
}