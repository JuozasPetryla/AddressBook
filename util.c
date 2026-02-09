#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "shared.h"

#define MAX_LEN

char* read_input_str(const char *msg, size_t max_len)
{
    printf("%s\n", msg);

    int c;
    while ((c = getchar()) == '\n');
    if (c != EOF) ungetc(c, stdin);

    char *buf = (char*)malloc(max_len + 1);
    if (!buf) return NULL;

    if (!fgets(buf, max_len + 1, stdin)) {
        free(buf);
        return NULL;
    }

    size_t len = strlen(buf);

    if (len > 0 && buf[len - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } else if (len > 0) {
        buf[len - 1] = '\0';
    }

    return buf;
}

extern int read_input_int(const char *msg)
{
    int number;
    int c;

    while (1) {
        printf("%s\n", msg);

        if (scanf("%d", &number) == 1)
            return number;

        printf("Invalid input! Please enter a valid integer.\n");

        while ((c = getchar()) != '\n' && c != EOF);
    }
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