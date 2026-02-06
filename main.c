#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "address.h"
#include "util.h"

#define TABLE_WIDTH 103

void displayAddresses(Node *node);

void fillDashes();

void read_address_csv(const char *filename, LList *llist);

void addNewAddress(LList *llist);

void insertNewAddress(LList *llist, int pos);

int main()
{
    LList *llist = (LList*) malloc(sizeof(LList));

    read_address_csv("./addresses.csv", llist);

    // addNewAddress(llist);

    displayAddresses(llist->head);

    // insertNewAddress(llist, 0);
    // insertNewAddress(llist, 9);
    insertNewAddress(llist, 4);

    displayAddresses(llist->head);

    return 0;
}

void read_address_csv(const char *filename, LList *llist) 
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char line[1024];

    fgets(line, sizeof line, fp);

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *name = strtok(line, ",");
        char *surname = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *phone_number = strtok(NULL, ",");

        Address *address = createAddress(name, surname, email, phone_number);

        llist_append(llist, address);
    }

    fclose(fp);
}

void insertNewAddress(LList *llist, int pos)
{
    printf("Enter address\n");

    char *name = read_string_console("name");
    char *surname = read_string_console("surname");
    char *email = read_string_console("email");
    char *phone_number = read_string_console("phone number");

    Address *address = createAddress(name, surname, email, phone_number);

    llist_insert(llist, address, pos);
}

void addNewAddress(LList *llist)
{
    printf("Enter address\n");

    char *name = read_string_console("name");
    char *surname = read_string_console("surname");
    char *email = read_string_console("email");
    char *phone_number = read_string_console("phone number");

    Address *address = createAddress(name, surname, email, phone_number);

    llist_append(llist, address);
}

void displayAddresses(Node *node) 
{
    fillDashes();
    printf("| %20s | %20s | %35s | %15s |\n", "Name", "Surname", "Email", "Phone Number");
    fillDashes();
    for (Node *curr = node; curr != NULL; curr = curr->next) {
        Address *address = (Address*)curr->data;

        if (address == NULL) continue;

        printf("| %20s | %20s | %35s | %15s |\n", 
            address->name,
            address->surname,
            address->email,
            address->phone_number
        );
    }
    fillDashes();
}

void fillDashes() {
    for (int i = 0; i < TABLE_WIDTH; ++i) {
        printf("-");
    }
    printf("\n");
}