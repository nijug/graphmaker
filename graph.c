#include "graph.h"

node **graph;

double find_value(node *l, int point)
{
    node *tmp=l;
    while (tmp->point!= point)
        tmp=tmp->next;
    return tmp->value;
}

node* add(node *l, int point, double value)
{
    if (l == NULL)
    {
        node *nw = malloc(sizeof(node));
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
        tmp->next = malloc(sizeof (node));
        tmp->next->value = value;
        tmp->next->point = point;
        tmp->next->next = NULL;
        return l;
    }
}


void generate(int x, int y, double rand1, double rand2)
{
   graph = malloc(sizeof(node*) * x * y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            graph[i * y + j]=NULL;
            if(i!=0) // górny
                graph[i * y + j]=add(graph[i * y + j], (i-1) * y + j,find_value(graph[(i-1) * y + j],i * y + j));
            if(j+1!=y) // lewy
                graph[i * y + j] = add(graph[i * y + j], i * y + j+1, rand_d(rand1, rand2));
            if(j!=0) // prawy
                graph[i * y + j]=add(graph[i * y + j], i * y + j-1,find_value(graph[i * y + j-1],i * y + j));
            if(i+1!=x) //dolny
                graph[i * y + j]=add(graph[i * y + j], (i+1) * y + j,rand_d(rand1, rand2) );

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

void Twrite_graph (int x, int y) // tylko debuggowania, wypisuje na terminal w czytelniejszym formacie
{
    fprintf(stdout,"%d %d\n",x,y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            fprintf(stdout,"%d: \n", i * y + j);
            node *tmp = graph[i * y + j];
            while (tmp != NULL)
            {
                fprintf(stdout,"%d %f \n", tmp->point, tmp->value);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}

void write_graph (char* fname, int x, int y)
{
    FILE *in= fopen(fname,"w+");
    if (in == NULL)
    {
        fprintf (stderr,"Błąd w zapisywaniu do pliku\n");
        exit (EXIT_FAILURE);
    }
    fprintf(in,"%d %d\n",x,y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            node *tmp = graph[i * y + j];
            while (tmp != NULL)
            {
                fprintf(in,"%d %f ", tmp->point, tmp->value);
                tmp = tmp->next;
            }
            fprintf(in,"\n");
        }
    }
}

void read_graph  (char *fname, int *x, int *y)
{
    FILE *in= fopen(fname,"a+");
    if (in == NULL)
    {
        fprintf (stderr,"Błąd w odczytywaniu pliku\n");
        exit (EXIT_FAILURE);
    }
    int read=fscanf(in,"%d %d",x, y);
    if (read == EOF || read != 2 )
    {
        fprintf (stderr,"Nieprawidłowy format pliku\n");
        exit (EXIT_FAILURE);
    }
    graph = malloc(sizeof(node*) * *x * *y);
    for (int i = 0; i<*x * *y ; i++)
    {

    }
}