#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void fajlbakiir(int* tomb, int n);

int main()
{
    int n;
    n=10;
    int X[n]={18, 13, 15, 35, 5, 2 , 12, 20, 10, 25};
    int Y[n];
    Y[0]=X[0];
    int i;
    int k=0;
    for(i=1;i<n;i++)
    {
        Y[i]=X[i-1]+X[i];
        k=2;
    }
    while(k<n)
    {
        for(i=k+1;i<n;i++)
        {
            Y[i]=Y[i-k]+Y[i];
        }
        k=2*k;
    }
    fajlbakiir(Y,n);
    return 0;
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