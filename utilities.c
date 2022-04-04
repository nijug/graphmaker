#include "utilities.h"

int rand_bool()
{
    return random()>(RAND_MAX/2);
}
/* z standardowych bibliotek c nie da się zrobić równo rozłożonych liczb całkowitych ( ostatnia w zakresie będzie miała minimalną szansę)
 dlatego przy losowaniu gałęzi trzeba powtarzać losowanie true/false ( tu szanse są zbliżone do 50/50)*/

 double rand_d(double a, double b)
 {
     double temp = (double)rand()/RAND_MAX;
     return a+(b-a)*temp;
 }