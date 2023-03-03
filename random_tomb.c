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
    
    int tomb[n];
    srand(time(NULL));
    int i;
    ok=0;
    for(i=0; i<n; i++)
    { 
        do{
            tomb[i]=rand();
            if(tomb[i]<a && tomb[i]>b)
            {
               printf("Hibas adat");
                ok=0; 
            }
            else
            {
                ok=1;
            }
        }while(!ok);
    }
    i=0;
    for(i=0; i<n; i++)
    {
        printf("%d, ", tomb[i]);
    }

    return 0;
}