#include "graph.h"

node **graph;

double find_value(node *l, int point)
{
    node *tmp=l;
    while (tmp->point!=point)
    {
        tmp=tmp->next;
    }
    return tmp->value;
}

node* add(node *l, int point, double value)
{
    if (l == NULL)
    {
        node *nw = malloc(sizeof(node*));
        nw->value = value;
        nw->point = point;
        nw->next = NULL;
        return nw;
    }
    else
    {
        node *tmp = l;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = malloc(sizeof  (node*));
        tmp->next->value = value;
        tmp->next->point = point;
        tmp->next->next = NULL;
        return l;
    }
}


void generate(int x, int y)
{
   graph = malloc(sizeof(node*) * x * y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if(j+1!=y)
                graph[i * y + j] = add(graph[i * y + j], i * y + j+1, j * 8);
            if(j!=0)
                graph[i * y + j]=add(graph[i * y + j], i * y + j-1,find_value(graph[i * y + j-1],i * y + j));
            if(i+1!=x)
                graph[i * y + j]=add(graph[i * y + j], (i+1) * y + j,i*8 );
            if(i!=0)
                graph[i * y + j]=add(graph[i * y + j], (i-1) * y + j,find_value(graph[(i-1) * y + j],i * y + j));
        }
    }
}

void graphfree(int x, int y)
{

    for (int i = 0; i < x * y; i++)
    {
        node* tmp;
        while (graph[i]->next != NULL)
        {
            tmp = graph[i];
            graph[i] = graph[i]->next;
            free(tmp);
        }
        free(graph[i]);
    }
free (graph);
}

void write (char* fname, int x, int y)
{
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            printf("%d: \n", i * y + j);
            node *tmp = graph[i * y + j];
            while (tmp != NULL) {
                printf("%d %f \n", tmp->point, tmp->value);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}