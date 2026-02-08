#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <stdbool.h>
#include <signal.h>
#include "llist.h"
#include "address.h"
#include "util.h"
#include "shared.h"

#define ADDRESS_BOOK_WIDTH 103

LList *llist;

typedef enum {
    DEFAULT,
    DISPLAY_ALL,
    APPEND,
    INSERT,
    REMOVE,
    REMOVE_ALL,
    FIND_BY_POS,
    FIND_BY_STR,
    EXIT
} Action;

void _display_address_safe(Address *address, const char *err_msg);

Address* _read_address_from_input();

void _handle_default_action(Action action);

void _clear_screen();

void _handle_sigint(int sig);

void _cleanup();

void perform_selected_action(Action action);

void display_all_addresses();

void append_address();

void insert_address();

void find_address_by_pos();

void find_address_by_str();

void remove_address();

void remove_all_addresses();

int main()
{
    signal(SIGINT, _handle_sigint);

    llist = (LList*)malloc(sizeof(LList));
    llist_init(llist);

    read_csv_to_list("./addresses.csv", llist);

    Action action = DEFAULT;
    
    while(action != EXIT) {
        perform_selected_action(action);
        action = (Action)read_input_int("Choose an action: ");
    }


    _cleanup();

    exit(0);
}

void perform_selected_action(Action action)
{
    _clear_screen();

    fill_symbols(ADDRESS_BOOK_WIDTH, '*');
    printf("| %-99s |\n", "Address Book management program");
    printf("| %-s%-74d |\n", "Records in address book: ", (int)llist->size);
    fill_symbols(ADDRESS_BOOK_WIDTH, '*');  

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
    int pos = read_input_int("Input address insertion position:");

    Address *address = _read_address_from_input();
    bool result = llist_insert(llist, address, pos);
    if (!result) {
        printf("Invalid insert position of %d\n", pos);
    } else {
        printf("Inserted address to book position %d\n", pos);
    }
}

void append_address()
{
    Address *address = _read_address_from_input();

    llist_append(llist, address);
    printf("Appended address to the end of the book\n");
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
    int pos = read_input_int("Input position for the address to be found:");

    Address *address = (Address*)llist_find_pos(llist, pos);
    _display_address_safe(address, "Could not find address");
}

void find_address_by_str() 
{
    char *str = read_input_str("Input string to search the address by:");

    Address *address = (Address*)llist_find_str(llist, str);
    free(str);
    _display_address_safe(address, "Could not find address");
}

void remove_address()
{
    int pos = read_input_int("Input address to remove position:");

    Address *address = (Address*)llist_remove(llist, pos);
    _display_address_safe(address, "Could not remove address");

    destroy(address);
}

void remove_all_addresses()
{
    bool result = llist_remove_all(llist);
    if (!result) {
        printf("Book is already empty\n");
    } else {
        printf("Successfully removed all addresses from the book\n");
    }
}

void _show_action_types()
{
    fill_symbols(ADDRESS_BOOK_WIDTH, '*');
    printf("| %-99s |\n", "0: Show available action types");
    printf("| %-99s |\n", "1: Display all addresses");
    printf("| %-99s |\n", "2: Append a new address to the book");
    printf("| %-99s |\n", "3: Insert a new address in the selected position");
    printf("| %-99s |\n", "4: Remove an address from the selected position the book");
    printf("| %-99s |\n", "5: Remove all addresses from the book");
    printf("| %-99s |\n", "6: Find an address in the selected position in the book");
    printf("| %-99s |\n", "7: Find an address by the first matching string in the book");
    printf("| %-99s |\n", "8: Exit program");
    fill_symbols(ADDRESS_BOOK_WIDTH, '*');
}

void _handle_default_action(Action action)
{
    if (DEFAULT != action) {
        printf("| %-99s |\n", "Invalid action type, please select a valid action:");
    }
    _show_action_types();
}

Address* _read_address_from_input()
{
    printf("Enter address\n");

    char *name = read_input_str("Input name:");
    char *surname = read_input_str("Input surname:");
    char *email = read_input_str("Input email:");
    char *phone_number = read_input_str("Input phone number:");

    Address *address = address_create(name, surname, email, phone_number);
    
    free(name);
    free(surname);
    free(email);
    free(phone_number);

    return address;
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

void _clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
    fflush(stdout);
#endif
}

void _handle_sigint(int)
{
    _cleanup();
    exit(0);
}

void _cleanup()
{
    if (llist) {
        llist_remove_all(llist);
        free(llist);
        llist = NULL;
    }
}
