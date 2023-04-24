#include <stdio.h>
#include <stdlib.h>

void Upload( array* array);
void CombsTogether(array* array_1; array* array_2); //megírni!!!

struct Array{
    int *data;
    int size;
};

const int N_THREADS = 10;
typedef struct Array array;

int main()
{
    int n=10;
    struct array array_1*;
    struct array array_2*;
    array_2.size=n;
    array_1.size=n;

    Upload(array_1);
    Upload(array_2);
    CombsTogether(array_1, array_2);

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

void CombsTogether(array* array_1; array* array_2)
{

}