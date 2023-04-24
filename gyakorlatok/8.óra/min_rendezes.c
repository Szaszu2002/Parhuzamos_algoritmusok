#include <stdio.h>
#include <stdlib.h>


struct Array{
    int *data;
    int size;
};

const int N_THREADS = 10;
typedef struct Array array;

void MinSort( array* array);
void Upload( array* array);

int main()
{
    int i;
    for(i=100;i<100000;i+=100)
    {
        struct array array*;
        array.size=i;
        int j;
        Upload(array);

        clock_t sequencial_time1;
        sequencial_time1=clock();
        MinSort(array);
        clock_t sequencial_time2;
        sequencial_time2=clock();
        clock_t sequencial_time;
        sequencial_time=sequencial_time2-sequencial_time1;

        clock_t p_time1;
        p_time1=clock();
        for(j=0;j<N_THREADS;j++)
        {
            pthread_create(&threads[j],NULL,MinSort, array* array);
        }
        clock_t p_time2;
        p_time2=clock();
        clock_t p_time;
        p_time=p_time2-p_time1;

        runtime_display(sequencial_time, p_time, i);
    }
    return 0;
}

void Upload( array* array)
{
    srand(time(NULL));
    int i;
    int ok=0;
    for(i=0; i<array.size; i++)
    { 
        array.data[i] = rand();
    }
    return;
}

void runtime_display(clock_t sequencial_time, clock_t p_time , int size)
{
    FILE *fp;
   
    fp=fopen("runtime_min_rendezes.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n%d; %.2lf; %.2lf;\n",size, sequencial_time, p_time);
        fclose(fp);
    }
    return;
}

void MinSort( array* array)
{
    int i, j;
    for(i=0;i<array.size-1;i++)
    {
        for(j=i+1;j<array.size;i++)
        {
            if(array.data[i]>array.data[j])
            {
                int tmp=array.data[i];
                array.data[i]=array.data[j];
                array.data[j]=tmp;
            }
        }
    }
}