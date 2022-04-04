#include "graph.h"
#include "utilities.h"

// narazie dałem standardowe mniejsze niż w funkcjonalnej żeby było łatwiej debuggować, potem do zmiany
int main(int argc, char** argv)
{
    srandom(time(NULL));
    int mode; // 0 dla generowania, 1 dla analizy
    int opt;
    char *fname=NULL;
    int x = 3;
    int y = 3;
    int n = 1;
    double r1=0.0;
    double r2=1.0;
    int k[256] = {1,25};
    int i =0;

    while ((opt = getopt (argc, argv, "f:x:y:n:r:k:")) != -1) {
        switch (opt) {
            case 'f':
                fname = optarg;
                break;
            case 'x':
                if(isINT(optarg)==0)
                {
                    fprintf (stderr,"Argumenty x i y nie są liczbami całkowitymi większymi od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    x= atoi(optarg);
                break;
            case 'y':
                if(isINT(optarg)==0)
                {
                    fprintf (stderr,"Argumenty x i y nie są liczbami całkowitymi większymi od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    y = atoi(optarg);
                break;
            case 'n':
                if(isINT(optarg)==0)
                {
                    fprintf (stderr,"Argument n powinien być liczba całkowita większą od zera!\n");
                    exit (EXIT_FAILURE);
                }
                else
                    n= atoi(optarg);
                break;
            case 'r':
                r1 = atof(argv[optind-1]);
                r2 = atof(argv[optind]);
                if (r1 <= 0.0 || r2 <= 0.0)
                {
                    fprintf (stderr,"Argumenty r powinny być liczbami większymi od zera!\n");
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
                for( ;optind< argc && *argv[optind] != '-'; optind++) {
                    k[i++]= atoi(argv[optind]);
                }
            }
    }
    generate(x, y, 1.0 ,2.0);
    write(fname,x,y);

    graphfree(x,y);

   printf("f:%s x:%d y:%d n:%d r1=%f r2=%f\n", fname, x,y,n,r1,r2);
 for (int j = 0; j<i; j++)
    {
        printf("k:");
        printf(" %d",k[j]);
    }

    printf("\n");
    return 0;
}
