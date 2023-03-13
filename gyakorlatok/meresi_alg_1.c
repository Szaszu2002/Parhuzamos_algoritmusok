#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void scan(int* array, int size); //megírni!
void notice(int* array, int size);
int sum(int* array, int size);
int min(int* array, int size); //megírni
int max(int* array, int size); //megírni 

int main()
{
    int size=10;
    int array[size];
    scan(array,size);
    notice(array,size);
    int sum;
    sum=sum(array,size);
    printf("\nA tomb elemeinek osszege: %d",sum);
    int min;
    min=min(array,size);
    int max;
    max=max(array,size);
    printf("\nA tomb legkisebb eleme: %d, a tomb legnagyobb eleme: %d",min, max);
    return 0;
}

void scan(int* array, int size)
{
    return;
}

void notice(int* array, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("%d, ", array[i]);
    }
    return;
}

int sum(int* array, int size)
{
    int sum;
    int i;
    for(i=0;i<size;i++)
    {
        sum=sum+array[i];
    }
    return sum;
}
int min(int* array, int size)
{
    int min;
    return min;
}

int max(int* array, int size)
{
    int max;
    return max;
}