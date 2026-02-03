#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

int CNT = 10;

typedef struct
{
    char name[20];
    char surname[20];
    char email[30];
    char phone_number[30];
} Address;

void displayAddresses(Node *node);

void createAddress(Address *address);

void fillDashes();

int main()
{
    LList *llist = llist_init();

    Address *address1 = malloc(sizeof(Address));
    createAddress(address1);

    Address *address2 = malloc(sizeof(Address));
    createAddress(address2);

    Address *address3 = malloc(sizeof(Address));
    createAddress(address3);

    llist_append(llist, address1);
    llist_append(llist, address2);
    llist_append(llist, address3);

    displayAddresses(llist->head->next);

    return 0;
}

void createAddress(Address *address)
{
    strcpy(address->name, "Juozas");
    strcpy(address->surname, "Petryla");
    strcpy(address->email, "itsgrtjuozas@gmail.com");
    strcpy(address->phone_number, "+37065327044");
}

void displayAddresses(Node *node) 
{
    printf("| %20s | %20s | %30s | %30s |\n", "Name", "Surname", "Email", "Phone Number");
    fillDashes();
    for (Node *curr = node; curr != NULL; curr = curr->next)
    {
        Address *address = (Address*)curr->data;

        if (address == NULL) continue;

        printf("| %20s | %20s | %30s | %30s |\n", 
            address->name,
            address->surname,
            address->email,
            address->phone_number
        );
    }
    fillDashes();
}

void fillDashes() {
    int count = sizeof(Address) + 13;
    for (int i = 0; i < count; ++i) 
    {
        printf("-");
    }
    printf("\n");
}