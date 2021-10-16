#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "zadanie2.h"

#define TRUE 1
#define FALSE 0



int main() {
	char choice;	
	
	printf("1 - nevyvazeny binarny vyhladavaci strom\n");
	printf("2 - vyvazeny binarny vyhladavaci strom (AVL - moj)\n");
	printf("3 - vyvazeny binarny vyhladavaci strom (Red-black - prevzaty)\n");
	printf("4 - hashovanie (moje)\n");
	printf("5 - hashovanie (prevzate)\n");
	printf("6 - koniec\n");

	while (TRUE) {

		scanf("%c", &choice);
		switch (choice) {

		case '1':
			u_bin_tree_main();
			break;
		case '2':
			avl_tree_main();
			break;
		case '3':
			red_black_tree_main();
			break;
		case '4':
			my_hash_main();
			break;
		case '5':
			other_hash_main();
			break;
		case '6':
			exit(0);
		}
	}
	return 0;
}