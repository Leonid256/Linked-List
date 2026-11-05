#ifndef LIST_HPP
#define LIST_HPP

#include <stdio.h>
#include <stdlib.h>

#include "colours.hpp"

//----------------------------------------------------------------------------
const int POIZON_VALUE = 676767;
const int LIST_LEN = 10;

//----------------------------------------------------------------------------
struct linked_list
{
    int* data;
    int* next;
    int* prev;
    int next_free;
};

enum list_stat
{
    LIST_OK     = 0,
    LIST_ERROR  = 1,
};

//----------------------------------------------------------------------------
list_stat data_init(linked_list* list);
list_stat prev_init(linked_list* list);
list_stat next_init(linked_list* list);
list_stat print_data(linked_list* list, int line);

list_stat push_number(linked_list* list, int value, int number);
list_stat push_index(linked_list* list, int value, int index);
list_stat pop_index(linked_list* list, int* value, int index);

//----------------------------------------------------------------------------
#define PRINT_DATA(list) print_data(list, __LINE__) 

//----------------------------------------------------------------------------
#endif