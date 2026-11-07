#include "list.hpp"

int G_global_counter = 0;

//----------------------------------------------------------------------------
list_stat data_init(linked_list* list)
{
    for (int i = 0; i < list -> list_size; i++)
    {
        list -> data[i] = POIZON_VALUE;
    }

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat next_init(linked_list* list)
{
    list -> next[0] = 0;

    for (int i = 1; i < list -> list_size - 1; i++)
    {
        list -> next[i] = i + 1;
    }

    list -> next[list -> list_size - 1] = 0;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat prev_init(linked_list* list)
{
    for (int i = 1; i < list -> list_size; i++)
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

    for (int i = 0; i < list -> list_size; i++)
    {
        printf("%-3d %-6d %-6d %-6d", i, list -> data[i], list -> next[i], list -> prev[i]);
        if (i == list -> first_free)
            printf("   <- next free");
        printf("\n");
    }
    printf("\n");

    return LIST_OK;
}

//----------------------------------------------------------------------------
int search_free_index(linked_list* list)    //NOTE: относительно бесполезная функция
{
    for (int i = 1; i < list -> list_size; i++)
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
    if (number >= list -> list_size || number < 0)
    {
        printf(RED "Error: attempt to push by the wrong number\n" CRESET);
        return LIST_PUSH_ERR;
    }
    

    int i = 0;
    for (int k = 0; k < number - 1; k++)
    {
        i = list -> next[i];
        if (i == 0)
            return LIST_PUSH_ERR;
    }

    return push_index(list, value, list -> next[i]);
}

//----------------------------------------------------------------------------
list_stat push_index(linked_list* list, etype_t value, int index)               //добавление эл-та по индексу в массиве data
{
    if (index >= list -> list_size || index < 0 || list -> prev[index] == -1)
    {
        printf(RED "Error: attempt to push by the wrong index\n" CRESET);
        return LIST_PUSH_ERR;
    }
    else if (list -> free_size == 0)
    {
        list_stat st = LIST_VERIFY(list);
        if (st != LIST_OK) return st;

        int old_size = list -> list_size;
        int new_size = old_size * REALLOC_SСALE;

        etype_t* new_data = (etype_t*) realloc(list -> data, (size_t)new_size * sizeof(etype_t));
        if (new_data == NULL) return LIST_REALC_ERR;
        list -> data = new_data;

        int* new_next = (int*) realloc(list -> next, (size_t)new_size * sizeof(int));
        if (new_next == NULL) return LIST_REALC_ERR;
        list -> next = new_next;

        int* new_prev = (int*) realloc(list -> prev, (size_t)new_size * sizeof(int));
        if (new_prev == NULL) return LIST_REALC_ERR;
        list -> prev = new_prev;

        for (int i = old_size; i < new_size; i++)
        {
            list -> data[i] = POIZON_VALUE;
            list -> prev[i] = -1;
            list -> next[i] = (i + 1 < new_size) ? i + 1 : 0;
        }

        list -> first_free = old_size;
        list -> free_size  = (size_t)(new_size - old_size);
        list -> list_size  = new_size;
    }
    int free_i = list -> first_free;

    list -> first_free = list -> next[free_i];
    list -> data[free_i] = value;

    list -> prev[free_i] = index;
    list -> next[free_i] = list -> next[index];

    list -> prev[list -> next[index]]  = free_i;
    list -> next[index] = free_i;

    list -> free_size--;
    list -> data_size++;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat pop_index(linked_list* list, etype_t* value, int index)               //удаление эл-та по индексу в массиве data
{
    if (index == 0)
    {
        printf(RED "Error: attempt to pop the first(special) element\n" CRESET);
        return LIST_POP_ERR;
    }
    else if (index >= list -> list_size || index < 0 || list -> data_size == 0)
    {
        printf(RED "Error: attempt to pop by the wrong index\n" CRESET);
        return LIST_POP_ERR;
    }
    else if (list -> prev[index] == -1)
    {
        printf(RED "Error: attempt to pop a free element\n" CRESET);
        return LIST_POP_ERR;
    }

    *value = list -> data[index];

    list -> next[list -> prev[index]] = list -> next[index];
    list -> prev[list -> next[index]] = list -> prev[index];

    list -> next[index] = list -> first_free;
    list -> prev[index] = -1;
    list -> data[index] = POIZON_VALUE;

    list -> first_free = index;

    list -> free_size++;
    list -> data_size--;

    return LIST_OK;
}

//----------------------------------------------------------------------------
list_stat push_first(linked_list* list, etype_t value)      //push на первое место
{
    int index = list -> next[0];

    return push_index(list, value, index);
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
list_stat list_verify(linked_list* list, int line)
{
    if (list -> next == NULL || list -> prev == NULL || list -> data == NULL)
    {
        printf(RED "Error in verify in %d line: list ptr = NULL\n" CRESET, line);
        return LIST_NULL_PTR;
    }
    if ((int)(list -> data_size + list -> free_size + 1) != list -> list_size)
    {
        printf(RED "Error in verify in %d line: data_size + free_size != list -> list_size\n" CRESET, line);
        return LIST_LEN_ERR;
    }

    //проверка закольцованности data
    bool ring_check = false;
    int current = 0;
    for (size_t i = 0; (int)i < list -> list_size; i++)
    {
        int nxt = list -> next[current];
        if (nxt < 0 || nxt >= list -> list_size)     break;
        if (list -> prev[nxt] != current)   break;
        if (nxt == 0)
        {
            ring_check = true;
            if (i != list -> data_size)
            {
                printf(RED "Error in verify in %d line: data size is wrong\n" CRESET, line);
                printf(RED "(data = %zu || data_size = %zu)\n" CRESET, i, list -> data_size);
                return LIST_LEN_ERR;
            }
            break;
        }
        current = nxt;
    }
    if (!ring_check)
    {
        printf(RED "Error in verify in %d line: data not linked\n" CRESET, line);
        return LIST_LINK_ERR;
    }

    //проверка связей free
    int free_count = 0;
    current = list -> first_free;
    while (current != 0 && free_count <= list -> list_size)
    {
        if (current < 0 || current >= list -> list_size || list -> prev[current] != -1)
        {
            printf(RED "Error in verify in %d line: free not linked (bad element %d)\n" CRESET, line, current);
            return LIST_LINK_ERR;
        }
        current = list -> next[current];
        free_count++;
    }
    if (current != 0)
    {
        printf(RED "Error in verify in %d line: free chain is cyclic\n" CRESET, line);
        return LIST_LINK_ERR;
    }
    if ((size_t)free_count != list -> free_size)
    {
        printf(RED "Error in verify in %d line: free size is wrong\n" CRESET, line);
        printf(RED "(free = %d || free_size = %zu)\n" CRESET, free_count, list -> free_size);
        return LIST_FREE_ERR;
    }

    printf("List verify finished with no errors in %d line\n", line);
    return LIST_OK;
}

//----------------------------------------------------------------------------
void call_graphic_dump(void)
{
    system("./graph_hui.sh");
    system("open graph.png");
}

//----------------------------------------------------------------------------
void list_free(linked_list* list)
{
    free(list -> data);
    free(list -> prev);
    free(list -> next);

    list -> data = NULL;
    list -> prev = NULL;
    list -> next = NULL;
}

//----------------------------------------------------------------------------
