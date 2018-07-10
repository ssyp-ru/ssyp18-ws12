#include "stdafx.h"
#include "zbrtree.h"
#include"zbrstr.h"
#include"zbrdic.h"
#define SIZE_TREE 5000

int size_tree(Tree* root) {
	if (!root)
		return 0;
	return(size_tree(root->left) + size_tree(root->right) + 1);
}

void add_to_tree(Tree* root, char* word, char* translate) {
	int res_cmp = cmp(root->word, word);
	if (res_cmp == 1) {
		if (root->right == NULL) {
			root->right = create_tree(word, translate);
			return;
		}
		add_to_tree(root->right, word, translate);
		return;
	}
	if (res_cmp == -1) {
		if (root->left == NULL) {
			root->left = create_tree(word, translate);
			return;
		}
		add_to_tree(root->left, word, translate);
		return;
	}
	if (res_cmp == 0) 
		return;
}

Tree * arr_to_tree(Tree ** arr, int n) {
	Tree* root;
	if (n == 2) {
		root = arr[0];
		root->right = arr[1];
		root->left = NULL;
		arr[1]->left = NULL;
		arr[1]->right = NULL;
	}
	if (n == 1) {
		root = arr[0];
		root->left = NULL;
		root->right = NULL;
	}
	if (n == 0) {
		return NULL;
	}
	int i = n / 2;
	root = arr[i];
	root->right = arr_to_tree(arr, i);
	root->left = arr_to_tree(arr + n / 2 + 1, n - i - 1);
	return(root);

}


void remove_tree(Tree * root) {
	if (root) {
		free(root->word);
		free(root->translate);
		remove_tree(root->left);
		remove_tree(root->right);
		free(root);
	}
}

Tree * create_tree(char * word, char * translate) {
	Tree* tree;
	tree = (Tree*)malloc(sizeof(Tree));
	tree->word = cp(word);
	tree->translate = cp(translate);
	tree->right = NULL;
	tree->left = NULL;
	return tree;
}

char* search_in_tree(char* word, Tree* root) {
	if (root == NULL) {
		return NULL;
	}
	int res_cmp = cmp(root->word, word);
	if (res_cmp == 1) {
		return(search_in_tree(word, root->right));
	}
	if (res_cmp == -1) {
		return(search_in_tree(word, root->left));
	}
	if (res_cmp == 0) {
		return(root->translate);
	}
	return NULL;
}

void print_tree(Tree * root)
{
	if (root == NULL)
		return;
	printf("%s", root->word);
	print_tree(root->left);
	print_tree(root->right);
}


void tree_to_arr(Tree* root, Tree** arr) {
	if (root) {
		int n = size_tree(root);
		*arr = root;
		tree_to_arr(root->left, arr + 1);
		tree_to_arr(root->right, arr + 1 + size_tree(root->left));
	}
}

void sort(Tree** arr, int n) {
	int flag = 1;
	int i;
	Tree *tmp;
	while (flag == 1) {
		flag = 0;
		for (i = 0; i < n - 1; i++) {
			if (cmp(arr[i]->word, arr[i + 1]->word) == 1) {
				flag = 1;
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

Tree* balancing_tree(Tree* root) {
	if (!root) {
		return NULL;
	}
	Tree** arr;
	int len_tree;
	len_tree = size_tree(root);
	arr = (Tree**)malloc(len_tree * sizeof(Tree*));
	tree_to_arr(root, arr);
	sort(arr, len_tree);
	Tree* qwe = arr_to_tree(arr, len_tree);
	return(arr_to_tree(arr, len_tree));
}