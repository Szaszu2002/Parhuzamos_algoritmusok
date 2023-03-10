#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tombfajlbairas2.h>

int main()
{
    int n;
    int a;
    int b;
    beker(&n,0);
    beker(&a,0);
    beker(&b,a);
    int tomb[n];
    feltolt(a,b,tomb,n);
    kiir(tomb,n);
    fajlbakiir(tomb,n);

    return 0;
}