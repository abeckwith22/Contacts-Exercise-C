#include "Contacts.h"

int test(void) {
    char string[MAX_LENGTH] = {};
    char name[50] = {};
    char phone[20] = {};
    char email[50] = {};

    int contacts_size = 100;
    Contact contacts[contacts_size] = {};

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
    };

    contacts[0] = first_contact;
    contacts[1] = second_contact;
    contacts[2] = third_contact;

    Contact *cptr = contacts;

    int num_contacts = 0;

    // Add new contact
    printf("Enter new contact!\n");
    printf("Enter Name : ");
    int c_name  = get_input(name, 50);
    printf("Enter Phone: ");
    int c_phone = get_input(phone, 20);
    printf("Enter Email: ");
    int c_email = get_input(email, 50);
    
    printf("Name  : %s\n", name);
    printf("Phone : %s\n", phone);
    printf("Email : %s\n", email);
    add_contact(contacts, contacts_size, name, phone, email);
    list_contacts(contacts, contacts_size);


    printf("^ Contacts listed! ^\n");
    return 0;
}

int run(void) {
    return 0;
}

int get_input(char* result, int result_size) {
    char c;
    int i;
    // for every character user types, i increments by 1 to get string length. Also makes sure 'i' is not incremented beyond size of result string.
    for(i = 0; (c = getchar()) != EOF && c != '\n' && c != '\t' && i < result_size; i++) {
        *(i+result) = c;
    }

    return i;
}

int is_contact_empty(Contact contacts[], int index) {
    Contact *contact = &contacts[index];
    return (
        strcmp(contact->name, "")  == 0 &&
        strcmp(contact->phone, "") == 0 &&
        strcmp(contact->email, "") == 0
    );
}

void list_contacts(Contact contacts[], int contacts_size) {
    for(int i = 0; i < contacts_size && !is_contact_empty(contacts, i); i++) {
        Contact *p_contact = &contacts[i];
        printf("==========\n");
        printf("Contact #%d\n", i);
        printf("Name  : %s\n", p_contact->name);
        printf("Phone : %s\n", p_contact->phone);
        printf("Email : %s\n", p_contact->email);
    }
    return;
}

Contact get_contact(Contact contacts[], int contacts_size, int index) {
    Contact empty_contact = {
        .name="",
        .phone="",
        .email=""
    };

    if(index < 0 || index >= contacts_size) 
        return empty_contact;
    return contacts[index];
}

void add_contact(Contact contacts[], int contacts_size, char* name, char* phone, char* email) {
    // Create new contact
    Contact new_contact;

    strncpy(new_contact.name, name, sizeof(new_contact.name) - 1);
    new_contact.name[sizeof(new_contact.name) - 1] = '\0'; 
    strncpy(new_contact.phone, phone, sizeof(new_contact.phone) - 1);
    new_contact.phone[sizeof(new_contact.phone) - 1] = '\0'; 
    strncpy(new_contact.email, email, sizeof(new_contact.email) - 1);
    new_contact.email[sizeof(new_contact.email) - 1] = '\0'; 

    int i;
    // Iterate through list until empty space is detected. Found by checking if all struct members are empty.
    for(i = 0; i < contacts_size && !is_contact_empty(contacts, i); i++);

    printf("Contact_list empty @ i: %d\n", i);

    // if no space, throw error and return
    if(i+1==contacts_size) {
        printf("ERROR: Array of contacts is full.");
        return;
    }
    contacts[i] = new_contact;
    return;
}

void delete_contact(Contact contacts[], int contacts_size, int index) {
    if(index < 0 || index > contacts_size) {
        printf("Invalid index. Index out-of-bounds.");
        return;
    }

    Contact empty_contact = {
        .name="",
        .phone="",
        .email=""
    };
    contacts[index] = empty_contact;
}
