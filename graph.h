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
