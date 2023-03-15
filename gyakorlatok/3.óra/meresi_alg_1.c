#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void scan(int* array, int size,int round); 
void notice(int* array, int size);
int Sum(int* array, int size);
int Min(int* array, int size); 
int Max(int* array, int size); 
int Reksum(int* array,int begin, int over);
int Rekmin(int* array,int begin, int over);
int Rekmax(int* array,int begin, int over);
void runtime_display(double sumtime, double reksumtime, double mintime, double rekmintime, double maxtime, double rekmaxtime, int size);

int main()
{
    int i;
    int round=0;
    for(i=10;i<10000;i+=10)
    {
        
        int size;
        size=i;
        int array[size];
        scan(array,size,round);
        notice(array,size);

        int sum;
        clock_t sumtime1;
        sumtime1=clock();
        sum=Sum(array,size);
        clock_t sumtime2;
        sumtime2=clock();
        clock_t sumtime;
        sumtime=sumtime2-sumtime1;

        int reksum;
        clock_t reksumtime1;
        reksumtime1=clock();
        reksum=Reksum(array,0,size-1);
        clock_t reksumtime2;
        reksumtime2=clock();
        clock_t reksumtime;
        reksumtime=reksumtime2-reksumtime1;

        printf("\nA tomb elemeinek osszege: %d / %d",sum, reksum);

        int min;
        clock_t mintime1;
        mintime1=clock();
        min=Min(array,size);
        clock_t mintime2;
        mintime2=clock();
        clock_t mintime;
        mintime=mintime2-mintime1;

        int rekmin;
        clock_t rekmintime1;
        rekmintime1=clock();
        rekmin=Rekmin(array,0,size-1);
        clock_t rekmintime2;
        rekmintime2=clock();
        clock_t rekmintime;
        rekmintime=rekmintime2-rekmintime1;

        int max;
        clock_t maxtime1;
        maxtime1=clock();
        max=Max(array,size);
        clock_t maxtime2;
        maxtime2=clock();
        clock_t maxtime;
        maxtime=maxtime2-maxtime1;

        int rekmax;
        clock_t rekmaxtime1;
        rekmaxtime1=clock();
        rekmax=Rekmax(array,0,size-1);
        clock_t rekmaxtime2;
        rekmaxtime2=clock();
        clock_t rekmaxtime;
        rekmaxtime=rekmaxtime2-rekmaxtime1;

        printf("\nA tomb legkisebb eleme: %d / %d, a tomb legnagyobb eleme: %d / %d",min, rekmin, max, rekmax);
        double sumtimei = (double)sumtime / CLOCKS_PER_SEC;
        double reksumtimei = (double)reksumtime / CLOCKS_PER_SEC;
        double mintimei = (double)mintime / CLOCKS_PER_SEC;
        double rekmintimei = (double)rekmintime / CLOCKS_PER_SEC;
        double maxtimei = (double)maxtime / CLOCKS_PER_SEC;
        double rekmaxtimei = (double)rekmaxtime / CLOCKS_PER_SEC;
        runtime_display(sumtimei,reksumtimei,mintimei,rekmintimei,maxtimei,rekmaxtimei,size);
        round+10;
    }
    
    return 0;
}

void scan(int* array, int size, int round)
{
    FILE *fp;
    int i;
    fp=fopen("rand_tomb.txt","r");
     if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0; i<size;i++)
        {
            fscanf(fp,"%d", &array[i]);
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
int Reksum(int* array,int begin, int over)
{
    int sum=0;
    if(begin==over)
    {
        sum=array[over];
    }
    else
    {
        int half=(over+begin)/2;
        sum=sum+Reksum(array,begin,half);
        sum=sum+Reksum(array,half+1,over);
    }
    return sum;
}
int Rekmin(int* array,int begin, int over)
{
    int min=array[begin];
    if(begin!=over)
    {
        int half=(over+begin)/2;
         min=Rekmin(array,begin,half);
        int m;
        m=Rekmin(array,half+1,over);
        if(min>m)
        {
            min=m;
        }
    }
    return min;
}
int Rekmax(int* array,int begin, int over)
{
    int max=array[begin];
    if(begin!=over)
    {
         int half=(over+begin)/2;
        max=Rekmax(array,begin,half);
        int m;
        m=Rekmax(array,half+1,over);
        if(max<m)
        {
            max=m;
        }
    }
    return max;
}
void runtime_display(double sumtime, double reksumtime, double mintime, double rekmintime, double maxtime, double rekmaxtime, int size)
{
    FILE *fp;
    int i;
   
    fp=fopen("runtime_meresi_alg_1.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"%d; %.15lf; %.15lf; %.15lf; %.15lf; %.15lf; %.15lf;\n",size,sumtime,reksumtime,mintime,rekmintime,maxtime,rekmaxtime);
        fclose(fp);
    }
    return;
}