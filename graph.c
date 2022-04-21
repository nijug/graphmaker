#include "graph.h"

node **graph;
node **Fgraph;

struct lista_c *first_c = NULL;
struct lista_c *last_c = NULL;

double find_value(node *l, int point)
{
    node *tmp=l;
    while (tmp->point!= point)
        tmp=tmp->next;
    return tmp->value;
}

void delete(node *l, int point, double value ) // point numer wezla do którego ma byc usunieta krawedz , value -1.0 dla usunietej krawedzi, -2.0 dla usunietego wezla i krawedzi
{
    node *tmp=l;
    while (tmp->point != point)
        tmp=tmp->next;
    tmp->value=value;
    return;
}

int v_count(node *l,double value) // zlicza ilośc value w węźle
{
    node *tmp=l;
    int count=0;
    while (tmp->next!=NULL)
    {
        if (tmp->value==value)
            count++;
        tmp=tmp->next;
    }
    if (tmp->value= value)
        count++;
    return count;
}

// usuwa wezel poprzez zamiane wartosci wszystkich jego krawedzi na -2.0
// wezel moze nie posiadac zadnych krawedzi, ale dalej istniec
void obliterate(node *l) // ustawia value wszystkich krawędzi wezła na -2.0
{
    node *tmp=l;
    while (tmp->next!=NULL)
    {
        tmp->value=-2.0;
        tmp=tmp->next;
    }
    tmp->value=-2.0;
return ;
}

node* add(node *l, int point, double value)
{
    // dla pierwszego węzła
    if (l == NULL)
    {
        node *nw = malloc(sizeof(node));
        nw->value = value;
        nw->point = point;
        nw->next = NULL;
        return nw;
    }
    // dla kolejnych węzłów
    else
    {
        node *tmp = l;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = malloc(sizeof (node));
        tmp->next->value = value;
        tmp->next->point = point;
        tmp->next->next = NULL;
        return l;
    }
}

// generator grafu
void generate(int x, int y, double rand1, double rand2)
{
   graph = malloc(sizeof(node*) * x * y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            graph[i * y + j]=NULL;
            // tworzenie krawędzi prowadzących do sąsiadujących węzłów
            if(i!=0) // górny, dzięki temu warunkowi find_value szuka wartości tylko jeśli sąsiadujący węzeł już istnieje
                graph[i * y + j]=add(graph[i * y + j], (i-1) * y + j,find_value(graph[(i-1) * y + j],i * y + j));
            if(j+1!=y) // lewy
                graph[i * y + j] = add(graph[i * y + j], i * y + j+1, rand_d(rand1, rand2));
            if(j!=0) // prawy
                graph[i * y + j]=add(graph[i * y + j], i * y + j-1,find_value(graph[i * y + j-1],i * y + j));
            if(i+1!=x) //dolny
                graph[i * y + j]=add(graph[i * y + j], (i+1) * y + j,rand_d(rand1, rand2) );

        }
    }
}
void Fgenerate(int x, int y)
{
    Fgraph = malloc(sizeof(node*) * x * y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            Fgraph[i * y + j]=NULL;

            if(i!=0)
                Fgraph[i * y + j]=add(Fgraph[i * y + j], (i-1) * y + j,0);
            if(j+1!=y)
                Fgraph[i * y + j] = add(Fgraph[i * y + j], i * y + j+1, 0);
            if(j!=0)
                Fgraph[i * y + j]=add(Fgraph[i * y + j], i * y + j-1,0);
            if(i+1!=x)
                Fgraph[i * y + j]=add(Fgraph[i * y + j], (i+1) * y + j,0 );

        }
    }
}
void graphfree(int x, int y)
{
    for (int i = 0; i < x * y; i++)
    {
        node* tmp;
        if(graph[i] != NULL)
        {
            while (graph[i]->next != NULL)
            {
                tmp = graph[i];
                graph[i] = graph[i]->next;
                free(tmp);
            }
        }
        free(graph[i]);
    }
free (graph);
}
void Fgraphfree(int x, int y)
{
    for (int i = 0; i < x * y; i++)
    {
        node* tmp;
        if(Fgraph[i] != NULL)
        {
            while (Fgraph[i]->next != NULL)
            {
                tmp = Fgraph[i];
                Fgraph[i] = Fgraph[i]->next;
                free(tmp);
            }
        }
        free(Fgraph[i]);
    }
    free (Fgraph);
}

void Twrite_graph (int x, int y) // tylko debuggowania, wypisuje na terminal w czytelniejszym formacie
{
    fprintf(stdout,"%d %d\n",x,y);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            fprintf(stdout,"%d: \n", i * y + j);
            node *tmp = graph[i * y + j];
            while (tmp != NULL)
            {
                fprintf(stdout,"%d %f \n", tmp->point, tmp->value);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
}
void write_graph (char* fname, int x, int y, int n) // n decyduje czy graf posiada krawędzie - jeśli nie (0) zapisujemy tylko rozmiary
{
    FILE *in= fopen(fname,"w+");
    if (in == NULL)
    {
        fprintf (stderr,"Błąd w zapisywaniu do pliku\n");
        fclose(in);
        exit (EXIT_FAILURE);
    }
    fprintf(in,"%d %d\n",x,y);
    if (n==1)
    {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                node *tmp = graph[i * y + j];
                if(tmp != NULL)
                {
                    while (tmp != NULL)
                    {
                        fprintf(in, "%d %f ", tmp->point, tmp->value);
                        tmp = tmp->next;
                    }
                }
                fprintf(in, "\n");
            }
        }
    }
    fclose(in);
}

void read_graph(char *fname, int *x, int *y)
{

    FILE *in= fopen(fname,"a+");
    if (in == NULL)
    {
        fprintf (stderr,"Błąd w otworzeniu pliku\n");
        fclose(in);
        exit (EXIT_FAILURE);
    }
    int points[4];
    double values[4];
    char line[256];
    if(fgets(line,256, in)==NULL)
    {
        fprintf (stderr,"Błąd podczas odczytywania pliku\n");
        fclose(in);
        exit (EXIT_FAILURE);
    };

    int read=sscanf(line,"%d %d",x, y);
    if (read == EOF || read != 2 )
    {
        fprintf (stderr,"Nieprawidłowy format pliku\n");
        fclose(in);
        exit (EXIT_FAILURE);
    }
    if (*x * *y>max_mem())
    {
        fprintf (stderr,"Iloczyn argumentow x i y przekroczyl dopuszczalna wartosc maksymalna : %d bajtow!\n",max_mem());
        exit (EXIT_FAILURE);
    }
    graph = malloc(sizeof(node*) * *x * *y);

    for (int i = 0; i<*x * *y ; i++)
    {
        if(fgets(line,256, in)==NULL)
        {
            fprintf (stdout,"Graf nie posiada krawędzi, nie można wyznaczyć ścieżki\n");
            fclose(in);
            exit (EXIT_SUCCESS);
        };


        read = sscanf(line, "%d %lf %d %lf %d %lf %d %lf ",&points[0], &values[0],&points[1], &values[1],&points[2], &values[2],&points[3], &values[3]);
        if (read/2==0)
            graph[i]=NULL;
        else if (read/2>0)
        {
            for (int j = 0; j < read / 2; j++)
                graph[i] = add(graph[i], points[j], values[j]);
        }
        else
        {
          fprintf (stderr,"Błąd podczas odczytywania pliku\n");
          fclose(in);
          exit (EXIT_FAILURE);
        }
    }
    fclose(in);
}

void divider(int x, int y, int n)
{
    int a, current;
    Fgenerate(x,y);
    for(int l = 1; l < n; l++)
    {
        do{
            a = rand_i(0, x * y - 1);
        }while(first_edgy(a, y) == 0);
        
        current = a;
        enqueue_c(current);

        do{
            // losowe wyznaczanie kierunku
            // w prawo, w innym wypadku w dol albo w gore
            if(rand_bool() == 1)
            {
                //printf(valid(current + 1, x, y));
                if(valid(current + 1, x, y)==1)
                    current++;
            }
            else
            {
                // w gore
                if((rand_bool() == 1)||(valid(current - y, x, y)==1))
                    current -= y;
                // w dol
                else if(valid(current + y, x, y)==1)
                {
                    current += y;
                }
            }

            // dodaje wezel do listy oznaczajacej sciezke, 
            // po ktorej graf bedzie dzielony
            enqueue_c(current);
        }while(edgy(current, x, y) == 0);
        
        cut_graph(y, x);
        clear_queue_c();
        /*
            obliterate((Fgraph[0]));
            delete(Fgraph[1],0,-2.0);
            delete(Fgraph[2],0,-2.0);

            fprintf(stdout,"%d %d\n",x,y);
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    fprintf(stdout,"%d: \n", i * y + j);
                    node *tmp = Fgraph[i * y + j];
                    while (tmp != NULL)
                    {
                        fprintf(stdout,"%d %f \n", tmp->point, tmp->value);
                        tmp = tmp->next;
                    }
                    printf("\n");
                }
            }

            printf("%d\n",v_count(Fgraph[0],-2.0));
            printf("%d\n",v_count(Fgraph[1],-2.0));
        */
    }

    Fgraphfree(x,y);

return;
}

// sprawdza czy wezel jest na krawedzi, 
// badz ktoras z krawedzi "nie istnieje"
// wtedy zwraca 1
// w przeciwnym wypadku zwraca 0
// (gdy ma wszystkie cztery krawedzie)
int edgy(int a, int x, int y){
    
    // czy na pewno?
    // moze potrzebny fgraph[a]
    node *tmp = Fgraph[a];
    // sprawdzenie czy wezel istnieje w ogole
    if(tmp->value == -2.0)
        return 0;
    int i = a / y;
    int j = a % y;

    if(i!=0)
    { // gorny
        if(tmp->value==-1.0)
            return 1;
        tmp = tmp->next;
    }
    else return 1;

    if(j+1!=y)
    { // lewy
        if(tmp->value==-1.0)
            return 1;
        tmp = tmp->next;
    }
    else return 1;

    if(j!=0)
    { // prawy
        if(tmp->value==-1.0)
            return 1;
        tmp = tmp->next;
    }
    else return 1;

    if(i+1!=x)
    { //dolny
        if(tmp->value==-1.0)
            return 1;
    }
    else return 1;

    return 0;
}

// specjalny wariant dla pierwszego znaku
int first_edgy(int a, int y)
{
    node *tmp = Fgraph[a];
    // sprawdzenie czy wezel istnieje w ogole
    if(tmp->value == -2.0)
        return 0;
    int i = a / y;
    int j = a % y;
    if(i!=0){ // gorny
        tmp = tmp->next;
    }

    // jesli po lewej ma usuniety graf
    // to sie nadaje
    if(j!=0){ // lewy
        if(tmp->value==-1.0)
            return 1;
        tmp = tmp->next;
    }

    // jesli przylega do lewej krawedzi grafu 
    // to sie nadaje
    else return 1;

    return 0;
}

// funkcja sprawdzajaca, czy dany wezel moze zostac
// dodany do sciezki (znajduje sie w zakresie numerow wezlow)
// raz nie zostal dodany tam juz wczesniej
int valid(int a, int x, int y)
{
    if((a<0)||(a>((x*y)-1)))
    {
        return 0;
    }
    node *tmp = Fgraph[a];

    if(tmp->value == -2.0){
        return 0;
    }

    if(in_queue_c(a)==1)
    {
        return 0;
    }
    return 1;
}

// funkcja tnaca graf, na podstawie danych o 
// wezlach znajdujacych sie w liscie
void cut_graph(int y, int x)
{
    int cel, start, kierunek, i, j;
    node *ftmp = NULL;
    node *tmp = NULL;
    node *tmp2 = NULL;

    // if dla punktu a,
    // zeby odciac jakas krawedz

    while(first_c->next!=NULL)
    {
        start = first_c->value;
        cel = first_c->next->value;
        kierunek = cel - start;
        i = start / y;
        j = start % y;
        ftmp = Fgraph[start];

        if(kierunek == 1)
        {
            // oba zawsze maja krawedz w lewo
            // tmp krawedz w dol
            // tmp2 krawedz w gore
            tmp = graph[start+1];
            tmp2 = graph[start+y+2];
            // wziecie pod uwage pozycji wezla
            // aby odczytac pozycje krawedzi
            if(i!=0){ // posiadanie krawedzi idacej w gore
                tmp = tmp->next;
            }

            tmp2->value = -1.0;
            tmp2 = tmp2->next;

            if(j+1!=y){ // posiadanie krawedzi idacej w prawo
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }

            //if(j!=0){ // posiadanie krawedzi idacej w lewo
            tmp = tmp->next;
            tmp2 = tmp2->next;
            //}

            tmp->value = -1.0;
            /* zbedne w tym przypadku
            if(i+1!=x){ //pozsiadanie krawedzi idacej w dol
            }
            */
        }

        else if(kierunek == y)
        {
            // oba zawsze maja krawedz w gore
            // tmp krawedz w prawo
            // tmp2 krawedz w lewo
            tmp = graph[start+y+1];
            tmp2 = graph[start+y+2];
            // wziecie pod uwage pozycji wezla
            // aby odczytac pozycje krawedzi
            //if(i!=0){ // posiadanie krawedzi idacej w gore
                tmp = tmp->next;
                tmp2 = tmp->next;
            //}

            if(j+1!=y){ // posiadanie krawedzi idacej w prawo
                tmp2 = tmp2->next;
            }
            tmp->value = -1.0;
            tmp = tmp->next;

            if(j!=0){ // posiadanie krawedzi idacej w lewo
                tmp = tmp->next;
            }
            tmp2->value = -1.0;
            tmp2 = tmp2->next;

            /*if(i+1!=x){ //pozsiadanie krawedzi idacej w dol

            }*/
        }

        else if(kierunek == (-1*y))
        {
            tmp = graph[start];
            tmp2 = graph[start+1];
            // oba zawsze maja krawedz w dol
            // tmp krawedz w prawo
            // tmp2 krawedz w lewo
            tmp = graph[start+y+1];
            tmp2 = graph[start+y+2];
            // wziecie pod uwage pozycji wezla
            // aby odczytac pozycje krawedzi
            if(i!=0){ // posiadanie krawedzi idacej w gore
                tmp = tmp->next;
                tmp2 = tmp->next;
            }

            if(j+1!=y){ // posiadanie krawedzi idacej w prawo
                tmp2 = tmp2->next;
            }
            tmp->value = -1.0;
            tmp = tmp->next;

            if(j!=0){ // posiadanie krawedzi idacej w lewo
                tmp = tmp->next;
            }
            tmp2->value = -1.0;
            tmp2 = tmp2->next;

            /*if(i+1!=x){ //pozsiadanie krawedzi idacej w dol

            }*/
        }
        obliterate(ftmp);
        dequeue_c();            
    }
}

////////////////////////// metody do listy

// metoda do usuniecia wezla z listy wezlow rozpatrzonych
void dequeue_c()
{
    if(first_c != NULL)
    {
        struct lista_c *tmp;
        tmp = first_c;
        first_c = first_c->next;
        free(tmp);
    }
}

// sprawdza czy dany numer wezla jest juz w kolejce
// zwraca 1 gdy jest i 0 gdy nie ma
int in_queue_c(int val)
{
    struct lista_c *tmp;
    tmp = first_c;
    if(first_c != NULL)
    {
        do{
            if(tmp->value == val)
                return 1;
            if(tmp->next!=NULL)
                tmp = tmp->next;
        }while(tmp->next!=NULL);
        if(tmp->value == val)
            return 1;
    }
    return 0;    
}

// zwraca ilosc wezlow w liscie wezlow do rozpatrzenia
int queue_size_c()
{
    int size = 0;
    struct lista_c *tmp;
    tmp = first_c;
    if(first_c != NULL)
    {
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

// metoda do dodania wezla do listy wezlow do rozpatrzenia
void enqueue_c(int val)
{
    struct lista_c *rb = malloc(sizeof(struct lista_c));
    rb->value = val;
    rb->next = NULL;
    if(last_c == NULL)
    {
        first_c = rb;
        last_c = rb;
    }
    else{
        last_c->next = rb;
        last_c = last_c->next;
    }
}

// metoda do czyszczenia pamiec i resetujaca kolejke
void clear_queue_c()
{
    while(first_c!=NULL)
    {
        dequeue_c();
    }
    first_c = NULL;
    last_c = NULL;
}
