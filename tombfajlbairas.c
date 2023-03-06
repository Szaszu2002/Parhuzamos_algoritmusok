#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void beker(int* bekerendo, int plusz);
void feltolt(int a, int b,int[] *tomb);
void kiir(int[] tomb);
void fajlbakiir(int[] tomb);

int main()
{
    int n;
    int a;
    int b;
    beker(n,0);
    beker(a,0);
    beker(b,a);
    double tomb[n];
    feltolt(a,b,tomb);
    kiir(tomb);
    fajlbakiir(tomb);

    return 0;
}

void beker(int* bekerendo, int plusz)
{
 int ok=0;
 
    do{
        printf("Adjon meg egy számot!\n");
        if(scanf("%d",&bekerendo)!=1||bekerendo<=plusz)
        {
            printf("Hibas adat");
            ok=0;
        }
        else
        {
            ok=1;
        }
    }while(!ok);
    return;
}

void feltolt(int a, int b,int[] tomb)
{
    srand(time(NULL));
    int i;
    int ok=0;
    double tav =(b-a);
    double div = RAND_MAX /tav;
    for(i=0; i<n; i++)
    { 
        tomb[i] = (rand() / div) + a;
    }
    return;

}

void kiir(int[] tomb)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        printf("%lf, ", tomb[i]);
    }
    return;
}
void fajlbakiir(int[] tomb)
{
    FILE *fp;
    char filename[50];
    printf("Adja meg a fájl nevét! ");
    scanf("%s",filename);
    fp=fopen(filename,"w");
    printf("Szöveg kiírása");
    while((tomb=getchar())!='#')
    {
        putc(tomb,fp);
    }
    fclose(fp);

    return;
}