#include "graph.h"
#include "bfs.h"
#include "dijkstra.h"
#include "utilities.h"

// narazie dałem standardowe mniejsze niż w funkcjonalnej żeby było łatwiej debuggować, potem do zmiany
int main(int argc, char** argv)
{
    //dijkstra(1, 1, 1, 1);
    
    srandom(time(NULL));
    int opt;
    char *fname="graf.txt";
    int x = 4;
    int y = 4;
    int n = 1;
    double r1=0.0;
    double r2=1.0;
    int k[256] = {1,25};
    int kSize =0;

    while ((opt = getopt (argc, argv, "f:x:y:n:r:k:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                fname = optarg;
                break;
            case 'x':
                if(is_int(optarg,0)==0)
                {
                    fprintf (stderr,"Argumenty x i y nie są liczbami całkowitymi większymi od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    x= atoi(optarg);
                break;
            case 'y':
                if(is_int(optarg,0)==0)
                {
                    fprintf (stderr,"Argumenty x i y nie są liczbami całkowitymi większymi od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    y = atoi(optarg);
                break;
            case 'n':
                if(is_int(optarg,0)==0)
                {
                    fprintf (stderr,"Argument n powinien być liczba całkowita większą od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    n= atoi(optarg);
                break;
            case 'r':
                optind--;
                r1 = atof(argv[optind]);
                if( *argv[optind] == '-' || optind == argc-1)
                {
                    fprintf (stderr,"Należy podać dwa argumenty r\n");
                    exit (EXIT_FAILURE);
                }
                r2 = atof(argv[optind+1]);
                if (r1 == 0 || r2 == 0  || r1 < 0.0 || r2 < 0.0)
                {
                    fprintf (stderr,"Argumenty r powinny być liczbami nieujemnmi!\n");
                    exit (EXIT_FAILURE);
                }
                if (r1 > r2 )
                {
                    fprintf (stderr,"Drugi argument r nie może być mniejszy od pierwszego!\n");
                    exit (EXIT_FAILURE);
                }
                break;
            case 'k':
                optind--;
                for( ;optind< argc ; optind++)
                {
                    if(isalpha(*(argv[optind]+1)) && *argv[optind] == '-' )
                        break;
                    if(is_int(argv[optind],1)==0)
                    {
                        fprintf (stderr,"Numery wezlow powinny być liczbami calkowitymi, nieujemnymi\n");
                        exit (EXIT_FAILURE);
                    }

                    k[kSize++]= atoi(argv[optind]);

                }
        }
    }

    if (x*y>max_mem())
    {
        fprintf (stderr,"Iloczyn argumentow x i y przekroczyl dopuszczalna wartosc maksymalna : %d !\n",max_mem());
        exit (EXIT_FAILURE);
    }

    if (x*y<n)
    {
        fprintf (stderr,"Argument n nie może być większy od iloczynu x*y!\n");
        exit (EXIT_FAILURE);
    }

    for (int i =0 ; i<kSize; i++)
    {
        if (k[i]>x*y)
        {
            fprintf (stderr,"Numery wezlow nie moga być większe od ilosci wszystkich wezlow w grafie (iloczynu argumentow x i y)!\n");
            exit (EXIT_FAILURE);
        }
    }

    if( access( fname, F_OK ) == 0 )
    {

        read_graph(fname,&x,&y);
        // tutaj wywołanie ścieżek grafu i zapisania ścieżki do pliku
        printf("Wynik bfsa: %d\n", bfs(0, 0, 4, 4));
        graphfree(x,y);
    }
   else
    {
       if ( x*y==1 || n == x*y )
       {
           write_graph(fname,x,y,0);
       }
       else
       {
           generate(x, y, r1, r2);
           if (k>0)
               // tu funkcja do dzielenia
           write_graph(fname, x, y,1);
           graphfree(x,y);
       }
    }
//printf("%d",max_mem());

/*
    printf("f:%s x:%d y:%d n:%d r1=%f r2=%f\n", fname, x,y,n,r1,r2);

    for (int j = 0; j<kSize; j++)
    {
        printf("k:");
        printf(" %d",k[j]);
    }

    printf("\n");
do testowania 

*/
    fprintf (stdout,"Program zakończono pomyślnie\n");
    exit (EXIT_SUCCESS);

}
