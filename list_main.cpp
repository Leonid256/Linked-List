#include "list.hpp"

//----------------------------------------------------------------------------
int main()
{
    linked_list list = {};
    int* data = NULL;
    int* next = NULL;
    int* prev = NULL;
    list.next_free = 1;


    if ((data = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.data = data;
    else return LIST_ERROR;
    if ((next = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.next = next;
    else return LIST_ERROR;
    if ((prev = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.prev = prev;
    else return LIST_ERROR;

    data_init(&list);
    next_init(&list);
    prev_init(&list);

    push_index(&list, 10, 0);
    push_index(&list, 20, 0);
    push_index(&list, 30, 0);
    push_index(&list, 40, 0);
    push_index(&list, 35, 4);
    push_number(&list, 99, 1);
    

    PRINT_DATA(&list);
}

//----------------------------------------------------------------------------
