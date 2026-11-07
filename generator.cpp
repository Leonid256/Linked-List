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
void gener_elem(linked_list* list, int index, FILE* file, int line, const char* colour)
{
    assert(list != NULL);
    assert(file != NULL);

    fprintf(file, "\tnode_%d_%d [pos = \"%d,%d!\", style = filled, fillcolor = %s, label = ",
                index, line, index * 3, -line * 6, colour);    
    fprintf(file, "\"{INDEX = %d | DATA = %d | {NEXT = %d | PREV = %d}}\"];\n", index,
                list -> data[index], list -> next[index], list -> prev[index]);
}

//----------------------------------------------------------------------------
void dump_generator(linked_list* list, FILE* file, int line)
{
    assert(list != NULL);
    assert(file != NULL);

    // fprintf(file, "\tsubgraph cluster_%d {\n", line);
    //fprintf(file, "\t\tlabel = \"Graph dump %d\"; labelloc = t; labeljust = l; fontsize = 24;\n", line);

    gen_nodes(list, file, line);

    //порядок по индексам(а не по связям)
    //fprintf(file, "\t{ rank = same;");
    for (int i = 0; i < LIST_LEN; i++)
        fprintf(file, " node_%d_%d;", i, line);
    // fprintf(file, " }\n");

    // for (int i = 0; i < LIST_LEN - 1; i++)
    //     fprintf(file, "\tnode_%d_%d -> node_%d_%d [style = invis];\n", i, line, i + 1, line);

    
    //Заголовки
    generator_headlines(list, file, line);

    //Связи элементов
    gen_lines(list, file, line);

    //Связи с заголовками
    gen_cnct_headlines(list, file, line);

    //fprintf(file, "\t}\n");
}

//----------------------------------------------------------------------------
void dump_begin(FILE* file)
{
    fprintf(file, "//Автоматически сгенерированный файл. Не править руками!\n");
    fprintf(file, "digraph G\n{\n");
    fprintf(file, "\tsplines = ortho;\n");
    fprintf(file, "\tnode [shape = record, width = 2.2, height = 0.7];\n");
}

//----------------------------------------------------------------------------
void dump_end(FILE* file, int count)
{
    // for (int g = 1; g < count; g++)
    // {
    //     for (int i = 0; i < LIST_LEN; i++)
    //         fprintf(file, "\tnode_%d_%d -> node_%d_%d [style = invis, weight = 100, minlen = 3];\n", i, g, i, g + 1);
    // }
    (void) count;
    fprintf(file, "}\n");
}

//----------------------------------------------------------------------------
// void generator_headlines(FILE* file, int line)
// {
//     assert(file != NULL);

//     fprintf(file, "\tlabel_0_%d [style = filled, fillcolor = lightpink, label = \"ZERO\"];\n", line);
//     fprintf(file, "\tlabel_free_%d [style = filled, fillcolor = lightblue, label = \"first free\"];\n", line);
//     fprintf(file, "\tlabel_head_%d [style = filled, fillcolor = cornsilk, label = \"head\"];\n", line);
//     fprintf(file, "\tlabel_tail_%d [style = filled, fillcolor = papayawhip, label = \"tail\"];\n", line);

//     fprintf(file, "\t{ rank = same; label_0_%d; label_free_%d; label_head_%d; label_tail_%d; }\n",
//                 line, line, line, line);
// }
void generator_headlines(linked_list* list, FILE* file, int line)
{
    double y = -line * 6.0 + 1.6;   // подписи над строкой узлов

    fprintf(file, "\ttitle_%d [shape = plaintext, fontsize = 24, pos = \"1,%.1f!\", label = \"Graph dump %d\"];\n",
            line, y + 1.6, line);
    fprintf(file, "\tlabel_0_%d [width = 0.9, style = filled, fillcolor = lightpink, pos = \"0,%.1f!\", label = \"ZERO\"];\n",
            line, y);
    fprintf(file, "\tlabel_free_%d [width = 0.9, style = filled, fillcolor = lightgreen, pos = \"%d,%.1f!\", label = \"first free\"];\n",
            line, list -> first_free * 3, y);
    fprintf(file, "\tlabel_head_%d [width = 0.9, style = filled, pos = \"%.1f,%.1f!\", label = \"head\"];\n",
            line, list -> next[0] * 3 - 1.0, y);
    fprintf(file, "\tlabel_tail_%d [width = 0.9, style = filled, pos = \"%.1f,%.1f!\", label = \"tail\"];\n",
            line, list -> prev[0] * 3 + 1.0, y);
}

//----------------------------------------------------------------------------
void gen_cnct_headlines(linked_list* list, FILE* file, int line)
{
    assert(list != NULL);
    assert(file != NULL);

    fprintf(file, "\tlabel_0_%d -> node_0_%d;\n", line, line);
    fprintf(file, "\tlabel_free_%d -> node_%d_%d;\n", line, list -> first_free, line);
    fprintf(file, "\tlabel_head_%d -> node_%d_%d;\n", line, list -> next[0], line);
    fprintf(file, "\tlabel_tail_%d -> node_%d_%d;\n", line, list -> prev[0], line);
}

//----------------------------------------------------------------------------
void gen_nodes(linked_list* list, FILE* file, int line)
{
    assert(list != NULL);
    assert(file != NULL);

    for (int i = 0; i < LIST_LEN; i++)
    {
        const char* colour = "lightgrey";
        if (i == 0) colour = "lightpink";
        else if (i == list -> first_free) colour = "lightgreen";
        else if (list -> prev[i] == -1) colour = "lightgreen";

        gener_elem(list, i, file, line, colour);
    }
}

//----------------------------------------------------------------------------
void gen_lines(linked_list* list, FILE* file, int line)
{
    assert(list != NULL);
    assert(file != NULL);

    for (int i = 0; i < LIST_LEN; i++)
    {
        int i_1 = i;
        int i_2 = list -> next[i];
        if ((list -> next[i_1]) == i_2 && i_1 == (list -> prev[i_2]))
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [dir = both, constraint = false];\n", i_1, line, i_2, line);
        }
        else if ((list -> next[i_1]) == i_2 && i_2 != 0 && (list -> prev[i_1]) == -1 && (list -> prev[i_2]) == -1)
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [color = green, constraint = false, penwidth = 2, arrowsize = 1.3];\n", i_1, line, i_2, line);
        }
        else if ((list -> prev[i_1]) != -1 && (list -> prev[i_2]) != -1)
        {
            fprintf(file, "\tnode_%d_%d -> node_%d_%d [color = red, constraint = false, penwidth = 4, arrowsize = 1.3];\n", i_1, line, i_2, line);
        }
    }
}

//----------------------------------------------------------------------------