#include "list.hpp"

//----------------------------------------------------------------------------
FILE* open_graph_file(const char* const graph_file_name)
{
    return fopen(graph_file_name, "w");
}

//----------------------------------------------------------------------------
void close_graph_file(FILE* file)
{
    assert(file != NULL);

    fclose(file);
}

//----------------------------------------------------------------------------
void gener_elem(linked_list* list, int index, FILE* file, int count, const char* colour)
{
    assert(list != NULL);
    assert(file != NULL);

    fprintf(file, "\tnode_%d_%d [pos = \"%d,%d!\", style = filled, fillcolor = %s, label = ",
                index, count, index * 3, -count * 6, colour);    
    fprintf(file, "\"{INDEX = %d | DATA = %d | {NEXT = %d | PREV = %d}}\"];\n", index,
                list -> data[index], list -> next[index], list -> prev[index]);
}

//----------------------------------------------------------------------------
void dump_generator(linked_list* list, FILE* file, int count, int line)
{
    assert(list != NULL);
    assert(file != NULL);

    gen_nodes(list, file, count);

    //порядок по индексам(а не по связям)
    for (int i = 0; i < list -> list_size; i++)
        fprintf(file, " node_%d_%d;", i, count);
    
    //Заголовки
    generator_headlines(list, file, count, line);

    //Связи элементов
    gen_lines(list, file, count);

    //Связи с заголовками
    gen_cnct_headlines(list, file, count);
}

//----------------------------------------------------------------------------
void dump_begin(FILE* file)
{
    fprintf(file, "//Автоматически сгенерированный файл. Не править руками!\n");
    fprintf(file, "digraph G\n{\n");
    fprintf(file, "\tsplines = ortho;\n");
    //fprintf(file, "\tsplines = true;\n"); //не проходит сквозь, но не прямые углы
    fprintf(file, "\tnode [shape = record, width = 2.2, height = 0.7];\n");
}

//----------------------------------------------------------------------------
void dump_end(FILE* file, int count)
{
    (void) count;
    fprintf(file, "}\n");
}

//----------------------------------------------------------------------------
void generator_headlines(linked_list* list, FILE* file, int count, int line)
{
    double y = -count * 6.0 + 1.6;   // подписи над строкой узлов

    fprintf(file, "\ttitle_%d [shape = plaintext, fontsize = 24, pos = \"1,%.1f!\", label = \"Graph dump %d(%d line)\"];\n",
            count, y + 1.6, count, line);
    fprintf(file, "\tlabel_0_%d [width = 0.9, style = filled, fillcolor = lightpink, pos = \"0,%.1f!\", label = \"ZERO\"];\n",
            count, y);
    fprintf(file, "\tlabel_free_%d [width = 0.9, style = filled, fillcolor = lightgreen, pos = \"%d,%.1f!\", label = \"first free\"];\n",
            count, list -> first_free * 3, y);
    fprintf(file, "\tlabel_head_%d [width = 0.9, style = filled, pos = \"%.1f,%.1f!\", label = \"head\"];\n",
            count, list -> next[0] * 3 - 1.0, y);
    fprintf(file, "\tlabel_tail_%d [width = 0.9, style = filled, pos = \"%.1f,%.1f!\", label = \"tail\"];\n",
            count, list -> prev[0] * 3 + 1.0, y);
}

//----------------------------------------------------------------------------
void gen_cnct_headlines(linked_list* list, FILE* file, int count)
{
    assert(list != NULL);
    assert(file != NULL);

    fprintf(file, "\tlabel_0_%d -> node_0_%d;\n", count, count);
    fprintf(file, "\tlabel_free_%d -> node_%d_%d;\n", count, list -> first_free, count);
    fprintf(file, "\tlabel_head_%d -> node_%d_%d;\n", count, list -> next[0], count);
    fprintf(file, "\tlabel_tail_%d -> node_%d_%d;\n", count, list -> prev[0], count);
}

//----------------------------------------------------------------------------
void gen_nodes(linked_list* list, FILE* file, int count)
{
    assert(list != NULL);
    assert(file != NULL);

    for (int i = 0; i < list -> list_size; i++)
    {
        int i_1 = i;
        int i_2 = list -> next[i];

        const char* colour = "lightgrey";
        if (i == 0) colour = "lightpink";
        else if ((list -> prev[i_1]) == -1 && (list -> prev[i_2]) != -1 && list -> next[i_1] != 0) colour = "red";
        else if ((list -> next[i_1]) == i_2 && (list -> next[i_2]) == i_1 && 
                list -> prev[i_1] == -1 && list -> prev[i_2] == -1) colour = "red";
        else if (i == list -> first_free) colour = "lightgreen";
        else if (list -> prev[i_1] == -1 && list -> prev[i_2] == -1) colour = "lightgreen";
        else if (list -> prev[i_1] == -1 && list -> next[i_1] == 0) colour = "lightgreen";
        else if ((list -> next[i_1]) != i_2 || (list -> prev[i_2]) != i_1) colour = "red";

        gener_elem(list, i, file, count, colour);
    }
}

//----------------------------------------------------------------------------
void gen_lines(linked_list* list, FILE* file, int count)
{
    assert(list != NULL);
    assert(file != NULL);

    for (int i = 0; i < list -> list_size; i++)
    {
        int i_1 = i;
        int i_2 = list -> next[i];
        if ((list -> next[i_1]) == i_2 && i_1 == (list -> prev[i_2]))
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [dir = both, constraint = false];\n", i_1, count, i_2, count);
        }
        else if ((list -> next[i_1]) == i_2 && (list -> next[i_2]) == i_1 && 
                list -> prev[i_1] == -1 && list -> prev[i_2] == -1)
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [color = red, constraint = false, penwidth = 4, arrowsize = 1.3];\n", i_1, count, i_2, count);
        }
        else if ((list -> next[i_1]) == i_2 && i_2 != 0 && (list -> prev[i_1]) == -1 && (list -> prev[i_2]) == -1)
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [color = green, constraint = false, penwidth = 2, arrowsize = 1.3];\n", i_1, count, i_2, count);
        }
        else if ((list -> next[i_1]) != 0)
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [color = red, constraint = false, penwidth = 4, arrowsize = 1.3];\n", i_1, count, i_2, count);
        }
    }
}

//----------------------------------------------------------------------------