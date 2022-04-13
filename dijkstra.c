#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"

// metoda do tworzenia nowego elementu kolejki
box_2* new_box(int number, double priority)
{
    box_2* tmp = (box_2*)malloc(sizeof(box_2));
    tmp->number = number;
    tmp->priority = priority;
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
void push(box_2** head, int number, double priority)
{
    box_2* start = (*head);

    box_2* tmp = new_box(number, priority);

    // jesli glowa ma wiekszy priorytet niz nowy element
    if ((*head)->priority > priority)
    {
        tmp->next = *head;
        (*head) = tmp;
    }
    else{
        while (start->next != NULL && start->next->priority < priority) {
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

void dijkstra(int a, int b, int x, int y)
{
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