#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"

typedef struct e
{
    double value;
    int point;
    struct e *next;
} node;

extern node **graph;

double find_value(node *l, int point);
node* add(node *l, int point, double value);
void generate(int x, int y, double rand1, double rand2);
void graphfree(int x, int y);
void write (char* fname, int x, int y);
