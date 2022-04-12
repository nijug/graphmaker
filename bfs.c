#include "graph.h"
#include "bfs.h"

struct box *first = NULL;
struct box *last = NULL;

void display_curr();

// metoda do dodania numeru wezla do kolejki
void enqueue(int number){
    struct box *rb = malloc(sizeof(struct box));
    rb->nb = number;
    rb->next = NULL;
    if(last == NULL){
        first = rb;
        last = rb;
    }
    else{
        last->next = rb;
        last = last->next;
    }
}
// metoda do usuniecia numeru wezla do kolejki
void dequeue(){
    if(first != NULL){
        struct box *tmp;
        tmp = first;
        first = first->next;
        free(tmp);
    }
}

// sprawdza czy dany numer wezla jest juz w kolejce
// zwraca 1 gdy jest i 0 gdy nie ma
int in_queue(int number){
    struct box *tmp;
    tmp = first;
    if(first != NULL){
        do{
            if(tmp->nb == number)
                return 1;
            if(tmp->next!=NULL)
                tmp = tmp->next;
        }while(tmp->next!= NULL);
    }
    return 0;    
}

//DO POPRAWIENIA (SCALENIA TYCH FUNKCJI DO KOLEJEK)
struct box *first_2 = NULL;
struct box *last_2 = NULL;

// metoda do dodania numeru wezla do kolejki
void enqueue_curr(int number){
    struct box *rb = malloc(sizeof(struct box));
    rb->nb = number;
    rb->next = NULL;
    if(last_2 == NULL){
        first_2 = rb;
        last_2 = rb;
    }
    else{
        last_2->next = rb;
        last_2 = last_2->next;
    }
}
// metoda do usuniecia numeru wezla do kolejki
void dequeue_curr(){
    if(first != NULL){
        struct box *tmp;
        tmp = first_2;
        first_2 = first_2->next;
        free(tmp);
    }
}

// sprawdza czy dany numer wezla jest juz w kolejce
// zwraca 1 gdy jest i 0 gdy nie ma
int in_queue_curr(int number){
    struct box *tmp;
    tmp = first_2;
    if(first_2 != NULL){
        do{
            if(tmp->nb == number)
                return 1;
            if(tmp->next!=NULL)
                tmp = tmp->next;
        }while(tmp->next!= NULL);
    }
    return 0;    
}

// zwraca 1 jesli znajdzie sciezke albo 0 jesli nie znajdzie
int bfs(int a, int b, int x, int y){
    int curr = a;
    enqueue_curr(curr);
    int i, j;
    node *tmp;
    while(curr != b){
        i = curr / x;
        j = curr % y;
        tmp = graph[curr];
        if(tmp != NULL){

            if(i!=0){ // gorny
                if(tmp->value!=-1.0)
                // jesli dany numer wezla nie pojawil sie jeszcze w kolejce rozpatrzonych oraz w kolejce do rozpatrzenia
                    if(in_queue(tmp->point)!=1&&in_queue_curr(tmp->point)!=1)
                        enqueue_curr(tmp->point);
                tmp = tmp->next;
            }

            if(j+1!=y){ // lewy
                if(tmp->value!=-1.0)
                    if(in_queue(tmp->point)!=1&&in_queue_curr(tmp->point)!=1)
                        enqueue_curr(tmp->point);
                tmp = tmp->next;
            }

            if(j!=0){ // prawy
                if(tmp->value!=-1.0)
                    if(in_queue(tmp->point)!=1&&in_queue_curr(tmp->point)!=1)
                        enqueue_curr(tmp->point);
                tmp = tmp->next;
            }

            if(i+1!=x){ //dolny
                if(tmp->value!=-1.0)
                    if(in_queue(tmp->point)!=1&&in_queue_curr(tmp->point)!=1)
                        enqueue_curr(tmp->point);
            }
        }
        // zapisanie obecnego wezla do kolejki rozpatrzonych
        enqueue(curr);
        // usuniecie obecnego wezla z kolejki do rozpatrzenia
        dequeue_curr(curr);
        if(first_2 == NULL)
            return 0;
        // zamiana obecnego wezla na pierwszy wezel w kolejce do rozpatrzenia
        curr = (first_2->nb);
        //printf("Current queue: \n");
        //display_curr();

    }

    
    return 1;
}

void display_curr(){
    struct box *tmp;
    if(first_2!=NULL){
        do{
            tmp = first_2;
            printf("%d ", tmp->nb);
            tmp = tmp->next;
        }while(tmp!=NULL);
    }
    printf("\n");
}