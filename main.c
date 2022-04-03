#include <stdio.h>
#include "graph.h"

int main()
{
    int x = 10;
    int y = 10;
    generate(x, y);
    write("test",x,y);
    graphfree(x,y);
    return 0;
}
