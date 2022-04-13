#include <stdio.h>
#include <stdlib.h>

typedef struct box_2
{
    int number;
    double priority;
    struct box_2* next;
} box_2;


void dijkstra(int a, int b, int x, int y);
box_2* new_box_2(int number, double priority);
int peek(box_2** head);
void pop(box_2** head);
void push(box_2** head, int number, double priority);
int is_empty(box_2** head);

