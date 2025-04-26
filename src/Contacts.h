#ifndef CONTACTS_HEADER
    #define CONTACTS_HEADER

    #include <stdio.h>
    #include <string.h>

    typedef struct {
        char name[50];
        char phone[20];
        char email[50];
    } Contact;

    #define TRUE 1
    #define FALSE 0
    #define MAX_LENGTH 1000

    int get_input(char* result, int result_size);
    int test(void);
    int run(void);

    Contact get_contact(Contact contacts[], int contacts_size, int index);
    void add_contact(Contact contacts[], int contacts_size, char* name, char* phone, char* email);
    void delete_contact(Contact contacts[], int contacts_size, int index);
    void list_contacts(Contact contacts[], int contacts_size);
    int is_contact_empty(Contact contacts[], int index);

#endif