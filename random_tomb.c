#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int n;
    int a;
    int b;
    int ok=0;
    
    do{
        printf("Adja meg a tömb méretét!\n");
        if(scanf("%d",&n)!=1||n<=0)
        {
            printf("Hibas adat");
            ok=0;
        }
        else
        {
            ok=1;
        }
    }while(!ok);

    ok=0;
    do{
        printf("Kérem adja meg az a változó értékét! \n");
        if(scanf("%d",&a)!=1||a<=0)
        {
            printf("\nHibas adat");
            ok=0;
        }
        else
        {
            ok=1;

        }
    }while(!ok);
    
    ok=0;
    do{
        printf("Kérem adja meg a b változó értékét! \n");
        if(scanf("%d",&b)!=1||b<=a)
        {
            printf("\nHibas adat");
            ok=0;
        }
        else
        {
            ok=1;
        }
    }while(!ok);
    
    double tomb[n];
    srand(time(NULL));
    int i;
    ok=0;
    double tav =(b-a);
    double div = RAND_MAX /tav;
    for(i=0; i<n; i++)
    { 
        tomb[i] = (rand() / div) + a;
    }
    i=0;
    for(i=0; i<n; i++)
    {
        printf("%lf, ", tomb[i]);
    }

    return 0;
}