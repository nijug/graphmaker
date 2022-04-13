#include "bfs.h"

struct box *first = NULL;
struct box *last = NULL;
struct box *first_2 = NULL;
struct box *last_2 = NULL;

void enqueue(int number);
void dequeue();
int in_queue(int number);
int queue_size();
void enqueue_curr(int number);
void dequeue_curr();
int in_queue_curr(int number);
void clear_queue();
void clear_queue_curr();

// dla roznych a i b zwraca 1 istnieje sciezka miedzy nimi albo 0 jesli nie istnieje
// dla tych samych a i b zwraca 1 jesli caly graf jest spojny oraz 0 jesli jest nie spojny
int bfs(int a, int b, int x, int y){
    int curr = a, found = 0, i, j;
    enqueue_curr(curr);

    node *tmp;
    while(first_2!=0){
        if(curr == b) found = 1;
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

        // gdy kolejka do rozpotrzenia jest pusta (wszystkie dostepne wezly zostaly rozpatrzone)
        if(first_2 == NULL)
        {
            // sytuacja, gdy sprawdzamy spojnosc calego grafu
            if(a == b)
            {
                if(queue_size() == (x*y)) 
                {
                    clear_queue_curr();
                    clear_queue();
                    printf("Graf jest spojny.\n");
                    return 2;
                }
                else 
                {
                    clear_queue_curr();
                    clear_queue();  
                    printf("Graf nie jest spojny.\n");
                    return 3;
                }
            }
            // sytuacja, gdy sprawdzamy tylko czy istnieje sciezka miedzy dwoma konkretnymi wezlami
            else
            {
                if(found == 0)
                {
                    clear_queue_curr();
                    clear_queue();  
                    printf("Sciezka miedzy wybranymi wezlami nie istnieje!\n");
                }
                return found;
            }
        }

        // zamiana numeru obecnego wezla na numer pierwszego wezla w kolejce do rozpatrzenia
        curr = (first_2->nb);

    }
    //*//                
    //return 1;
}

///////////////////////////// METODY /////////////////////////////

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
        if(tmp->nb == number)
            return 1;
    }
    return 0;    
}

// zwraca ilosc wezlow w liscie
int queue_size(){
    int size = 0;
    struct box *tmp;
    tmp = first;
    if(first != NULL){
        do{
            size++;
            //printf("%d. Numer wezla %d\n", size, tmp->nb);
            if(tmp->next!=NULL)
                tmp = tmp->next;
        }while(tmp->next!= NULL);
        size++;
    }
    return size;    
}

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
    if(first_2 != NULL){
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
        if(tmp->nb == number)
            return 1;
    }
    return 0;    
}

// metoda do czyszczaca pamiec i resetujaca kolejke
void clear_queue(){
    while(first!=NULL){
        dequeue();
    }
    first = NULL;
    last = NULL;
}

// metoda czyszczaca pamiec i resetujaca kolejke
void clear_queue_curr(){
    while(first_2!=NULL){
        dequeue_curr();
    }
    first_2 = NULL;
    last_2 = NULL;
}
