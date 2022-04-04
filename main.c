#include "graph.h"
#include "utilities.h"
#define  STD_X 3
#define  STD_Y 3
#define  STD_N 1
#define  STD_RAND1 0.0
#define  STD_RAND2 1.0

// narazie dałem standardowe mniejsze niż w funkcjonalnej żeby było łatiwej debuggować, potem do zmiany
int main()
{
    srandom(time(NULL));


    int x = 2;
    int y = 2;
    generate(x, y, 1.0 ,2.0);
    write("test",x,y);
    graphfree(x,y);
    return 0;
}
