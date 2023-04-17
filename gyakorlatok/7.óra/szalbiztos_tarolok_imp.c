#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

list* Request();
void Listing(list* actual);

struct List{
    int *data;
    struct pointer *next;
}
typedef struct List list;
int main()
{
    
    int n=10;
    int array[n];
    struct list *actual = Request();
    Listing(actual);
    return 0;

}
list* Request()
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
void Listing(list* actual)
{
    while(actual=NULL)
    {
        printf("Actual: %d\n",actual->data);
        actual=actual->next;
    }
}