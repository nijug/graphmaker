#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"

struct box *first_l = NULL;
struct box *last_l = NULL;

box_2* new_box(int number, double length);
int peek(box_2** head);
void pop(box_2** head);
void push(box_2** head, int number, double length);
int is_empty(box_2** head);

int dijkstra(int a, int b, int x, int y)
{
    return bfs(0, 0, 4, 4);
    box_2* pq = new_box(4, 1);
    push(&pq, 5, 2);
    push(&pq, 6, 3);
    push(&pq, 7, 0);

    while(!is_empty(&pq))
    {
        printf("%d ", peek(&pq));
        pop(&pq);
    }
}

///////////////////////////// METODY /////////////////////////////

// metoda do tworzenia nowego elementu kolejki
box_2* new_box(int number, double length)
{
    box_2* tmp = (box_2*)malloc(sizeof(box_2));
    tmp->number = number;
    tmp->length = length;
    tmp->next = NULL;

    return tmp;
}

// metoda zwracajaca wartosc glowy
int peek(box_2** head)
{
    return(*head)->number;
}

// metoda usuwajaca element z najnizszym priorytetem
void pop(box_2** head)
{
    box_2* tmp = *head;
    (*head) = (*head)->next;
    free(tmp);
}

// metoda dodajaca element do listy z uwzglednieniem jego priorytetu
void push(box_2** head, int number, double length)
{
    box_2* start = (*head);

    box_2* tmp = new_box(number, length);

    // jesli glowa ma wiekszy priorytet niz nowy element
    if ((*head)->length > length)
    {
        tmp->next = *head;
        (*head) = tmp;
    }
    else{
        while (start->next != NULL && start->next->length < length) {
            start = start->next;
        }
        tmp->next = start->next;
        start->next = tmp;
    }    
}

int is_empty(box_2** head)
{
    return (*head) == NULL;
}

void initialize_length(){
    queue_size();
}