#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct
{
    char *name;
    char *surname;
    char *email;
    char *phone_number;
} Address;

Address* create_address(
    const char *name,
    const char *surname,
    const char *email,
    const char *phone_number
);

#endif