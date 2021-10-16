//..............Moj hash...................................................................................
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "zadanie2.h"

struct data **hash_table = NULL;

unsigned long my_hash_operacie = 0;
int size_index = 0;
int free_size = 0;	// velkost volnych miest v tabulke
int capacity = 0;	// velkost hashovacej tabulky

long prime_num[MAX_SIZE];
char numbers[MAX_NUM];


// nacita prvocisla do pola
void load_prime() {
	int size, index = 0;

	memset(numbers, '1', MAX_NUM * sizeof(char));

	for (int i = 2; i * i <= MAX_NUM; i++) {
		if (numbers[i] == '1') {
			for (int j = i * i; j <= MAX_NUM; j += i) {
				numbers[j] = '0';
			}
		}
	}
	for (int i = 2; i <= MAX_NUM; i++) {
		if (numbers[i] == '1') {
			prime_num[index++] = i;
		}
	}
}

// vrati prvocislo, ktore nastavime na velkost tabulky
int get_prime(int num) {
	int size, index = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		my_hash_operacie++;
		if (prime_num[i] > (2 * num)) {
			size = prime_num[i];
			break;
		}
	}
	//printf("size %d\n", size);
	return size;
}


// funkcia, ktora vytvori hash pre dany kluc
int hash_function(int key) {
	//printf("%d mod %d = %d\n", key, capacity, key % capacity);
	my_hash_operacie++;
	return key % capacity;
}


// vytvori hashovaciu tabulku a nastavi jej prvky na NULL
void create_table(int table_size) {

	hash_table = (data *)malloc(table_size * sizeof(data));
	capacity = table_size;
	free_size = table_size;

	for (int i = 0; i < capacity; i++) {
		my_hash_operacie++;
		hash_table[i] = NULL;
	}
}


// zvacsi hashovaciu tabulku, nastavi nove prvky na NULL
void resize_table(int new_size) {
	int old_capacity = capacity;

	struct data **new_table = (data *)malloc(new_size * sizeof(data));

	capacity = new_size;
	free_size = new_size;

	for (int i = 0; i < capacity; i++) {
		my_hash_operacie++;
		new_table[i] = NULL;
	}
	for (int i = 0; i < old_capacity; i++) {
		if (hash_table[i] != NULL) {
			data *temp = hash_table[i];
			while (temp != NULL) {
				my_hash_operacie++;
				insert_item(hash_table[i]->value, hash_table[i]->value, new_table);
				if (temp->next == NULL) {
					break;
				}
				else {
					temp = temp->next;
				}
			}
		}
	}
	hash_table = new_table;
}


// vlozi prvok do tabulky
void insert_item(int value, int key, struct data **hash_table) {
	int index;

	index = hash_function(key);

	data *new = (data *)malloc(sizeof(data));
	new->key = key;
	new->value = value;
	new->next = NULL;

	if (hash_table[index] == NULL) {
		my_hash_operacie++;
		hash_table[index] = new;
		free_size--;
	}
	else if (hash_table[index] != NULL) {
		data *temp = hash_table[index];
		while (temp != NULL) {
			my_hash_operacie++;
			if (temp->next == NULL) {
				temp->next = new;
				break;
			}
			else {
				temp = temp->next;
			}
		}
		free_size--;
	}
}


// vyhlada prvok v tabulke
int search_item(int key) {
	int index;
	index = hash_function(key);

	if (hash_table[index] == NULL) {
		//printf("Prvok nenajdeny...\n");
		return 0;
	}

	if (hash_table[index]->key == key) {
		my_hash_operacie++;
		//printf("Prvok najdeny: %d\n", key);
		return 1;
	}
	else if (hash_table[index]->key != key) {
		data *temp = hash_table[index];
		while (temp != NULL) {
			my_hash_operacie++;
			//printf("Prechadzam cez %d...\n", temp->key);
			if (temp->key == key) {
				//printf("Prvok najdeny: %d\n", key);
				return 1;
			}
			temp = temp->next;
		}
		//printf("Prvok nenajdeny...\n");
	}
	else {
		//printf("Prvok nenajdeny...\n");
		return 0;
	}
}



//....................main....................................
void my_hash_main() {
	int prime, random, num, help = 0, min = 0, max = 0, min2;
	int *rand_arr;
	double runtime, fill_factor, n1, n2;
	char choice;
	clock_t time;

	printf("\nMoje hashovanie\n");
	printf("1 - search item\n2 - random vstup\n3 - postupnost vstup\n4 - quit\n");
	load_prime();
	
	while (1) {
		
		scanf("%c", &choice);	

		if (choice == '4')
			break;

		switch (choice) {
		case '1':
			if (max == 0) {
				time = clock();
				for (int i = 0; i < num; i++)
					search_item(min2++);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", my_hash_operacie);
				my_hash_operacie = 0;
			}
			else {
				time = clock();
				for (int i = 0; i < num; i++)
					search_item(rand_arr[i]);
				time = clock() - time;
				runtime = (double)(time) / CLOCKS_PER_SEC;
				printf("cas: %f\n", runtime);
				printf("Vykonane operacie: %lu\n", my_hash_operacie);
				my_hash_operacie = 0;
			}
			//printf("Zadaj hodnotu: ");
			//scanf("%d", &num);
			//search_item(num);
			break;
		case '3':
			printf("Zadaj pocet prvkov: ");
			scanf("%d", &num);
			if (hash_table == NULL) {
				prime = get_prime(num);
				create_table(prime);
			}
			//my_hash_operacie = 0;
			printf("Zadaj velkost prveho: ");
			scanf("%d", &min);
			min2 = min;
			time = clock();
			for (int i = 0; i < num; i++) {
				n1 = free_size;
				n2 = capacity;
				fill_factor = n1 / n2;
				if (fill_factor < 0.5) {
					resize_table(get_prime(capacity));
					//printf("Velkost zvacsena\n");
				}
				insert_item(min, min, hash_table);
				min++;
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", my_hash_operacie);
			my_hash_operacie = 0;
			break;
		case '2':
			printf("Zadaj pocet pridavanych prvkov: ");
			scanf("%d", &num);
			if (hash_table == NULL) {
				prime = get_prime(num);
				create_table(prime);
			}
			printf("Zadaj min velkost intervalu: ");
			scanf("%d", &min);
			printf("Zadaj max velkost intervalu: ");
			scanf("%d", &max);
			rand_arr = (int *)malloc(num * sizeof(int));
			for (int i = 0; i < num; i++) {
				random = (rand() % (max - min + 1)) + min;
				rand_arr[i] = random;
			}
			//my_hash_operacie = 0;
			time = clock();
			for (int i = 0; i < num; i++) {
				n1 = free_size;
				n2 = capacity;
				fill_factor = n1 / n2;
				//printf("%d %d %lf\n", free_size, capacity, fill_factor);
				if (fill_factor < 0.5) {
					resize_table(get_prime(capacity));
					//printf("Velkost zvacsena\n");
				}
				insert_item(rand_arr[i], rand_arr[i], hash_table);
			}
			time = clock() - time;
			runtime = (double)(time) / CLOCKS_PER_SEC;
			printf("cas: %f\n", runtime);
			printf("Vykonane operacie: %lu\n", my_hash_operacie);
			my_hash_operacie = 0;
			break;
		}
	}
	return;
}