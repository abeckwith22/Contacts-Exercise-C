#ifndef CONTACTS_HEADER
    #define CONTACTS_HEADER

    #include <stdio.h>
    #include <string.h>

    // This is our basic contact struct.
    typedef struct Contact {
        char name[50];
        char phone[20];
        char email[50];
        struct Contact *next;
    } Contact;

    #define TRUE 1
    #define FALSE 0
    #define MAX_LENGTH 1000 // Defines max length for user input.

    // Gets input from user and modifies result, returns input length.
    int get_input(char* result, int result_size);

    // Testing new features and debugging.
    int test(void);

    // Actual run code.
    int run(void);

    // Returns a contact at a specified index.
    Contact get_contact(Contact* head, const char* email);

    // Adds contact to contact array, needs name, phone, email.
    void add_contact(Contact** head, const char* name, const char* phone, const char* email);

    // Prints info about contact (i.e. name, phone, email)
    void get_contact_info(Contact *contact);

    // Deletes contact from contact list, needs an index.
    int delete_contact(Contact** head, const char* email);

    // Traverse all contacts in contacts list.
    void list_contacts(Contact* head);

    // Gets the last node in linked list
    Contact* get_tail(Contact* head);

    int is_duplicate_email(Contact** head, const char* email);

#endif
