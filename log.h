#ifndef LOG_H_
#define LOG_H_

#include"def.h"

void push_log(Log** lg, int lineno, char* url, char* title, char* content, char* time);


void print_log(Log* lg);

#endif
