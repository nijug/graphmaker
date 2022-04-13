#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "bfs.h"

typedef struct box_2
{
    // numer wezla
    int number;
    // dlugosc najkrotszej drogi wezla od zrodla
    double length;
    // wskaznik na wezel poprzedzajacy ten wezel w najkrotszej drodze do zrodla
    struct box_2* prev;
    // wskaznik na nastepny element listy
    struct box_2* next;
} box_2;

double dijkstra(int a, int b, int x, int y);
box_2 *new_box(int number, double length);
void pop();
box_2 *push(int number, double length);
void clear();
box_2 *is_listed(int nb);