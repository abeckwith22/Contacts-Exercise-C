#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

/* Files to test */
#include "../include/Contacts.h"

// First contact
const char* s1_name = "first1 last1";
const char* s1_phone = "123-456-7890";
const char* s1_email = "test1@email.com";

// Second contact
const char* s2_name = "first2 last2";
const char* s2_phone = "123-456-7890";
const char* s2_email = "test2@email.com";

// Third contact
const char* s3_name = "first3 last3";
const char* s3_phone = "123-456-7890";
const char* s3_email = "test3@email.com";

static int setup(void **state) {
    Contact *contacts = NULL; // start with empty linked list

    // Adds three contacts before tests
    add_contact(&contacts, s1_name, s1_phone, s1_email);
    add_contact(&contacts, s2_name, s2_phone, s2_email);
    add_contact(&contacts, s3_name, s3_phone, s3_email);

    *state = contacts;

    return 0;
}

static int teardown(void **state) {
    Contact *current = *state;
    Contact *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;

}

static void test_memory_setup(void **state) {
    Contact *context = *state;
    assert_non_null(context);
}

static void test_name_equals(void **state) {
    Contact *context = *state;
    assert_int_equal(strcmp(context->name, s1_name), 0);
}
static void test_phone_equals(void **state) {
    Contact *context = *state;
    assert_int_equal(strcmp(context->phone, s1_phone), 0);
}

static void test_email_equals(void **state) {
    Contact *context = *state;
    assert_int_equal(strcmp(context->email, s1_email), 0);
}

static void test_is_duplicate_email(void **state) {
    Contact *context = *state;
    assert_int_equal(is_duplicate_email(&context, s1_email), 1);
    assert_int_not_equal(is_duplicate_email(&context, s1_email), 0);
}

static void test_get_tail(void **state) {
    Contact *context = *state;
    assert_string_equal(get_tail(context)->name, s3_name);
    assert_string_equal(get_tail(context)->phone, s3_phone);
    assert_string_equal(get_tail(context)->email, s3_email);
}

static void test_get_contact(void **state) {
}

static void test_delete_contact(void **state) {
    Contact *context = *state;
    Contact* contact3 = context->next->next;

    assert_non_null(contact3);
    assert_int_equal(strcmp(context->next->next->email, s3_email), 0);
    delete_contact(&context, s3_email);
    // Contact3 now should not exist
    // Now running, I'm realizing I may have freed contact3 from the linked list, but that doesn't necessarily
    // mean it's set to NULL. Could have garbage values which is why I'm getting that
    // So instead do a string compare to check if s3_email is the same value as it was before
    // printf("Name  : %s\n", context->next->next->name);
    // printf("Phone : %s\n", context->next->next->phone);
    // printf("Email : %s\n", context->next->next->email);
    assert_null(context->next->next);
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_memory_setup, setup, teardown),
        cmocka_unit_test_setup_teardown(test_name_equals, setup, teardown),
        cmocka_unit_test_setup_teardown(test_phone_equals, setup, teardown),
        cmocka_unit_test_setup_teardown(test_email_equals, setup, teardown),
        cmocka_unit_test_setup_teardown(test_is_duplicate_email, setup, teardown),
        cmocka_unit_test_setup_teardown(test_get_tail, setup, teardown),
        cmocka_unit_test_setup_teardown(test_delete_contact, setup, teardown),
        
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
