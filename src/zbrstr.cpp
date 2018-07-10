#include "stdafx.h"
#include"zbrstr.h"

int cmp(char * a, char * b) {
	if (*a == 0 && *b == 0)
		return 0;
	if (*a < *b)
		return (-1);
	if (*a > *b)
		return 1;
	if (*a == *b)
		return(cmp(a + 1, b + 1));
}

int len(char* a) {
	int i = 0;
	if (a == NULL)
		return(0);
	while (*a) {
		a++;
		i++;
	}
	return(i);
}

char* cp(char *a) {
	int i;
	int n = len(a);
	char* new_a;
	if (a == NULL)
		return(NULL);
	new_a = (char*)malloc((n + 1) * sizeof(char));
	for (i = 0; i < n; i++) {
		new_a[i] = a[i];
	}
	new_a[n] = 0;
	return(new_a);
}

char low_char(char c) {
	if (is_up_rus_char(c))
		return (c + ('à' - 'À'));
	if (is_up_eng_char(c))
		return (c + ('a' - 'A'));
	return c;
}

void low_string(char* s) {
	char* a = s;
	while (*a) {
		*a = low_char(*a);
		a++;
	}
}

int is_eng_char(char c) {
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

int is_rus_char(char c) {
	if (c >= 'à' && c <= 'ÿ' || c >= 'À' && c <= 'ß')
		return 1;
	return 0;
}


int is_up_eng_char(char c) {
	if (c >= 'A' && c <= 'Z')
		return 1;
	return 0;
}

int is_up_rus_char(char c) {
	if (c >= 'À' && c <= 'ß')
		return 1;
	return 0;
}

void trans(char* s) {
	char alphabet_eng[34] = { "ôèñâóàïðøîëäüòùçéêûåãìö÷íÿ" };
	char alphabet_rus[34] = { "f,dult;pbqrkvyjghcnea[wxioms]\'.z" };
	if (is_rus_char(s[0])) {
		while (*s) {
			*s = alphabet_rus[(*s) - 'à'];
			s++;
		}
		return;
	}
	if (is_eng_char(*s)) {
		while (*s) {
			if (*s == ',')
				*s = 'á';
			else if (*s == '.')
				*s = 'þ';
			else
				*s = alphabet_eng[(*s) - 'a'];
			s++;
		}
		return;
	}
}