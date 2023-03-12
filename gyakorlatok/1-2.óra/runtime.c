#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void beker(int* bekerendo, int plusz);
void feltolt(int a, int b,int *tomb, int n);
void kiir(int* tomb, int n);
void fajlbakiir(int* tomb, int n);
void runtime_display(clock_t request, clock_t upload, clock_t listing, clock_t filedump, int n);

int main()
{
    int n;
    int a;
    int b;
    clock_t time1=clock();
    beker(&n,0);
    beker(&a,0);
    beker(&b,a);
    clock_t time2=clock();
    clock_t request=time2-time1;

    int tomb[n];
    clock_t time3=clock();
    feltolt(a,b,tomb,n);
    clock_t time4=clock();
    clock_t upload=time4-time3;

    clock_t time5=clock();
    kiir(tomb,n);
    clock_t time6=clock();
    clock_t listing=time6-time5;

    clock_t time7=clock();
    fajlbakiir(tomb,n);
    clock_t time8=clock();
    clock_t filedump=time8-time7;
    runtime_display(request,upload,listing,filedump,n);
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
void runtime_display(clock_t request, clock_t upload, clock_t listing, clock_t filedump, int n)
{
    FILE *fp;
    int i;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"%d; %d; %d; %d; %d;\n",n,request,upload,listing,filedump);
        fclose(fp);
    }
    return;
}