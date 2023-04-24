#include <stdio.h>
#include <stdlib.h>

void Upload( array* array);
void QuickSort(array* array);
void runtime_display(clock_t sequencial_time, clock_t p_time , int size); 

struct Array{
    int *data;
    int size;
};

const int N_THREADS = 10;
typedef struct Array array;

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
        QuickSort(array);
        clock_t sequencial_time2;
        sequencial_time2=clock();
        clock_t sequencial_time;
        sequencial_time=sequencial_time2-sequencial_time1;

        clock_t p_time1;
        p_time1=clock();
        for(j=0;j<N_THREADS;j++)
        {
            pthread_create(&threads[j],NULL,QuickSort, array* array);
        }
        clock_t p_time2;
        p_time2=clock();
        clock_t p_time;
        p_time=p_time2-p_time1;

        runtime_display(sequencial_time, p_time, i);
    }

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

void QuickSort(array* array)
{
    int begin=array.data[0];
    int end=array.data[n-1];
    if(begin<end)
    {
        int half=(end+begin)/2;
        QuickSort(array,begin, half);
        QuickSort(array, half+1, end);
    }
    return;
}

void runtime_display(clock_t sequencial_time, clock_t p_time , int size)
{
    FILE *fp;
   
    fp=fopen("runtime_beszuro_rendezes.txt","a");
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