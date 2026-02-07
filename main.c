#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <stdbool.h>
#include "llist.h"
#include "address.h"
#include "util.h"

#define ADDRESS_BOOK_WIDTH 103
#define INTERFACE_MENU_WIDTH 79

LList *llist;

typedef enum {
    DEFAULT,
    DISPLAY_ALL,
    APPEND,
    INSERT,
    REMOVE,
    REMOVE_ALL,
    FIND_BY_POS,
    FIND_BY_STR
} action;

void _display_address_safe(Address *address, const char *err_msg);

Address* _read_address_from_input();

void _handle_default_action(action action);

void perform_selected_action(action action);

void display_all_addresses();

void append_address();

void insert_address();

void find_address_by_pos();

void find_address_by_str();

void remove_address();

void remove_all_addresses();

int main()
{
    llist = (LList*) malloc(sizeof(LList));
    read_csv_to_list("./addresses.csv", llist);

    action action = DEFAULT;
    
    fill_symbols(INTERFACE_MENU_WIDTH, '*');
    printf("| %-75s |\n", "Welcome to the Address Book program!");
    fill_symbols(INTERFACE_MENU_WIDTH, '*');

    while(true) {
        perform_selected_action(action);
        
        printf("Choose an action: ");
        scanf("%d", &action);
    }

    return 0;
}

void perform_selected_action(action action)
{
    switch (action)
    {
    case DISPLAY_ALL:
        display_all_addresses();
        break;
    case APPEND: 
        append_address();
        break;
    case INSERT:
        insert_address();
        break;
    case REMOVE:
        remove_address();
        break;
    case REMOVE_ALL:
        remove_all_addresses();
        break;
    case FIND_BY_POS:
        find_address_by_pos();
        break;
    case FIND_BY_STR:
        find_address_by_str();
        break;
    default:
        _handle_default_action(action);
        break;
    }
}

void insert_address()
{
    int pos;

    printf("Input address insertion position:");
    scanf("%d", &pos);

    Address *address = _read_address_from_input();

    llist_insert(llist, address, pos);
}

void append_address()
{
    Address *address = _read_address_from_input();

    llist_append(llist, address);
}

void display_all_addresses() 
{
    fill_symbols(ADDRESS_BOOK_WIDTH, '-');
    printf("| %20s | %20s | %35s | %15s |\n", "Name", "Surname", "Email", "Phone Number");
    fill_symbols(ADDRESS_BOOK_WIDTH, '-');

    LListIter *iter = llist_iter_create(llist);
    while (llist_iter_condition(iter)) {
        Address *address = (Address*) llist_iter_next(iter);
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
    }
    llist_iter_free(iter);

    fill_symbols(ADDRESS_BOOK_WIDTH, '-');
}

void find_address_by_pos() 
{
    int pos;

    printf("Input position for the address to be found:");
    scanf("%d", &pos);

    Address *address = (Address*)llist_find_pos(llist, pos);
    printf("Searching for address at position %d\n", pos);
    _display_address_safe(address, "Could not find address");
}

void find_address_by_str() 
{
    char str[128];

    printf("Input string to search the address by:");
    scanf("%s", str);

    Address *address = (Address*)llist_find_str(llist, str);

    printf("Searching for address with matching string '%s'\n", str);
    _display_address_safe(address, "Could not find address");
}

void remove_address()
{
    int pos;

    printf("Input address to remove position:");
    scanf("%d", &pos);

    Address *address = (Address*)llist_remove(llist, pos);
    printf("Removing for address at position %d\n", pos);
    _display_address_safe(address, "Could not remove address");
}

void remove_all_addresses()
{
    printf("Removing all addresses from address book\n");
    llist_remove_all(llist);
}

void _show_action_types()
{
    fill_symbols(INTERFACE_MENU_WIDTH, '*');
    printf("| %-75s |\n", "0: Show available action types");
    printf("| %-75s |\n", "1: Display all addresses");
    printf("| %-75s |\n", "2: Append a new address to the book");
    printf("| %-75s |\n", "3: Insert a new address in the selected position");
    printf("| %-75s |\n", "4: Remove an address from the selected position the book");
    printf("| %-75s |\n", "5: Remove all addresses from the book");
    printf("| %-75s |\n", "6: Find an address in the selected position in the book");
    printf("| %-75s |\n", "7: Find an address by the first matching string in the book");
    fill_symbols(INTERFACE_MENU_WIDTH, '*');
}

void _handle_default_action(action action)
{
    if (DEFAULT != action) {
        printf("Invalid action type, please select a valid action:\n");
    }
    _show_action_types();
}

Address* _read_address_from_input()
{
    printf("Enter address\n");

    char *name = read_string_console("name");
    char *surname = read_string_console("surname");
    char *email = read_string_console("email");
    char *phone_number = read_string_console("phone number");

    return create_address(name, surname, email, phone_number);
}

void _display_address_safe(Address *address, const char *err_msg)
{
    if (address != NULL) {
        fill_symbols(ADDRESS_BOOK_WIDTH, '-');
        printf("| %20s | %20s | %35s | %15s |\n", address->name, address->surname, address->email, address->phone_number);
        fill_symbols(ADDRESS_BOOK_WIDTH, '-');
    } else {
        printf("%s\n", err_msg);
    }
}