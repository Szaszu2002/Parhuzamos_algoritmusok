#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

data* ScanFile();//szöveg beolvasása
data2* EncodingText( data *uncoded);//szöveg kódolása
void CodedFileDump(data2 *coded);//kódolt szöveg kiírása egy fájlba
data* Decoding(data2 *coded);//dekódolás
void DecodedFileDump(data *uncoded);//dekódolt szöveg kiírása egy fájlba 
void runtime_display(clock_t , clock_t );     //futási idők kiírása egy fájlba

struct Data
{
    char *character;
    char *new;
    int n;
}
struct Data2
{
    int *firstnumber;
    int *secondnumber;
    int *code;
    int n;
}

typedef struct Data data;

typedef struct Data2 data2;

int main()
{
    struct data *uncoded=Scanfile();
    struct data2 *coded=EncodingText(uncoded);
    CodedFileDump(coded);
    uncoded=Decoding(coded);
    DecodedFileDump(uncoded);
    runtime_display();
    return 0;
}

void runtime_display(clock_t ,clock_t )
{
    FILE *fp;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf;",,);
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
    int p=1039;
    int q=2617;
    int n=p*q,e=11;
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
    for(i=0;i<coded->n;i++)
    {
        int M=(16*coded->firstnumber[i])+coded->firstnumber[i];
        int C;

        C=1%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        coded->code[i]=C;
    }

    return coded;
}

void CodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;

    fp=fopen("coded_text.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n");
        for(i=0;i<coded->n;i++)
        {
            fprintf(fp, "%d ", coded->code[i]);
        }
        fclose(fp);
    }
    return;
}

data* Decoding(data2 *coded)
{
    int i;
    int p=1039;
    int q=2617;
    int n=p*q,e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987
    
    for(i=1;i<coded->n;i++)
    {
        int C;
        int bin=0;
        C=1%n;  //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //0
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //0
        C=(C*C)%n; //0
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //0
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //0
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //0
        C=(C*C)%n; //0
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        C=(C*C)%n; //1
        C=(coded->code[i]*C)%n;
        if(C == 32)
        {
            uncoded->new[i]=" ";
        }
        else if(C == 33)
        {
            uncoded->new[i]="!";
        }
        else if(C == 35)
        {
            uncoded->new[i]="%%";
        }
        else if(C == 40)
        {
            uncoded->new[i]="(";
        }
        else if(C == 41)
        {
            uncoded->new[i]=")";
        }
        else if(C == 43)
        {
            uncoded->new[i]="+";
        }
        else if(C == 44)
        {
            uncoded->new[i]=",";
        }
        else if(C == 45)
        {
            uncoded->new[i]="-";
        }
        else if(C == 46)
        {
            uncoded->new[i]=".";
        }
        else if(C == 47)
        {
            uncoded->new[i]="/";
        }
        else if(C == 48)
        {
            uncoded->new[i]="0";
        }
        else if(C == 49)
        {
            uncoded->new[i]="1";
        }
        else if(C == 50)
        {
            uncoded->new[i]="2";
        }
        else if(C == 51)
        {
            uncoded->new[i]="3";
        }
        else if(C == 52)
        {
            uncoded->new[i]="4";
        }
        else if(C == 53)
        {
            uncoded->new[i]="5";
        }
        else if(C == 54)
        {
            uncoded->new[i]="6";
        }
        else if(C == 55)
        {
            uncoded->new[i]="7";
        }
        else if(C == 56)
        {
            uncoded->new[i]="8";
        }
        else if(C == 57)
        {
            uncoded->new[i]="9";
        }
        else if(C == 58)
        {
            uncoded->new[i]=":";
        }
        else if(C == 59)
        {
            uncoded->new[i]=";";
        }
        else if(C == 60)
        {
            uncoded->new[i]="<";
        }
        else if(C == 61)
        {
            uncoded->new[i]="=";
        }
        else if(C == 62)
        {
            uncoded->new[i]=">";
        }
        else if(C == 63)
        {
            uncoded->new[i]="?";
        }
        else if(C == 64)
        {
            uncoded->new[i]="@";
        }
        else if(C == 65)
        {
            uncoded->new[i]="A";
        }
        else if(C == 66)
        {
            uncoded->new[i]="B";
        }
        else if(C == 67)
        {
            uncoded->new[i]="C";
        }
        else if(C == 68)
        {
            uncoded->new[i]="D";
        }
        else if(C == 69)
        {
            uncoded->new[i]="E";
        }
        else if(C == 70)
        {
            uncoded->new[i]="F";
        }
        else if(C == 71)
        {
            uncoded->new[i]="G";
        }
        else if(C == 72)
        {
            uncoded->new[i]="H";
        }
        else if(C == 73)
        {
            uncoded->new[i]="I";
        }
        else if(C == 74)
        {
            uncoded->new[i]="J";
        }
        else if(C == 75)
        {
            uncoded->new[i]="K";
        }
        else if(C == 76)
        {
            uncoded->new[i]="L";
        }
        else if(C == 77)
        {
            uncoded->new[i]="M";
        }
        else if(C == 78)
        {
            uncoded->new[i]="N";
        }
        else if(C == 79)
        {
            uncoded->new[i]="O";
        }
        else if(C == 80)
        {
            uncoded->new[i]="P";
        }
        else if(C == 81)
        {
            uncoded->new[i]="Q";
        }
        else if(C == 82)
        {
            uncoded->new[i]="R";
        }
        else if(C == 83)
        {
            uncoded->new[i]="S";
        }
        else if(C == 84)
        {
            uncoded->new[i]="T";
        }
        else if(C == 85)
        {
            uncoded->new[i]="U";
        }
        else if(C == 86)
        {
            uncoded->new[i]="V";
        }
        else if(C == 87)
        {
            uncoded->new[i]="W";
        }
        else if(C == 88)
        {
            uncoded->new[i]="X";
        }
        else if(C == 89)
        {
            uncoded->new[i]="Y";
        }
        else if(C == 90)
        {
            uncoded->new[i]="Z";
        }
        else if(C == 97)
        {
            uncoded->new[i]="a";
        }
        else if(C == 98)
        {
            uncoded->new[i]="b";
        }
        else if(C == 99)
        {
            uncoded->new[i]="c";
        }
        else if(C == 100)
        {
            uncoded->new[i]="d";
        }
        else if(C == 101)
        {
            uncoded->new[i]="e";
        }
        else if(C == 102)
        {
            uncoded->new[i]="f";
        }
        else if(C == 103)
        {
            uncoded->new[i]="g";
        }
        else if(C == 104)
        {
            uncoded->new[i]="h";
        }
        else if(C == 105)
        {
            uncoded->new[i]="i";
        }
        else if(C == 106)
        {
            uncoded->new[i]="j";
        }
        else if(C == 107)
        {
            uncoded->new[i]="k";
        }
        else if(C == 108)
        {
            uncoded->new[i]="l";
        }
        else if(C == 109)
        {
            uncoded->new[i]="m";
        }
        else if(C == 110)
        {
            uncoded->new[i]="n";
        }
        else if(C == 111)
        {
            uncoded->new[i]="o";
        }
        else if(C == 112)
        {
            uncoded->new[i]="p";
        }
        else if(C == 113)
        {
            uncoded->new[i]="q";
        }
        else if(C == 114)
        {
            uncoded->new[i]="r";
        }
        else if(C == 115)
        {
            uncoded->new[i]="s";
        }
        else if(C == 116)
        {
            uncoded->new[i]="t";
        }
        else if(C == 117)
        {
            uncoded->new[i]="u";
        }
        else if(C == 118)
        {
            uncoded->new[i]="v";
        }
        else if(C == 119)
        {
            uncoded->new[i]="w";
        }
        else if(C == 120)
        {
            uncoded->new[i]="x";
        }
        else if(C == 121)
        {
            uncoded->new[i]="y";
        }
        else if(C == 122)
        {
            uncoded->new[i]="z";
        }
        else
        {
            uncoded->new[i]="#";
        }
    }
    return uncoded;
}

void DecodedFileDump(data *uncoded)
{
    FILE *fp;
    int i;

    fp=fopen("decoded_text.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n");
        for(i=0;i<uncoded->n;i++)
        {
            fprintf(fp, "%d ", uncoded->new[i]);
        }
        fclose(fp);
    }
    return;
}