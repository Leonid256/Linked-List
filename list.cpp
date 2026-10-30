#include "list.hpp"

//----------------------------------------------------------------------------
list_stat data_init(linked_list* list)
{
    for (int i = 0; i < LIST_LEN; i++)
    {
        list -> data[i] = POIZON_VALUE;
    }

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat next_init(linked_list* list)
{
    for (int i = 0; i < LIST_LEN; i++)
    {
        list -> next[i] = -1;
    }

    list -> next[0] = 0;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat prev_init(linked_list* list)
{
    for (int i = 0; i < LIST_LEN; i++)
    {
        list -> prev[i] = -1;
    }

    list -> prev[0] = 0;
    list -> prev[1] = 0;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat print_data(linked_list* list, int line)
{
    printf("List in %d line\n", line);
    printf("#   data   next   prev\n");

    for (int i = 0; i < LIST_LEN; i++)
    {
        printf("%-3d %-6d %-6d %-6d\n", i, list -> data[i], list -> next[i], list -> prev[i]);
    }
    printf("\n");

    return LIST_OK;
}

//----------------------------------------------------------------------------
int search_free_index(linked_list* list)
{
    for (int i = 1; i < LIST_LEN; i++)
    {
        if (list -> next[i] == -1)
        {
            return i;
        }
    }

    return -1;
}

//----------------------------------------------------------------------------
list_stat push_number(linked_list* list, int value, int number)            //добавление элемента по порядковому номеру в связях
{
    int i = 0;
    while (list -> next[i] != number) i++;

    push_index(list, value, ++i);

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat push_index(linked_list* list, int value, int index)               //добавление эл-та по индексу в массиве data
{
    int free_i = search_free_index(list);
    if (free_i == -1)
        return LIST_ERROR;

    list -> data[free_i] = value;                   //запись нового значения в data

    list -> next[free_i] = index;                   //запись адреса для нового  эл-та в next
    list -> prev[free_i] = list -> prev[index];

    list -> next[list -> prev[index]]  = free_i;    //запись адреса для старого эл-та в next
    list -> prev[index] = free_i;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat pop_index(linked_list* list, int* value, int index)               //удаление эл-та по индексу в массиве data
{
    *value = list -> data[index];

    list -> next[list -> prev[index]] = list -> next[index];

    list -> prev[list -> next[index]] = list -> prev[index];

    list -> next[index] = -1;
    list -> prev[index] = -1;
    list -> data[index] = POIZON_VALUE;

    return LIST_OK;
}
