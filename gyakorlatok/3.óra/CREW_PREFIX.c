#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void file_input(int* array, int n);
void sort(int* array,int begin, int end);
void uploaded(int a, int b,int *tomb, int n);

int main()
{
    int n;
    n=10;
    int half=n/2;
    int X[n];
    uploaded(10,100,X,n);
    printf("\n");
    sort(X,0,half);
    sort(X,half,n-1);
    int a=X[half-1];
    int i;
    printf("%d, ", a);



    
    for(i=half;i<n;i++)
    {
        X[i]=X[i]+a;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d ", X[i]);
    }

    file_input(X,n);
    return 0;
}

void file_input(int* array, int n)
{
    FILE *fp;
    int i;
   
    fp=fopen("array.txt","wt");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0; i<n;i++)
        {
            fprintf(fp,"%d\n", array[i]);
        }
        fclose(fp);
    }
    return;
}
void sort(int* array,int begin, int end)
{
    int i, j, tmp;
    
    for(i=begin;i<end;i++)
    {
        for(j=i+1;j<end+1;j++)
        {
            if(array[i]>array[j])
            {
                tmp=array[j];
                array[j]=array[i];
                array[i]=tmp;
            }
        }
    }
    return;
}
void uploaded(int a, int b, int* tomb, int n)
{
    srand(time(NULL));
    int i;
    int ok=0;
    for(i=0; i<n; i++)
    { 
        tomb[i] = rand() % (b-a+1) + a;
        printf("%d ", tomb[i]);
    }
    return;
}