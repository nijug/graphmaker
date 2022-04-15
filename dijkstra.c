#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "bfs.h"
#include "dijkstra.h"

struct box_2 *first_l = NULL;
struct box_2 *first_l_2 = NULL;

double dijkstra(int s, int b, int x, int y){
    int size, result = bfs(s, b, x, y);
    
    switch (result)
    {
        case 0:
            return 0;
            break;

        case 1:
            size = queue_size();
            //clear_queue_curr();
            clear_queue();        
            break;

        case 2:
            return 2;
            break;

        case 3:
            return 3;
            break;
    } 

    double dist;
    int curr = s, i, j, k;
    box_2 *crafted = NULL;
    push(s, 0);
    box_2 *ptr = first_l;
    first_l_2 = first_l;
    node *tmp;

    // petla powtarza sie tyle razy ile wezlow bfs znalazl w tej czesci grafu
    for(k = 0; k < size; k++){
        i = curr / y;
        j = curr % y;
        tmp = graph[curr];
        if(tmp != NULL){

            if(i != 0){ // gorny - rozpatrywanie krawedzi idacej w gore
                if(tmp->value != -1.0)
                {
                    // sprawdzenie czy wskazywany wezel jest juz w liscie wezlow 
                    // (tej zawierajacej wezly rozpatrzone i nie)
                    crafted = is_listed(tmp->point);
                    // przypadek gdy wskazywany wezel juz znajduje sie w liscie
                    if(crafted != NULL)
                    {
                        // jesli droga do wskazywanego wezla jest dluzsza od obecnie rozpatrywanej drogi
                        // to nastepuje zamiana wartosci jej dlugosci oraz poprzednika wskazywanego wezla
                        if (crafted->length > (ptr->length + tmp->value))
                        {
                            crafted->length = ptr->length + tmp->value;
                            crafted->prev = ptr;
                        }
                    }
                    else
                    {
                        // jesli wskazywany wezel nie byl wczesniej dodany do listy, 
                        // to zostaje on dodany, i jako poprzednika w najkrotszej drodze od zrodla
                        // wskazuje obecnie rozpatrywany wezel
                        crafted = push(tmp->point, (ptr->length + tmp->value));
                        crafted->prev = ptr;
                    }
                    
                }
                tmp = tmp->next;
            }

            if(j+1 != y){ // prawy - rozpatrywanie krawedzi idacej w prawo
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

            if(j != 0){ // lewy - rozpatrywanie krawedzi idacej w prawo
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

            if(i+1 != x){ // dolny - rozpatrywanie krawedzi idacej w dol
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

        // zamiana numeru obecnego wezla na numer pierwszego wezla w kolejce do rozpatrzenia (priorytetowej)
        curr = (ptr->number);

    }
    // jesli szukamy najkrotzej sciezki miedzy dwoma wezlami i algorytm bfs wykazal, 
    // ze przynajmniej jedna taka sciezka istnieje, to ta metoda zwraca jej dlugosc
    dist = is_listed(b)->length;
    printf("Najkrotsza sciezka miedzy punktami \"%d\" i \"%d\" ma dlugosc: %lf\n", s, b, dist);
    show_path(b);
    clear_list();
    return dist;
}

///////////////////////////// METODY /////////////////////////////

// funkcja pozwalajaca sprawdzic czy w liscie znajduje sie wezel o wskazanym numerze
// funkcja zaczyna sprawdzanie od poczatku listy zawierajacej zarowno wezly rozpatrzone, 
// jak i te ktore zamierzamy jeszcze rozpatrzyc
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

// funkcja do tworzenia nowego elementu kolejki
// uzywana w metodzie push
box_2* new_box(int number, double length)
{
    box_2* tmp = (box_2*)malloc(sizeof(box_2));
    tmp->number = number;
    tmp->length = length;
    tmp->prev = NULL;
    tmp->next = NULL;

    return tmp;
}

// metoda oczyszczajaca pamiec po algorytmie Dijkstry
void clear_list(){
    while(first_l_2!=NULL){
        element_destroy();
    }
    first_l = NULL;
    first_l_2 = NULL;
}

// metoda calkowicie oczyszczajaca pamiec po elemencie
// wywolywana przez metode clear_list()
void element_destroy()
{
    box_2* tmp = first_l_2;
    first_l_2 = first_l_2->next;
    free(tmp);
}

// metoda pomijajaca element z najwyzszym priorytetem, czyli najmniejsza odlegloscia od zrodla
// element zostaje w drugiej liscie, aby utworzyc liste elementow juz rozpatrzonych
void pop()
{
    box_2* tmp = first_l;
    first_l = first_l->next;
}

// funkcja dodajaca element do listy z uwzglednieniem jego priorytetu
// zwraca wskaznik na wlasnie dodany wezel
box_2 *push(int number, double length)
{
    box_2* start = first_l;

    box_2* tmp = new_box(number, length);
    tmp->next = NULL;
    tmp->prev = NULL;

    // przypadek dla dodawania pierwszego elementu
    if(first_l == NULL)
    {
        first_l = tmp;    
        tmp->prev = tmp;
    }
    else
    {
        // jesli glowa ma mniejszy priorytet niz nowy element (jest dalej od zrodla)
        if (first_l->length > length)
        {
            tmp->next = first_l;
            first_l = tmp;
        }
        else
        {
            // przeszukiwanie listy do momentu znalezienia odpowiedniego miejsca dla nowego elementu
            while (start->next != NULL && start->next->length < length) {
                start = start->next;
            }
            tmp->next = start->next;
            start->next = tmp;
        }   
    }
    return tmp;
     
}

void show_path(int tg){
    struct box_2 *tmp;
    tmp = is_listed(tg);
    if(tmp != 0){
        do{
            printf("%d -> ", tmp->number);
            if((tmp->prev !=NULL)&&(tmp->prev->number != tmp->number))
                tmp = tmp->prev;
        }while((tmp->prev != NULL)&&(tmp->prev->number != tmp->number));
    }
    printf("%d\n", tmp->number);
}