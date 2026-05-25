#include "linkedlist.h" // Include the user-defined header file for the list data structure.
#include <stdio.h>

int main(void)
{
    LinkedList *l1; // Declare a pointer to a linked list.
    LinkedList *l2;

    l1 = ll_create(); // Create an empty linked list and assign its pointer to 'l1'.
    for (int i = 0; i < 10; i++)
        ll_insert(l1, i); // Insert elements into the list using ll_insert.
    ll_print(l1);         // Show the elements of the list using ll_print.
    printf("------------\n\n");

    l2 = ll_create(); // Create an empty linked list and assign its pointer to 'l2'.
    for (int i = 20; i < 35; i++)
        ll_insert(l2, i); // Insert elements into the list using ll_insert.
    ll_print(l2);         // Show the elements of the list using ll_print.

    LinkedList *l3 = ll_concatenate(l1, l2); // Concatenate the two lists l1 and l2 using ll_concatenate.
    printf("------------\n\n");
    ll_print(l3); // Show the elements of the concatenated list using ll_print.

    ll_free(l1);
    ll_free(l2);
    ll_free(l3);

    return 0; // Return 0 to indicate successful program execution.
}