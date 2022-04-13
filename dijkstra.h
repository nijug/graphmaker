#include <stdio.h>
#include <stdlib.h>

typedef struct box_2
{
    int number;
    double length;
    struct box_2* prev;
    struct box_2* next;
} box_2;


double dijkstra(int a, int b, int x, int y);
box_2 *new_box_2(int number, double length);
int peek();
void pop();
box_2 *push(int number, double length);
void clear();
box_2 *is_listed(int nb);