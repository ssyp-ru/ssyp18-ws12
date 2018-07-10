#pragma once
#include "zbrtree.h"

#define MAP_SIZE 1090
#define ABC_SIZE_ENG 26
#define ABC_SIZE_RUS 33

typedef Tree** Map;

char* search_in_map(Map map, char *word);
Map create_map();
void remove_map(Map map);
void add_to_map(Map map, char* word, char *translate);
int get_index_map(char * word);
