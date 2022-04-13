#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"
#include "bfs.h"

struct box_2 *first_l = NULL;
struct box_2 *first_l_2 = NULL;

box_2 *new_box(int number, double length);
int peek();
void pop();
box_2 *push(int number, double length);
void clear();
box_2 *is_listed(int nb);

double dijkstra(int s, int b, int x, int y){
    int size, result = bfs(s, b, x, y);
    switch (result)
    {
    case 0:
        return 0;
        break;

    case 1:
        size = queue_size();
        clear_queue_curr();
        clear_queue();        
        break;

    case 2:
        return 2;
        break;

    case 3:
        return 3;
        break;
    
    default:
        break;
    }    
    double dist;
    int curr = s, i, j, k;
    box_2 *crafted = NULL;
    push(s, 0);
    box_2 *ptr = first_l;
    first_l_2 = first_l;
    node *tmp;
    for(k = 0; k < size; k++){
        i = curr / x;
        j = curr % y;
        tmp = graph[curr];
        if(tmp != NULL){

            if(i != 0){ // gorny - rozpatrywanie krawedzi idacej w dol
                if(tmp->value != -1.0)
                {
                    crafted = is_listed(tmp->point);
                    if(crafted != NULL)
                    {
                        if (crafted->length > (ptr->length + tmp->value))
                        {
                            crafted->length = ptr->length + tmp->value;
                            crafted->prev = ptr;
                        }
                    }
                    else
                    {
                        crafted = push(tmp->point, (ptr->length + tmp->value));
                        crafted->prev = ptr;
                    }
                    
                }
                tmp = tmp->next;
            }

            if(j+1 != y){ // lewy
                if(tmp->value != -1.0)
                {
                    crafted = is_listed(tmp->point);
                    if(crafted != NULL)
                    {
                        if (crafted->length > (ptr->length + tmp->value))
                        {
                            crafted->length = ptr->length + tmp->value;
                            crafted->prev = ptr;
                        }
                    }
                    else
                    {
                        crafted = push(tmp->point, (ptr->length + tmp->value));
                        crafted->prev = ptr;
                    }
                }
                tmp = tmp->next;
            }

            if(j != 0){ // prawy
                if(tmp->value != -1.0)
                {
                    crafted = is_listed(tmp->point);
                    if(crafted != NULL)
                    {
                        if (crafted->length > (ptr->length + tmp->value))
                        {
                            crafted->length = ptr->length + tmp->value;
                            crafted->prev = ptr;
                        }
                    }
                    else
                    {
                        crafted = push(tmp->point, (ptr->length + tmp->value));
                        crafted->prev = ptr;
                    }
                }
                tmp = tmp->next;
            }

            if(i+1 != x){ //dolny
                if(tmp->value != -1.0)
                {
                    crafted = is_listed(tmp->point);
                    if(crafted != NULL)
                    {
                        if (crafted->length > (ptr->length + tmp->value))
                        {
                            crafted->length = ptr->length + tmp->value;
                            crafted->prev = ptr;
                        }
                    }
                    else
                    {
                        crafted = push(tmp->point, (ptr->length + tmp->value));
                        crafted->prev = ptr;
                    }
                }
                tmp = tmp->next;
            }
        }
        
        pop(ptr);
        ptr = first_l;
        // zamiana obecnego wezla na pierwszy wezel w kolejce do rozpatrzenia
        curr = (ptr->number);

    }
    dist = is_listed(b)->length;
    printf("Najkrotsza sciezka miedzy punktami \"%d\" i \"%d\" ma dlugosc: %lf\n", s, b, dist);
    return dist;
}

///////////////////////////// METODY /////////////////////////////

box_2 *is_listed(int nb)
{
    if(first_l_2!=NULL)
    {
        box_2 *tmp = first_l_2;
        do
        {
            if (tmp->number == nb)
                return tmp;
            if(tmp->next!=NULL)
                tmp = tmp->next;
        }while(tmp->next!=NULL);
    }
    return 0;
}





// metoda do tworzenia nowego elementu kolejki
box_2* new_box(int number, double length)
{
    box_2* tmp = (box_2*)malloc(sizeof(box_2));
    tmp->number = number;
    tmp->length = length;
    tmp->prev = NULL;
    tmp->next = NULL;

    return tmp;
}

// metoda zwracajaca wartosc glowy
int peek()
{
    return first_l->number;
}

void clear()
{
    box_2* tmp = first_l;
    first_l = first_l->next;
    free(tmp);
}

// metoda usuwajaca element z najwyzszym priorytetem, czyli najmniejsza odlegloscia od zrodla
void pop()
{
    box_2* tmp = first_l;
    first_l = first_l->next;
}

// metoda dodajaca element do listy z uwzglednieniem jego priorytetu
box_2 *push(int number, double length)
{
    box_2* start = first_l;

    box_2* tmp = new_box(number, length);
    tmp->next = NULL;
    tmp->prev = NULL;
    if(first_l == NULL)
    {
        first_l = tmp;    
        tmp->prev = tmp;
    }
    else
    {
        // jesli glowa ma mniejszy priorytet niz nowy element
        if (first_l->length > length)
        {
            tmp->next = first_l;
            first_l = tmp;
        }
        else
        {
            while (start->next != NULL && start->next->length < length) {
                start = start->next;
            }
            tmp->next = start->next;
            start->next = tmp;
        }   
    }
    return tmp;
     
}

/*
void initialize_length(){
    int i, size = queue_size()-1;
    box_2* tmp = first_l;
    tmp->number = ->nb;
    tmp->length = 0;
    tmp->prev = tmp;
    push(tmp->number, tmp->length);
    for(i = 0; i < size; i++)
    {
        tmp->next = push(tmp_old->nb, -1);
        tmp = tmp->next;
    }
    clear_queue_curr();
    clear_queue();
}
*/