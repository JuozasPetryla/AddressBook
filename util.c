#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* read_string_console(const char *input_type) 
{
    char buf[128];

    printf("\nInput %s:\n", input_type);
    scanf("%s", buf);

    size_t len = strlen(buf);
    char *str = (char*)malloc(len + 1);

    memcpy(str, buf, len + 1);

    return str;
}
