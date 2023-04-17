#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

data* ScanFile();//szöveg beolvasása
data2* EncodingText( data *uncode);//szöveg kódolása
void CodedFileDump(data2 *coded);//kódolt szöveg kiírása egy fájlba
//dekódolás
//dekódolt szöveg kiírása egy fájlba 
void runtime_display(clock_t , clock_t , int n);     //futási idők kiírása egy fájlba

struct Data
{
    char *character;
    int n;
}
struct Data2
{
    int *firstnumber;
    int *secondnumber;
    int n;
}

typedef struct Data data;
typedef struct Data2 data2;

int main()
{
    struct data *uncoded=Scanfile();
    struct data2 *coded=EncodingText(uncoded);
    runtime_display();
    return 0;
}

void runtime_display(clock_t ,clock_t , int n)
{
    FILE *fp;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n%d; %.2lf; %.2lf\n",size,);
        fclose(fp);
    }
    return;
}

data* ScanFile()
{
    struct data *uncoded;
    FILE *fp;

    fp=fopen("text.txt","r");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fread();    //megírni !!!
        fclose();
    }
    return uncoded;
}

data2* EncodingText( data *uncode)
{
    struct data2 coded;
    coded->n=uncoded->n;
    int i;
    int prime=1039;
    for(i=0;i<uncoded->n,i++)
    {
        if(uncoded->character[i] == " ")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=0;
        }
        else if(uncoded->character[i] == "!")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "%%")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "(")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == ")")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == "+")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=11;
        }
        else if(uncoded->character[i] == ",")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=12;
        }
        else if(uncoded->character[i] == "-")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=13;
        }
        else if(uncoded->character[i] == ".")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=14;
        }
        else if(uncoded->character[i] == "/")
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=15;
        }
        else if(uncoded->character[i] == "0")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=0;
        }
        else if(uncoded->character[i] == "1")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "2")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=2;
        }
        else if(uncoded->character[i] == "3")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=3;
        }
        else if(uncoded->character[i] == "4")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=4;
        }
        else if(uncoded->character[i] == "5")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "6")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=6;
        }
        else if(uncoded->character[i] == "7")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=7;
        }
        else if(uncoded->character[i] == "8")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == "9")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == ":")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=10;
        }
        else if(uncoded->character[i] == ";")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=11;
        }
        else if(uncoded->character[i] == "<")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=12;
        }
        else if(uncoded->character[i] == "=")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=13;
        }
        else if(uncoded->character[i] == ">")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=14;
        }
        else if(uncoded->character[i] == "?")
        {
            coded->firstnumber[i]=3;
            coded->secondnumber[i]=15;
        }
        else if(uncoded->character[i] == "@")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=0;
        }
        else if(uncoded->character[i] == "A" || "Á")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "B")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=2;
        }
        else if(uncoded->character[i] == "C")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=3;
        }
        else if(uncoded->character[i] == "D")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=4;
        }
        else if(uncoded->character[i] == "E" || "É")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "F")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=6;
        }
        else if(uncoded->character[i] == "G")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=7;
        }
        else if(uncoded->character[i] == "H")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == "I")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == "J")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=10;
        }
        else if(uncoded->character[i] == "K")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=11;
        }
        else if(uncoded->character[i] == "L")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=12;
        }
        else if(uncoded->character[i] == "M")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=13;
        }
        else if(uncoded->character[i] == "N")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=14;
        }
        else if(uncoded->character[i] == "O" || "Ó" || "Ö" || "Ő")
        {
            coded->firstnumber[i]=4;
            coded->secondnumber[i]=15;
        }
        else if(uncoded->character[i] == "P")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=0;
        }
        else if(uncoded->character[i] == "Q")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "R")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=2;
        }
        else if(uncoded->character[i] == "S")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=3;
        }
        else if(uncoded->character[i] == "T")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=4;
        }
        else if(uncoded->character[i] == "U" || "Ú" || "Ü" || "Ű")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "V")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=6;
        }
        else if(uncoded->character[i] == "W")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=7;
        }
        else if(uncoded->character[i] == "X")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == "Y")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == "Z")
        {
            coded->firstnumber[i]=5;
            coded->secondnumber[i]=10;
        }
        else if(uncoded->character[i] == "a" || "á")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "b")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=2;
        }
        else if(uncoded->character[i] == "c")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=3;
        }
        else if(uncoded->character[i] == "d")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=4;
        }
        else if(uncoded->character[i] == "e" || "é")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "f")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=6;
        }
        else if(uncoded->character[i] == "g")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=7;
        }
        else if(uncoded->character[i] == "h")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == "i" || "í")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == "j")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=10;
        }
        else if(uncoded->character[i] == "k")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=11;
        }
        else if(uncoded->character[i] == "l")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=12;
        }
        else if(uncoded->character[i] == "m")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=13;
        }
        else if(uncoded->character[i] == "n")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=14;
        }
        else if(uncoded->character[i] == "o" || "ó" || "ö" || "ő")
        {
            coded->firstnumber[i]=6;
            coded->secondnumber[i]=15;
        }
        else if(uncoded->character[i] == "p")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=0;
        }
        else if(uncoded->character[i] == "q")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=1;
        }
        else if(uncoded->character[i] == "r")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=2;
        }
        else if(uncoded->character[i] == "s")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=3;
        }
        else if(uncoded->character[i] == "t")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=4;
        }
        else if(uncoded->character[i] == "u" || "ú" || "ü" || "ű")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=5;
        }
        else if(uncoded->character[i] == "v")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=6;
        }
        else if(uncoded->character[i] == "w")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=7;
        }
        else if(uncoded->character[i] == "x")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=8;
        }
        else if(uncoded->character[i] == "y")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=9;
        }
        else if(uncoded->character[i] == "z")
        {
            coded->firstnumber[i]=7;
            coded->secondnumber[i]=10;
        }
        else
        {
            coded->firstnumber[i]=2;
            coded->secondnumber[i]=3;
        }
    }
    //titkosítás rész !!!
    return coded;
}

void CodedFileDump(data2 *coded)
{
    FILE *fp;

    fp=fopen("coded_text.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp, "\n%d %d", coded->firstnumber, coded->secondnumber);
        fclose(fp);
    }
    return;
}