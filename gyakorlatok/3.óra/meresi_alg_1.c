#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void scan(int* array, int size,int round); 
void notice(int* array, int size);
int Sum(int* array, int size);
int Min(int* array, int size); 
int Max(int* array, int size); 
int Reksum(int* array, int size);
int Rekmin();
int Rekmax();

int main()
{
    int i;
    int round=0;
    for(i=10;i<10000;i+10)
    {
        
        int size=i;
        int array[size];
        scan(array,size,round);
        notice(array,size);
        int sum;
        sum=Sum(array,size);
        printf("\nA tomb elemeinek osszege: %d",sum);
        int min;
        min=Min(array,size);
        int max;
        max=Max(array,size);
        printf("\nA tomb legkisebb eleme: %d, a tomb legnagyobb eleme: %d",min, max);

        round+10;
    }
    
    return 0;
}

void scan(int* array, int size, int round)
{
    FILE *fp;
    fp=fopen("tomb_gyartas.txt","rt");
     if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=round; i<size;i++)
        {
            fscanf(fp,"%d", array[i]);
        }
        fclose(fp);
    }
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

int Sum(int* array, int size)
{
    int sum;
    int i;
    for(i=0;i<size;i++)
    {
        sum=sum+array[i];
    }
    return sum;
}
int Min(int* array, int size)
{
    int min;
    int i;
    min=array[0];
    for(i=1;i<size;i++)
    {
        if(array[i]<min)
        {
            min=array[i];
        }
    }
    return min;
}

int Max(int* array, int size)
{
    int max;
    int i;
    max=array[0];
    for(i=1;i<size;i++)
    {
        if(array[i]>max)
        {
            max=array[i];
        }
    }
    return max;
}
/*int Reksum(int* array, int size)
{
    int sum;
    if(size==2)
    {
        sum=sum+array[0]+array[1];
    }
    else if(size==1)
    {
        sum=sum+array[i];
    }
    else{
        int half=size/2;
        Reksum(array,half);
        Reksum(array,half);
    }

}*/
int Rekmin();
int Rekmax();