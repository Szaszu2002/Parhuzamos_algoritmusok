#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

const int N_THREADS = 10;

void Upload( int* array, int n);
array_2* Upload_2(array_2 array2);
int Multiply(int* array, int size);
int Rekmultiply(int* array,int begin, int over);
void runtime_display(clock_t sequentialtime, clock_t rektime, clock_t threadtime, clock_t omppartime, clock_t omprektime int size); 

struct Array
{
    int *data;
    int n;
}
typedef struct Array array_2;
int main()
{
    int i;
    for(i=100;i<100000;i+=100)
    {
        int n=i;
        int array[n];
        int multiply;
        int rekmultiply;
        int multiplyomp;
        int ompthread;
        int omprek;
        struct array_2 *array2=Upload_2();
        array2->n=i;
        pthread_t threads[N_THREADS];
        pthread_t threadsomp[N_THREADS];
        Upload(array, n);

        clock_t sequentialtime1;
        sequentialtime1=clock();
        multiply=Multiply(array, n);
        clock_t sequentialtime2;
        sequentialtime2=clock();
        clock_t sequentialtime;
        sequentialtime=sequentialtime2-sequentialtime1;

        clock_t rektime1;
        rektime1=clock();
        rekmultiply=Rekmultiply(array,0,n);
        clock_t rektime2;
        rektime2=clock();
        clock_t rektime;
        rektime=rektime2-rektime1;

        clock_t threadtime1;
        threadtime1=clock();
        pthread_create(&threads[1],NULL,Rekmultiply,array_2);
        pthread_join(threads[1],NULL);
        clock_t threadtime2;
        threadtime2=clock();
        clock_t threadtime;
        threadtime=threadtime2-threadtime1;

        clock_t omppartime1;
        omppartime1=clock();
        #pragma omp parallel
        {
            int j;
            for(j=0;j<N_THREADS;j++)
            {
                ompthread=pthread_create(&threadsomp[j],NULL,Multiply,array_2);
            }
            for(j=0;j<N_THREADS;j++)
            {
                pthread_join(threadsomp[j],NULL);
            }
        }
        clock_t omppartime2;
        omppartime2=clock();
        clock_t omppartime;
        omppartime=omppartime2-omppartime1;

        clock_t omprektime1;
        omprektime1=clock();
        #pragma omp rek
        {
            omprek=Rekmultiply(array,0,n);
        }
        clock_t omprektime2;
        omprektime2=clock();
        clock_t omprektime;
        omprektime=omprektime2-omprektime1;

        runtime_display(sequentialtime,rektime,threadtime,omppartime, omprektime,n);
    }
}

void Upload( int* array, int n)
{
    srand(time(NULL));
    int i;
    int ok=0;
    for(i=0; i<n; i++)
    { 
        array[i] = rand();
    }
    return;
}
array_2* Upload_2()
{
    srand(time(NULL));
    int i;
    for(i=0;i<array2->n;i++)
    {
        array2->data[i]=rand()
    }
    return array2;
}

int Multiply(int* array, int size)
{
    int multiply;
    int i;
    for(i=0;i<size;i++)
    {
        multiply=multiply*array[i];
    }
    return multiply;
}

int Rekmultiply(int* array,int begin, int over)
{
    int rek=0;
    if(begin==over)
    {
        rek=array[over];
    }
    else
    {
        int half=(over+begin)/2;
        rek=rek*Rekmultiply(array,begin,half);
        rek=rek*Rekmultiply(array,half+1,over);
    }
    return rek;
}
void runtime_display(clock_t sequentialtime, clock_t rektime, clock_t threadtime, clock_t omppartime, clock_t omprektime, int size)
{
    FILE *fp;
   
    fp=fopen("runtime_openmp_1.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n%d; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf\n",size, sequentialtime, rektime, threadtime, omppartime, omprektime);
        fclose(fp);
    }
    return;
}