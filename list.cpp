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
    list -> next[0] = 0;

    for (int i = 1; i < LIST_LEN - 1; i++)
    {
        list -> next[i] = i + 1;
    }

    list -> next[LIST_LEN - 1] = 0;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat prev_init(linked_list* list)
{
    for (int i = 1; i < LIST_LEN; i++)
    {
        list -> prev[i] = -1;
    }

    list -> prev[0] = 0;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat print_data(linked_list* list, int line)
{
    printf("List in %d line\n", line);
    printf("#   data   next   prev\n");

    for (int i = 0; i < LIST_LEN; i++)
    {
        printf("%-3d %-6d %-6d %-6d", i, list -> data[i], list -> next[i], list -> prev[i]);
        if (i == list -> next_free)
            printf("   <- next free");
        printf("\n");
    }
    printf("\n");

    return LIST_OK;
}

//----------------------------------------------------------------------------
int search_free_index(linked_list* list)    //NOTE: относительно бесполезная функция
{
    for (int i = 1; i < LIST_LEN; i++)
    {
        if (list -> prev[i] == -1)
        {
            return i;
        }
    }

    return -1;
}

//----------------------------------------------------------------------------
list_stat push_number(linked_list* list, etype_t value, int number)            //добавление элемента по порядковому номеру в связях
{
    if (number >= LIST_LEN || number < 0)
    {
        printf(RED "Error: attempt to pop by the wrong number\n" CRESET);
        return LIST_ERROR;
    }

    int i = 0;
    for (int k = 0; k < number - 1; k++)
    {
        i = list -> next[i];
        if (i == 0)
            return LIST_ERROR;
    }

    return push_index(list, value, list -> next[i]);
}

//----------------------------------------------------------------------------
list_stat push_index(linked_list* list, etype_t value, int index)               //добавление эл-та по индексу в массиве data
{
    int free_i = list -> next_free;
    if (free_i == 0)
    {
        printf(RED "ERROR: list is overfull. Addition is not possible\n" CRESET);
        return LIST_ERROR;
    }
    else if (index >= LIST_LEN || index < 0)
    {
        printf(RED "Error: attempt to pop by the wrong index\n" CRESET);
        return LIST_ERROR;
    }

    list -> next_free = list -> next[free_i];
    list -> data[free_i] = value;

    list -> prev[free_i] = index;
    list -> next[free_i] = list -> next[index];

    list -> prev[list -> next[index]]  = free_i;
    list -> next[index] = free_i;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat pop_index(linked_list* list, etype_t* value, int index)               //удаление эл-та по индексу в массиве data
{
    if (index == 0)
    {
        printf(RED "Error: attempt to pop the first(special) element\n" CRESET);
        return LIST_ERROR;
    }
    else if (index >= LIST_LEN || index < 0)
    {
        printf(RED "Error: attempt to pop by the wrong index\n" CRESET);
        return LIST_ERROR;
    }

    *value = list -> data[index];

    list -> next[list -> prev[index]] = list -> next[index];
    list -> prev[list -> next[index]] = list -> prev[index];

    list -> next[index] = list -> next_free;
    list -> prev[index] = -1;
    list -> data[index] = POIZON_VALUE;

    list -> next_free = index;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat push_first(linked_list* list, etype_t value)      //push на первое место
{
    int index = list -> next[0];

    return push_index(list, value, index - 1);
}

//----------------------------------------------------------------------------
list_stat push_last(linked_list* list, etype_t value)       //push на последнее место
{
    int index = list -> prev[0];

    return push_index(list, value, index);
}

//----------------------------------------------------------------------------
list_stat pop_first(linked_list* list, etype_t* value)      //pop с первого места
{
    int index = list -> next[0];

    return pop_index(list, value, index);
}

//----------------------------------------------------------------------------
list_stat pop_last(linked_list* list, etype_t* value)       //pop с последнего места
{
    int index = list -> prev[0];

    return pop_index(list, value, index);
}

//----------------------------------------------------------------------------
void graphic_dump(void)
{
    system("./graph_hui.sh");
    system("open graph.png");
}
