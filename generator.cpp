#include "list.hpp"

//----------------------------------------------------------------------------
FILE* open_graph_file(void)
{
    return fopen(GRAPH_FILE, "w");
}

//----------------------------------------------------------------------------
void gener_elem(linked_list* list, int index, FILE* file, const char* colour)
{
    fprintf(file, "\tnode_%d [style=filled, fillcolor=%s, label=", index, colour);
    fprintf(file, "\"{INDEX=%d | DATA=%d | {NEXT=%d | PREV=%d}}\"];\n", index,
                list -> data[index], list -> next[index], list -> prev[index]);
}

//----------------------------------------------------------------------------
void generator(linked_list* list, FILE* file)
{
    fprintf(file, "//Автоматически сгенерированный файл. Не править руками!\n");
    fprintf(file, "digraph G\n{\n");
    fprintf(file, "\trankdir=TB;\n");
    fprintf(file, "\tsplines=ortho;\n");
    fprintf(file, "\tnodesep=0.8;\n\tsize=\"12,7!\";\n\tdpi=150;\n");
    fprintf(file, "\tnode [shape=record, width=2.2, height=0.7];\n");

    gen_nodes(list, file);

    //порядок по индексам(а не по связям)
    fprintf(file, "\t{ rank=same;");
    for (int i = 0; i < LIST_LEN; i++)
        fprintf(file, " node_%d;", i);
    fprintf(file, " }\n");

    for (int i = 0; i < LIST_LEN - 1; i++)
        fprintf(file, "\tnode_%d -> node_%d [style=invis];\n", i, i + 1);

    
    //Заголовки
    generator_headlines(file);

    //Связи элементов
    gen_lines(list, file);

    //Связи с заголовками
    gen_cnct_headlines(list, file);

    fprintf(file, "}\n");
}

//----------------------------------------------------------------------------
void generator_headlines(FILE* file)
{
    fprintf(file, "\tlabel_0 [style=filled, fillcolor=lightpink, label = \"ZERO\"];\n");
    fprintf(file, "\tlabel_free [style=filled, fillcolor=lightblue, label = \"next free\"];\n");
    fprintf(file, "\tlabel_head [style=filled, fillcolor=cornsilk, label = \"head\"];\n");
    fprintf(file, "\tlabel_tail [style=filled, fillcolor=papayawhip, label = \"tail\"];\n");
}

//----------------------------------------------------------------------------
void gen_cnct_headlines(linked_list* list, FILE* file)
{
    fprintf(file, "\tlabel_0 -> node_0;\n");
    fprintf(file, "\tlabel_free -> node_%d;\n", list -> next_free);
    fprintf(file, "\tlabel_head -> node_%d;\n", list -> next[0]);
    fprintf(file, "\tlabel_tail -> node_%d;\n", list -> prev[0]);
}

//----------------------------------------------------------------------------
void gen_nodes(linked_list* list, FILE* file)
{
    for (int i = 0; i < LIST_LEN; i++)
    {
        const char* colour = "lightgrey";
        if (i == 0) colour = "lightpink";
        else if (i == list -> next_free) colour = "lightblue";
        else if (list -> prev[i] == -1) colour = "lightgreen";
        else if (i == list -> next[0]) colour = "cornsilk";
        else if (i == list -> prev[0]) colour = "papayawhip";

        gener_elem(list, i, file, colour);
    }
}

//----------------------------------------------------------------------------
void gen_lines(linked_list* list, FILE* file)
{
    for (int i = 0; i < LIST_LEN; i++)
    {
        int i_1 = i;
        int i_2 = list -> next[i];
        if ((list -> next[i_1]) == i_2 && i_1 == (list -> prev[i_2]))
        {
            fprintf(file, "\tnode_%d -> node_%d [dir=both, splines=ortho, constraint=false];\n", i_1, i_2);
        }
        else if ((list -> next[i_1]) == i_2 && i_2 != 0)
        {
            fprintf(file, "\tnode_%d -> node_%d;\n", i_1, i_2);
        }
    }
}

//----------------------------------------------------------------------------