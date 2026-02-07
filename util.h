#ifndef UTIL_H
#define UTIL_H

#include "llist.h"

char* read_input_str(const char *msg);
int read_input_int(const char *msg);
bool string_contains(const char *target_str, const char *input_str);
void read_csv_to_list(const char *filename, LList *llist);
void fill_symbols(int table_width, char symbol);

bool contains(void *data, const char *input_str);
void* parse_line(char line[]);
void destroy(void *data);

#endif