#include <stdio.h>
#include "graph.h"

struct box
{
    // numer wezla
    int nb;
    // wskaznik na nastepny wezel
    struct box *next;
};

void enqueue(int number);
void dequeue();
int in_queue(int number);
int queue_size();
void enqueue_curr(int number);
void dequeue_curr();
int in_queue_curr(int number);
void clear_queue();
void clear_queue_curr();
int bfs(int a, int b, int x, int y);