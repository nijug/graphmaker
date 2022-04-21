#include "utilities.h"

typedef struct e
{
    // waga krawędzi
    double value;
    // numer sąsiedniego węzła
    int point;
    // wskaźnik na następny
    struct e *next;
} node;

typedef struct lista_c
{
    // numer wezla
    int value;
    // wskaźnik na następny
    struct lista_c *next;
} lista_c;

extern node **graph;
node **Fgraph;

double find_value(node *l, int point);
void delete(node *l, int point, double value );
int v_count(node *l,double value);
node* add(node *l, int point, double value);
void generate(int x, int y, double rand1, double rand2);
void Fgenerate(int x, int y);
void graphfree(int x, int y);
void Fgraphfree(int x, int y);
void write_graph (char* fname, int x, int y, int n);
void Twrite_graph(int x, int y);
void read_graph(char* fname, int *x, int *y);
void divider(int x, int y, int n);
int edgy(int a, int x, int y);
int first_edgy(int a, int y);
void add_to_path(int a);
int is_in_path(int a);
int valid(int a, int x, int y);
void cut_graph(int y, int x);

// funkcje dla list
void dequeue_c();
int in_queue_c(int val);
int queue_size_c();
void enqueue_c(int val);
void clear_queue_c();


/*lista_c *new_lista_c_el(int number, double length);
void pop_lista_c();
lista_c *add_to_path(int number, double length);
void clear_lista_c();
void listel_destroy();
lista_c *is_in_path(int nb);
*/