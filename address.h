#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct
{
    char *name;
    char *surname;
    char *email;
    char *phone_number;
} Address;

Address* address_create(
    const char *name,
    const char *surname,
    const char *email,
    const char *phone_number
);

void address_destroy(Address *address);

#endif