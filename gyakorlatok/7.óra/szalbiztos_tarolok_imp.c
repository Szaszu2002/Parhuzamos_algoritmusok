#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void Upload(array* array1);
list* Request();
void Listing(list* actual);
int SearchList(list* actual, int question);

struct Array{
    int *data;
    int size;
};
struct List{
    int *data;
    struct pointer *next;
};
struct Queue{
    char *data;
    int n;
};
struct Stract{
    char *data;
    int n;
};

typedef struct Array array;
typedef struct List list;

int main()
{
    int n=10;
    struct array *array1;
    Upload(array1);
    struct list *actual = Request();
    Listing(actual);

    return 0;
}

list* Request() //lista feltöltése
{
    struct list *first, *actual, *new;
    int number=0;
    do{
        printf("Adja meg a szamot! ");
        scanf(%d,&number);
        if(number!=0)
        {
            new=(list*)malloc(sizeof(list*));
            new->data=number;
            new->next=NULL;
            if(first==0)
            {
                first=new;
            }
            else
            {
                actual->next=new;
            }
            actual=new;
        }

    }while(number!=0);
    actual=first;
    return actual;
}

void Listing(list* actual) //lista kiíratása
{
    while(actual=NULL)
    {
        printf("Actual: %d\n",actual->data);
        actual=actual->next;
    }
}

void Upload(array* array1) //tömb feltöltése
{
    srand(time(NULL));
    int i;
    int ok=0;
    for(i=0; i<array1->n; i++)
    { 
        array1->data[i] = rand();
    }
    return;
}

int SearchList(list* actual, int question)
{
    int i;
    int exists=0;
    while(actual=NULL)
    {
        if(actual==question)
        {
            exists++;
        }
        actual=actual->next;
    }
    return exists;
}