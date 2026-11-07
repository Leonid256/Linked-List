#ifndef LIST_HPP
#define LIST_HPP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "colours.hpp"

typedef int etype_t;
//----------------------------------------------------------------------------
const int POIZON_VALUE = 676767;
const int LIST_LEN = 10;
const int REALLOC_SСALE = 2;
const char* const GRAPH_FILE = "graph.dot";

extern int G_global_counter;

//----------------------------------------------------------------------------
struct linked_list
{
    etype_t* data;
    size_t data_size;
    int* next;
    int* prev;
    int first_free;
    size_t free_size;
    int list_size;
};

enum list_stat
{
    LIST_OK         = 0,
    LIST_NULL_PTR   = 1,
    LIST_LEN_ERR    = 2,
    LIST_LINK_ERR   = 3,
    LIST_FREE_ERR   = 4,
    LIST_POP_ERR    = 5,
    LIST_PUSH_ERR   = 6,
    LIST_GRAPH_ERR  = 7,
    LIST_REALC_ERR  = 8,
    // LIST_ERROR  = 1,
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
void list_free(linked_list* list);

void call_graphic_dump(void);

//graph
FILE* open_graph_file(const char* const graph_file_name);
void close_graph_file(FILE* file);
void gener_elem(linked_list* list, int index, FILE* file, int count, const char* colour);
void dump_generator(linked_list* list, FILE* file, int count, int line);
void dump_begin(FILE* file);
void dump_end(FILE* file, int count);
void generator_headlines(linked_list* list, FILE* file, int count, int line);
void gen_cnct_headlines(linked_list* list, FILE* file, int count);
void gen_nodes(linked_list* list, FILE* file, int count);
void gen_lines(linked_list* list, FILE* file, int count);

//----------------------------------------------------------------------------
#define PRINT_DATA(list) print_data(list, __LINE__) 
#define DUMP_GENERATOR(list, file)                          \
{                                                           \
    G_global_counter++;                                     \
    dump_generator(list, file, G_global_counter, __LINE__); \
}
#define LIST_VERIFY(list) list_verify(list, __LINE__)

//----------------------------------------------------------------------------
#endif