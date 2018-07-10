#pragma once
#include "zbrmap.h"
#define MAX_STRING 2000

int open_dic(const char* filename, Map dic);
char* search_in_dic(char* s, Map dic);
void close_dic(Map dic);
char* loose_search(char* s, Map dic);
void optimization(Map dic);