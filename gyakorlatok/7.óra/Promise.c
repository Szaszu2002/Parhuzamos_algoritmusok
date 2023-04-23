#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int has_value(promise promise);
int get_value(promise promise);
void get_error();

struct Promise{
    int value;
};

typedef Promise promise;

int main()
{
    struct promise promise;
    if(has_value(promise)==0)
    {
        printf("Nincs eredmeny!");
    }
    else if(has_value(promise)==1)
    {
        printf("Az eredmény: %d \n",get_value(promise));
    }
    else
    {
        get_error();
    }
    return 0;
}

int has_value(promise promise)
{
    if(promise.value==NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_value(promise promise)
{
    if(promise.value==NULL)
    {
        return NULL;
    }
    else
    {
        return promise.value;
    }
}
void get_error()
{
    printf("Hiba tortent!!!");
}