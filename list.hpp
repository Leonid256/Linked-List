#ifndef LIST_HPP
#define LIST_HPP

#include <stdio.h>
#include <stdlib.h>

#include "colours.hpp"

typedef int etype_t;
//----------------------------------------------------------------------------
const int POIZON_VALUE = 676767;
const int LIST_LEN = 10;
const char* const GRAPH_FILE = "graph.dot";

//----------------------------------------------------------------------------
struct linked_list
{
    etype_t* data;
    size_t data_size;
    int* next;
    int* prev;
    int next_free;
    size_t free_size;
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

list_stat push_number(linked_list* list, etype_t value, int number);
list_stat push_index(linked_list* list, etype_t value, int index);
list_stat pop_index(linked_list* list, etype_t* value, int index);

list_stat push_first(linked_list* list, etype_t value);
list_stat push_last(linked_list* list, etype_t value);
list_stat pop_first(linked_list* list, etype_t* value);
list_stat pop_last(linked_list* list, etype_t* value);
list_stat list_verify(linked_list* list, int line);

void call_graphic_dump(void);
list_stat graph_dump(linked_list* list, FILE* graph_file, int line);

//graph
FILE* open_graph_file(void);
void close_graph_file(FILE* file);
void gener_elem(linked_list* list, int index, FILE* file, const char* colour);
void generator(linked_list* list, FILE* file, int line);
void generator_headlines(FILE* file);
void gen_cnct_headlines(linked_list* list, FILE* file);
void gen_nodes(linked_list* list, FILE* file);
void gen_lines(linked_list* list, FILE* file);

//----------------------------------------------------------------------------
#define PRINT_DATA(list) print_data(list, __LINE__) 
#define GRAPH_DUMP(list, graph_file) graph_dump(list, graph_file, __LINE__)
#define LIST_VERIFY(list) list_verify(list, __LINE__)

//----------------------------------------------------------------------------
#endif