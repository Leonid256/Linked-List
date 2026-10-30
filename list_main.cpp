#include "list.hpp"

//----------------------------------------------------------------------------
int main()
{
    linked_list list = {};
    int* data = NULL;
    int* next = NULL;
    int* prev = NULL;

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
    print_data(&list, __LINE__);
    push_index(&list, 20, 0);
    print_data(&list, __LINE__);
    push_index(&list, 30, 0);
    print_data(&list, __LINE__);
    push_index(&list, 40, 0);
    print_data(&list, __LINE__);
    push_index(&list, 35, 4);

    print_data(&list, __LINE__);
}

//----------------------------------------------------------------------------