#pragma once

typedef struct Node {
	Node* right;
	Node* left;
	char* word;
	char* translate;
} Tree;

extern int deep;

Tree* create_tree(char* word, char* translate);
void remove_tree(Tree* root);
int size_tree(Tree* root);
void add_to_tree(Tree* root, char* word, char* translate);
void print_tree(Tree* root);
char* search_in_tree(char* word, Tree* root);
void tree_to_arr(Tree* root, Tree** arr);
Tree* arr_to_tree(Tree** arr, int n);
void sort(Tree** arr, int n);
Tree* balancing_tree(Tree* root);