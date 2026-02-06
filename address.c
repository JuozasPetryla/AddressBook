#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "util.h"
#include "address.h"

Address* createAddress(
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

bool contains(void *data, const char *input_str)
{
    Address *address = (Address*)data;

    if (address == NULL) return false;

    return string_contains(address->name, input_str) ||
        string_contains(address->surname, input_str) ||
        string_contains(address->email, input_str) ||
        string_contains(address->phone_number, input_str);
}