#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "address.h"
#include "util.h"

#define TABLE_WIDTH 103

void display_addresses(LList *llist);

void fill_dashes();

void read_address_csv(const char *filename, LList *llist);

void add_new_address(LList *llist);

void insert_new_address(LList *llist, int pos);

void find_address_by_pos(LList *llist, int pos);

void find_address_by_str(LList *llist, char *str);

void remove_address_by_pos(LList *llist, int pos);

void remove_all_addresses(LList *llist);

int main()
{
    LList *llist = (LList*) malloc(sizeof(LList));

    read_address_csv("./addresses.csv", llist);

    // add_new_address(llist);

    display_addresses(llist);

    // insert_new_address(llist, 0);
    // insert_new_address(llist, 9);
    // insert_new_address(llist, 4);

    // find_address_by_pos(llist, 0);
    // find_address_by_pos(llist, 9);
    // find_address_by_pos(llist, 5);

    // find_address_by_str(llist, "Lukas");
    // find_address_by_str(llist, "Monika");
    // find_address_by_str(llist, "6901");

    remove_address_by_pos(llist, 9);
    display_addresses(llist);
    remove_address_by_pos(llist, 0);
    display_addresses(llist);
    remove_address_by_pos(llist, 5);

    // remove_all_addresses(llist);

    display_addresses(llist);
    // display_addresses(llist);

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

void insert_new_address(LList *llist, int pos)
{
    printf("Enter address\n");

    char *name = read_string_console("name");
    char *surname = read_string_console("surname");
    char *email = read_string_console("email");
    char *phone_number = read_string_console("phone number");

    Address *address = createAddress(name, surname, email, phone_number);

    llist_insert(llist, address, pos);
}

void add_new_address(LList *llist)
{
    printf("Enter address\n");

    char *name = read_string_console("name");
    char *surname = read_string_console("surname");
    char *email = read_string_console("email");
    char *phone_number = read_string_console("phone number");

    Address *address = createAddress(name, surname, email, phone_number);

    llist_append(llist, address);
}

void display_addresses(LList *llist) 
{
    fill_dashes();
    printf("| %20s | %20s | %35s | %15s |\n", "Name", "Surname", "Email", "Phone Number");
    fill_dashes();

    LListIter *iter = llist_iter_create(llist);
    while (llist_iter_condition(iter)) {
        Address *address = (Address*) llist_iter_next(iter);
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
    }
    llist_iter_free(iter);

    fill_dashes();
}

void find_address_by_pos(LList *llist, int pos) 
{
    Address *address = (Address*)llist_find_pos(llist, pos);
    printf("Searching for address at position %d\n", pos);
    if (address != NULL) {
        fill_dashes();
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
        fill_dashes();
    } else {
        printf("Could not find address\n");
    }
}

void find_address_by_str(LList *llist, char *str) 
{
    Address *address = (Address*)llist_find_str(llist, str);
    printf("Searching for address with matching string '%s'\n", str);
    if (address != NULL) {
        fill_dashes();
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
        fill_dashes();
    } else {
        printf("Could not find address\n");
    }
}

void remove_address_by_pos(LList *llist, int pos)
{
    Address *address = (Address*)llist_remove(llist, pos);
    printf("Removing for address at position %d\n", pos);
    if (address != NULL) {
        fill_dashes();
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
        fill_dashes();
    } else {
        printf("Could not remove address\n");
    }
}

void remove_all_addresses(LList *llist)
{
    printf("Removing all addresses from address book\n");
    llist_remove_all(llist);
}

void fill_dashes() {
    for (int i = 0; i < TABLE_WIDTH; ++i) {
        printf("-");
    }
    printf("\n");
}