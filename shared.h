#ifndef SHARED_H
#define SHARED_H

#include <stdbool.h>

bool contains(void *data, const char *input_str);
void* parse_line(char line[]);
void destroy(void *data);

#endif