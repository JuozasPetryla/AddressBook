#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"

extern char* read_input_str(const char *msg) 
{
    char buf[128];

    printf("%s\n", msg);
    scanf("%s", buf);

    size_t len = strlen(buf);
    char *str = (char*)malloc(len + 1);

    memcpy(str, buf, len + 1);

    return str;
}

extern int read_input_int(const char *msg)
{
    int number;
    
    printf("%s\n", msg);
    if (scanf("%d", &number) != 1) {
        printf("Invalid input! Please enter a valid integer.\n");
    }   

    return number;
}

extern void read_csv_to_list(const char *filename, LList *llist)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s\n", filename);
        return;
    }

    char line[1024];

    fgets(line, sizeof line, fp);

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = '\0';

        void *parsed_line = parse_line(line);

        llist_append(llist, parsed_line);
    }

    fclose(fp);
}

extern bool string_contains(const char *target_str, const char *input_str) {
    return strstr(target_str, input_str) != NULL;
}

extern void fill_symbols(int table_width, char symbol) {
    for (int i = 0; i < table_width; ++i) {
        printf("%c", symbol);
    }
    printf("\n");
}