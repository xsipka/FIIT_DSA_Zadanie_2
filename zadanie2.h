//.....UBS tree............................................................
typedef struct u_bin_tree {
	int value;
	struct u_bin_tree *left;
	struct u_bin_tree *right;
} UNBALANCED_BIN_TREE;

void u_bin_tree_main();
UNBALANCED_BIN_TREE *u_bin_tree_insert(struct u_bin_tree *to_add, int value_to_add);
UNBALANCED_BIN_TREE *u_bin_tree_find(struct u_bin_tree *to_find, int value_to_find);


//.....AVL tree............................................................
typedef struct avl_tree {
	int value;
	int height;
	struct avl_tree *left;
	struct avl_tree *right;
} AVL_TREE;

void		avl_tree_main();
int			avl_test(struct avl_tree *node, static int error);
AVL_TREE	*avl_tree_find(struct avl_tree *to_find, int value_to_find);
AVL_TREE	*avl_tree_insert(struct avl_tree *node, int value_to_add);
AVL_TREE	*right_right_rotation(struct avl_tree *node);
AVL_TREE	*left_left_rotation(struct avl_tree *node);
AVL_TREE	*left_right_rotation(struct avl_tree *node);
AVL_TREE	*right_left_rotation(struct avl_tree *node);
int			max_height(int left, int right);
int			get_height(struct avl_tree *node);


//.....Red-black tree......................................................
#ifndef _RBTREE_H_
#define _RBTREE_H_

typedef struct __RBTNode
{
	struct __RBTNode* parent;
	struct __RBTNode* left;
	struct __RBTNode* right;
	enum { RED, BLACK } color;
	int key;
	void* data;
} RBTNode;

RBTNode*	RBT_CreateNode(int key, void* data);
RBTNode*	RBT_SearchNode(RBTNode* tree, int key);
void		red_black_tree_main();
void		RBT_InsertNode(RBTNode** tree, RBTNode* newnode);
void		RBT_InsertNodeHelper(RBTNode** tree, RBTNode* newnode);
void		RBT_RebuildAfterInsert(RBTNode** tree, RBTNode* newnode);
void		RBT_RotateLeft(RBTNode** root, RBTNode* parent);
void		RBT_RotateRight(RBTNode** root, RBTNode* parent);

#endif


//.....My hash.............................................................
typedef struct data {
	int value;
	int key;
	struct data *next;
} data;

#define MAX_NUM 1299710	
#define MAX_SIZE 100000	

void	my_hash_main();
void	load_prime();
int		get_prime(int num);
int		hash_function(int key);
void	create_table(int table_size);
void	resize_table(int new_size);
int		search_item(int key);
void	insert_item(int value, int key, struct data **hash_table);


//.....Other hash..........................................................
struct DataItem {
	int data;
	int key;
};

void other_hash_main();
void insert(int key, int data);
int	hashCode(int key);
struct DataItem	*search(int key);