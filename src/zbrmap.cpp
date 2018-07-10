#include "stdafx.h"
#include "zbrmap.h"
#include "zbrstr.h"


Map create_map() {
	int i;
	Map arr = (Map)malloc(MAP_SIZE * sizeof(Map));
	for (i = 0; i < MAP_SIZE; i++)
		arr[i] = NULL;
	return arr;
}

void remove_map(Map map) {
	int i;
	if (map) {
		for (i = 0; i < MAP_SIZE; i++)
			remove_tree(map[i]);
		free(map);
	}
}

int get_index_map(char *word) {
	char a;
	char b;
	if (len(word) < 2)
		return(MAP_SIZE - 1);
	a = word[0];
	b = word[1];
	if (is_eng_char(a) && is_eng_char(b))
		return ((a - 'a') * ABC_SIZE_ENG + (b - 'a'));
	if (is_rus_char(a) && is_rus_char(b))
		return ((a - 'à') * ABC_SIZE_RUS + (b - 'à'));
	return(MAP_SIZE - 1);
}

char* search_in_map(Map map, char *word) {
	int i = get_index_map(word);
	char* a = search_in_tree(word, map[i]);
	return(a);
}

void add_to_map(Map map, char* word, char *translate) {
	int i = get_index_map(word);
	if (map[i]) {
		add_to_tree(map[i], word, translate);

	}
	else {
		map[i] = create_tree(word, translate);
	}
}