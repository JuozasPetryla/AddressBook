#ifndef UTIL_H
#define UTIL_H

#include "llist.h"

char* read_input_str(const char *msg, size_t max_len);
int read_input_int(const char *msg);
bool string_contains(const char *target_str, const char *input_str);
void read_csv_to_list(const char *filename, LList *llist);
void fill_symbols(int table_width, char symbol);

#endif