#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int N_THREADS = 10;

int Prime_number(int begin, int end);


int main()
{
    int n=10;
    int array[n];
    pthread_t threads[N_THREADS];
    int i;
    for(i=0;i<N_THREADS;i++)
    {
        pthread_create(&threads[i],NULL,Prime_number,int begin, int end);
    }
    for(i=0;i<N_THREADS;i++)
    {
        pthread_join(thread[i],NULL);
    }
    return 0;
}

int Prime_number(int begin, int end)
{
    int i;
    int prime=0;
    int counter=0;
    for(i=begin;i<end;i++) 
    {
        for(j=1;j<i;j++)
        {
            if(i%j==0)
            {
                counter++;
            } 
        }
        if(counter==2)
        {
            prime++;
        }
    }
    return prime;
}