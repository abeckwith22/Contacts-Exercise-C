#include "Contacts.h"
#include <string.h>
#include <stdlib.h>

// ====================
// TODO
// ====================
// - [ ] Add a tui with the following features, all of which should be accessible through the program
//      - [ ] User can go through a series of options to list contacts
//      - [ ] Get a specific contact
//      - [ ] Add a contact
// - [ ] Security
//      - [ ] Shouldn't allow user to input duplicate email.
//      - [ ] When adding contact, values (i.e. name, phone, email) should not be empty and should also be valid.
// - [ ] Features
//      - [ ] Test for edge cases
//

int test(void) {
    char string[MAX_LENGTH] = {};
    char name[50] = "First Last";
    char phone[20] = "123-456-7890";
    char email[50] = "firstlast@email.com";

    Contact first_contact = {
        .name="Sprinky Jims Junior",
        .phone="512-789-0254",
        .email="FloridaMan@email.com",
    };
    Contact second_contact = {
        .name="Jeremy P. Butler",
        .phone="512-789-0255",
        .email="JeremyBut(t)ler@email.com",
    };
    Contact third_contact = {
        .name="Satan",
        .phone="666-666-6666",
        .email="ElDiablo@email.com",
        .next=NULL
    };
    Contact fourth_contact = {
        .name="Testing",
        .phone="123-456-7890",
        .email="firstlast@email.com",
        .next=NULL
    };

    Contact* head = &first_contact;

    first_contact.next = &second_contact;
    second_contact.next = &third_contact;

    // Before allocation of new contact
    printf("------------------------ BEFORE ALLOCATION ------------------------\n");
    list_contacts(head);

    // After allocation of new contact
    printf("------------------------ AFTER  ADD   USER ------------------------\n");
    add_contact(&head, name, phone, email);
    list_contacts(&first_contact);
    
    printf("------------------------ AFTER DELETE USER ------------------------\n");
    delete_contact(&head, "firstlast@email.com");
    list_contacts(&first_contact);
    return 0;
}

void list_contacts(Contact *head) {
    Contact *current=head;
    for(int i=0; current != NULL; i++, current=current->next) {
        printf("================= Contact #%d: =================\n", i);
        printf("Name  : %s\n", current->name);
        printf("Phone : %s\n", current->phone);
        printf("Email : %s\n", current->email);
    }
    return;
}

void get_contact_info(Contact *contact) {
    printf("================= Contact =================\n");
    printf("Name  : %s\n", contact->name);
    printf("Phone : %s\n", contact->phone);
    printf("Email : %s\n", contact->email);
    printf("===========================================\n");

    return;
}

Contact* get_tail(Contact *head) {
    if(head==NULL) return head;
    
    Contact *current;
    // Traverses list until the next value is null indicating the tail.
    for(current=head; current->next != NULL; current=current->next); 
    return current;
}

int run(void) {
    return 0;
}

int tui(void) {
    return 0;
} 

// TODO: Could I just dumb this down to an scanf?
int get_input(char* result, int result_size) {
    char c;
    int i;
    // for every character user types, i increments by 1 to get string length. Also makes sure 'i' is not incremented beyond size of result string.
    for(i = 0; (c = getchar()) != EOF && c != '\n' && c != '\t' && i < result_size; i++) {
        *(i+result) = c;
    }

    return i;
}

int is_duplicate_email(Contact **head, const char* email) {
    for(Contact *current=*head; current!=NULL; current=current->next) {
        if(strcmp(current->email, email) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

// Needs a unique ID to be able to search properly
Contact get_contact(Contact *head, const char *email) {
    return *head;
}

void add_contact(Contact **head, const char *name, const char *phone, const char *email) {

    // Allocate memory for new contact
    Contact *new_contact = (Contact *) malloc(sizeof(Contact));

    if(new_contact == NULL) {
        printf("function add_contact(): Failed to allocated memory\n");
        return;
    }

    if(is_duplicate_email(head, email)) {
        printf("function add_contact(): Email address already exists, exiting.");
        return;
    }

    // Set values for new_contact with string copy and adding a terminating value at the end.
    strncpy(new_contact->name, name, sizeof(new_contact->name) - 1);
    new_contact->name[sizeof(new_contact->name) - 1] = '\0';

    strncpy(new_contact->phone, phone, sizeof(new_contact->phone) - 1);
    new_contact->phone[sizeof(new_contact->phone) - 1] = '\0';

    strncpy(new_contact->email, email, sizeof(new_contact->email) - 1);
    new_contact->email[sizeof(new_contact->email) - 1] = '\0';

    // append to end of linked list
    if(*head == NULL) {
        *head = new_contact;
    } else {
        Contact *tail = *head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = new_contact;
    }

    return;
}

// Need to traverse the array to find the contact before the contact to delete
// I'll also need the contact after the contact to delete
// so I can set src->next=target
// Need a unique value so I don't get wrong node
// Then free the target
void delete_contact(Contact** head, const char* email) {
    if(head==NULL || *head == NULL) {
        printf("function delete_contact(): Empty list\n");
        return;
    }

    Contact* current=*head;

    // head needs to be deleted
    if(strcmp(current->email,email) == 0) {
        *head = current->next;
        free(current);
        printf("function delete_contact(): Contact successfully deleted\n");
        return;
    }

    for(;current->next != NULL; current=current->next) {
        // if the next node in list is the desired one save the current one as temp
        if(strcmp(current->next->email, email) == 0) {
            Contact* node_to_delete = current->next;

            current->next=node_to_delete->next;

            // then we free node_to_delete
            free(node_to_delete);
            printf("function delete_contact(): Contact successfully deleted\n");
            return;
        }
    }
    printf("function delete_contact(): Email not found\n");
    return;
}
