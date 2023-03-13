#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void feltolt(int a, int b,int *tomb, int n);
void fajlbakiir(int* tomb, int n);

int main()
{
    int a=10;
    int b=100;
    int i;

    for(i=10;i<10000;i+10)
    {
        int array[i];
        feltolt(a,b,array,i);
        fajlbakiir(array,i);

    }
    return 0;
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

void fajlbakiir(int* tomb, int n)
{
    FILE *fp;
    int i;
   
    fp=fopen("rand_tomb.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0; i<n;i++)
        {
            fprintf(fp,"%d ", tomb[i]);
        }
        fclose(fp);
    }
    return;
}