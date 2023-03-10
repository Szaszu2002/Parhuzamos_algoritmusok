#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int a, b, n;
    int ok=0;
    
    do{
        printf("Kérem adja meg az a változó értékét! \n");
        if(scanf("%d",&a)!=1)
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
        printf("Kérem adja meg a b változó értékét! \n");
        if(scanf("%d",&b)!=1||a<=0)
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
        printf("Kérem adja meg az n változó értékét! \n");
        if(scanf("%d",&n)!=1)
        {
            printf("\nHibas adat");
            ok=0;
        }
        else
        {
            ok=1;

        }
    }while(!ok);
    printf("\n a = %d \n b = %d \n n = %d", a, b, n);

    return 0;
}