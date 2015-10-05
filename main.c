#include "funcs.h"
#include <stdio.h>


int main (const int argc, const char **argv) {
    double jd;

    jd = CalculateSolarTerms(4485, 18 * 15);

    printf ("jd->%f\n", jd);

    return 0;
}
