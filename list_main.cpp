#include "list.hpp"

//----------------------------------------------------------------------------
int main()
{
    linked_list list = {};
    etype_t* data  = NULL;
    int* next      = NULL;
    int* prev      = NULL;
    list.data_size = 0;
    list.first_free = 1;
    list.free_size = LIST_LEN - 1;
    list.list_size = LIST_LEN;


    if ((data = (etype_t*) calloc(LIST_LEN, sizeof(int))) != NULL) list.data = data;
    else return LIST_NULL_PTR;
    if ((next = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.next = next;
    else return LIST_NULL_PTR;
    if ((prev = (int*) calloc(LIST_LEN, sizeof(int))) != NULL) list.prev = prev;
    else return LIST_NULL_PTR;

    data_init(&list);
    next_init(&list);
    prev_init(&list);

    FILE* graph_file = NULL;
    if ((graph_file = open_graph_file(GRAPH_FILE)) == NULL)
        return LIST_GRAPH_ERR;
    dump_begin(graph_file);

    etype_t value = 0;
    push_index(&list, 10, 0);
    push_index(&list, 20, 1);
    push_index(&list, 30, 2);
    push_index(&list, 40, 3);
    push_index(&list, 35, 4);
    push_number(&list, 99, 1);
    push_first(&list, 52);
    pop_last(&list, &value);
    // pop_index(&list, &value, -1); //SECTION: error
    pop_index(&list, &value, 2);
    pop_index(&list, &value, 3);
    push_index(&list, 30, 2);
    push_index(&list, 40, 3);
    push_index(&list, 35, 4);
    push_index(&list, 30, 2);
    push_index(&list, 40, 3);
    push_index(&list, 35, 4);
    
    // list.next[1] = 7;   //SECTION: ERROR
    // list.next[2] = 3;   //SECTION: ERROR

    //printf("%d\n", value);

    LIST_VERIFY(&list);
    
    DUMP_GENERATOR(&list, graph_file);

    dump_end(graph_file, G_global_counter);
    //PRINT_DATA(&list);
    //TODO: realloc
    //TODO: errors dump
    //TODO: неск раз вывод в html картинку

    //call_graphic_dump();

    close_graph_file(graph_file);
    list_free(&list);
}

//----------------------------------------------------------------------------
