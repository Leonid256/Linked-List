#include "list.hpp"

//----------------------------------------------------------------------------
int main()
{
    linked_list list = {};
    etype_t* data = NULL;
    int* next     = NULL;
    int* prev     = NULL;
    list.next_free = 1;


    if ((data = (etype_t*) calloc(LIST_LEN, sizeof(int))) != NULL) list.data = data;
    else return LIST_ERROR;
    if ((next = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.next = next;
    else return LIST_ERROR;
    if ((prev = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.prev = prev;
    else return LIST_ERROR;

    data_init(&list);
    next_init(&list);
    prev_init(&list);

    etype_t value = 0;
    push_index(&list, 10, 0);
    push_index(&list, 20, 1);
    push_index(&list, 30, 2);
    push_index(&list, 40, 3);
    push_index(&list, 35, 4);
    push_number(&list, 99, 1);
    push_first(&list, 52);
    pop_last(&list, &value);
    //pop_index(&list, &value, -1);

    //printf("%d\n", value);
    
    FILE* graph_file = NULL;
    if ((graph_file = open_graph_file()) == NULL)
        return LIST_ERROR;

    generator(&list, graph_file);

    close_graph_file(graph_file);

    PRINT_DATA(&list);
    graphic_dump();
}

//----------------------------------------------------------------------------
