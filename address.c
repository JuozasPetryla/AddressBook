#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "address.h"
#include "shared.h"
#include "util.h"

Address* address_create(
    const char *name,
    const char *surname,
    const char *email,
    const char *phone_number
)
{
    Address *address = (Address*)malloc(sizeof(Address));

    address->name = (char*)malloc(strlen(name) + 1);
    address->surname = (char*)malloc(strlen(surname) + 1);
    address->email = (char*)malloc(strlen(email) + 1);
    address->phone_number = (char*)malloc(strlen(phone_number) + 1);

    strcpy(address->name, name);
    strcpy(address->surname, surname);
    strcpy(address->email, email);
    strcpy(address->phone_number, phone_number);

    return address;
}

void destroy(void *data)
{
    Address *address = (Address*) data;

    if (address == NULL) return;

    free(address->name);
    free(address->surname);
    free(address->email);
    free(address->phone_number);
    free(address);
}

bool contains(void *data, const char *input_str)
{
    Address *address = (Address*)data;

    if (address == NULL) return false;

    return string_contains(address->name, input_str) ||
        string_contains(address->surname, input_str) ||
        string_contains(address->email, input_str) ||
        string_contains(address->phone_number, input_str);
}

void* parse_line(char line[])
{
    char *name = strtok(line, ",");
    char *surname = strtok(NULL, ",");
    char *email = strtok(NULL, ",");
    char *phone_number = strtok(NULL, ",");

    return address_create(name, surname, email, phone_number);
}