#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void beker(int* bekerendo, int plusz);
void feltolt(int a, int b,int *tomb, int n);
void kiir(int* tomb, int n);
void fajlbakiir(int* tomb, int n);

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

void beker(int* bekerendo, int plusz)
{
 int ok=0;
 
    do{
        printf("Adjon meg egy számot!\n");
        if(scanf("%d",bekerendo)!=1||*bekerendo<plusz || *bekerendo==plusz)
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

void feltolt(int a, int b, int* tomb, int n)
{
    srand(time(NULL));
    int i;
    int ok=0;
    //double tav=(b-a);
    //double div = RAND_MAX /tav;
    for(i=0; i<n; i++)
    { 
        tomb[i] = rand() % (b-a+1) + a;
    }
    return;

}

void kiir(int* tomb, int n)
{
    int i=0;
    for(i=0; i<n; i++)
    {
        printf("%d\n, ", tomb[i]);
    }
    return;
}
void fajlbakiir(int* tomb, int n)
{
    FILE *fp;
    int i;
   
    fp=fopen("tomb.txt","wt");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0; i<n;i++)
        {
            fprintf(fp,"%d\n", tomb[i]);
        }
        fclose(fp);
    }
    return;
}