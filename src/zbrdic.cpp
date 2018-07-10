#include "stdafx.h"
#include "zbrtree.h"
#include "zbrmap.h"
#include"zbrstr.h"
#include"zbrdic.h"

#define SIZE_NAME 1000
#define SIZE_TRANS 20000
#define WORD_SEPARATE '|'
#define TRANSLATE_SEPARATE '#'

int open_dic(const char* filename, Map dic) {
	char symbol;
	int isName;
	int i;
	char* name;
	char* trans;

	FILE *in = fopen(filename, "rt");
	if (!in) {
		return 0;
	}

	name = (char*)malloc(SIZE_NAME * sizeof(char));
	trans = (char*)malloc(SIZE_TRANS * sizeof(char));
	isName = 1;
	i = 0;

	while (fscanf(in, "%c", &symbol) == 1) {
		if (isName == 1 && symbol != WORD_SEPARATE) {
			name[i] = symbol;
			i++;
			continue;
		}
		if (isName == 1 && symbol == WORD_SEPARATE) {
			name[i] = 0;
			isName = 0;
			i = 0;
			continue;
		}
		if (isName == 0 && symbol != TRANSLATE_SEPARATE) {
			trans[i] = symbol;
			i++;
			continue;
		}
		if (isName == 0 && symbol == TRANSLATE_SEPARATE) {
			trans[i] = 0;
			low_string(name);
			low_string(trans);
			add_to_map(dic, name, trans);
			isName = 1;
			i = 0;
			continue;
		}
	}

	free(name);
	free(trans);
	fclose(in);
	return 1;
}

char* search_in_dic(char* s, Map dic) {
	low_string(s);
	char* a;
	a = search_in_map(dic, s);
	if (a)
		return a;
	a = loose_search(s, dic);
	if (a)
		return a;
	trans(s);
	return(search_in_map(dic, s));
}

void close_dic(Map dic) {
	remove_map(dic);
}

char* loose_search(char* s, Map dic) {
	char* str = s;
	char tmp;
	char* str_trans;
	char low = 'a';
	char up = 'z';
	if (is_rus_char(s[0])) {
		low = 'à';
		up = 'ÿ';
	}

	if (is_eng_char(s[0]) || is_rus_char(s[0])) {
		while (*s) {
			tmp = *s;
			(*s)++;
			while (*s <= up) {
				str_trans = search_in_map(dic, str);
				if (str_trans) 
					return(str_trans);
				(*s)++;
			}
			*s = tmp;
			(*s)--;
			while (*s >= low) {
				str_trans = search_in_map(dic, str);
				if (str_trans) 
					return(str_trans);
				(*s)--;
			}
			*s = tmp;
			s++;
		}
	}
	return NULL;
}

void optimization(Map dic) {
	for (int j = 0; j < MAP_SIZE; j++) {
		dic[j] = balancing_tree(dic[j]);
	}
}