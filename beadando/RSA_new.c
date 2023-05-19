#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct data
{
    char *character;
    char *new;
    char *new_o;
    char *new_p;
    int n;
}data;
typedef struct data2
{
    int *number;
    int *number_o;
    int *number_p;
    int *code;
    int *code_o;
    int *code_p;
    int n;
}data2;
typedef struct helper
{
    char character;
    int i;
    int number;
    int code;
    char new;
}helper;

void Scanfile(data* uncoded);//szöveg beolvasása
void EncodingText( data *uncoded,data2 *code);//szöveg kódolása
void ParEncodingText( helper *help);
void CodedFileDump(data2 *coded);//kódolt szöveg kiírása egy fájlba
void PCodedFileDump(data2 *coded);
void OCodedFileDump(data2 *coded);
void Decoding(data2 *coded, data *uncoded);//dekódolás
void ParDecoding(helper *help);
void DecodedFileDump(data *uncoded);//dekódolt szöveg kiírása egy fájlba 
void ODecodedFileDump(data *uncoded);
void PDecodedFileDump(data *uncoded);
void runtime_display(clock_t allsequencialtime, clock_t palltime, clock_t openmpalltime, clock_t encoding_time, clock_t pencoding_time, clock_t openmpencoding_time, clock_t decoding_time, clock_t pdecoding_time, clock_t openmpdecoding_time);     //futási idők kiírása egy fájlba



int main()
{
    clock_t allsequencialtime;  //
    clock_t palltime; //
    clock_t openmpalltime;
    clock_t start_time; //
    clock_t pstart_time; //
    clock_t openmpstart_time;
    clock_t encoding_time1; //
    clock_t encoding_time2; //
    clock_t encoding_time;  //
    clock_t pencoding_time1; //
    clock_t pencoding_time2;
    clock_t pencoding_time;
    clock_t openmpencoding_time1;
    clock_t openmpencoding_time2;
    clock_t openmpencoding_time;
    clock_t decoding_time1; //
    clock_t decoding_time2; //
    clock_t decoding_time;  //
    clock_t pdecoding_time1;
    clock_t pdecoding_time2;
    clock_t pdecoding_time;
    clock_t openmpdecoding_time1;
    clock_t openmpdecoding_time2;
    clock_t openmpdecoding_time;
    clock_t end_time;
    clock_t pend_time;
    clock_t openmpend_time;
    clock_t read_time;
    clock_t read_time1;
    clock_t read_time2;
    int i;
    int j;
    struct helper help;
    
    

    read_time1=clock();
    struct data uncoded;
    uncoded.character=malloc(sizeof(char)*100000);
    uncoded.new=malloc(sizeof(char)*100000);
    //printf("Before\n");
    Scanfile(&uncoded);
    //printf("Beolvas");
    read_time2=clock();
    read_time=read_time2-read_time1;
    
    pthread_t threads[uncoded.n];
    pthread_t threadsomp[uncoded.n];

    start_time=clock();
    encoding_time1=clock();
    struct data2 coded;
    coded.code=malloc(sizeof(int)*100000);
    coded.number=malloc(sizeof(int)*100000);
    EncodingText(&uncoded,&coded);
    encoding_time2=clock();
    encoding_time=encoding_time2-encoding_time1;

    CodedFileDump(&coded);
    
    decoding_time1=clock();
    Decoding(&coded,&uncoded);
    
    decoding_time2=clock();
    decoding_time=decoding_time2-decoding_time1;
    DecodedFileDump(&uncoded);
    end_time=clock();
    allsequencialtime=(end_time-start_time)+read_time;
    printf(" end ");

    
    //párhuzamos rész !!!
    
    pstart_time=clock();
    pencoding_time1=clock();
    for(i=0;i<uncoded.n;i++)
    {
        help.i=i;
        help.character=uncoded.character[i];
        printf("\nThe struct size: %d",uncoded.n);
        pthread_create(&threads[i],NULL,ParEncodingText, &help);
        printf("\n%d", help.number); //Idáig jut el !!!
        coded.number_p[i]=help.number;
        printf("\n%d",help.code);
        coded.code_p[i]=help.code;
    }
    pencoding_time2=clock();
    pencoding_time=pencoding_time2-pencoding_time1;
    printf(" 128 ");
    PCodedFileDump(&coded); //itt áll meg!!!
    printf(" 130 ");
    pdecoding_time1=clock();
    for(i=0;i<coded.n;i++)
    {
        help.i=i;
        //printf("\n i=%d",help.i);
        help.code=coded.code_p[i];      //itt megáll!!!
        //printf("\n%d",help.code);
        pthread_create(&threads[i],NULL,ParDecoding, &help);
        uncoded.new_p[i]=help.new;
    }
    printf( " 138 ");
    pdecoding_time2=clock();
    pdecoding_time=pdecoding_time2-pdecoding_time1;

    PDecodedFileDump(&uncoded);
    pend_time=clock();
    palltime=(pend_time-pstart_time)+read_time;
    printf(" end "); 

    //OPENMP rész !!!

    openmpstart_time=clock();
    openmpencoding_time1=clock();
    printf("\nThe struct size: %d", coded.n);
    #pragma omp parallel
    {
        //printf("\n166 ");
        printf("\n1The struct size: %d", coded.n);
        #pragma omp for
        for(j=0;j<coded.n;j++)
        {
            printf("\n2The struct size: %d", coded.n);
            help.i=j;
            help.character=uncoded.character[j];
            ParEncodingText(&help);
            coded.number_o[i]=help.number;      //Itt valamiért hiba van!!!
            printf("\n140");
            coded.code_o[i]=help.code;
        }
        printf("\n175 ");
    } 
    openmpencoding_time2=clock();
    openmpencoding_time=openmpencoding_time2-openmpencoding_time1;
    printf("\n175 ");
    OCodedFileDump(&coded);
    printf("\n177 ");
    openmpdecoding_time1=clock();
    
    #pragma omp parallel for
    for(j=0;j<coded.n;j++)
    {
        help.i=i;
        help.code=coded.code_o[j];
        printf("\n198");
        ParDecoding(&help);
        printf("\n200");
        uncoded.new_o[i]=help.new;      //Valamiért megakad
        printf("\n202");
    }
    printf("\n 201");
    openmpdecoding_time2=clock();
    openmpdecoding_time=openmpdecoding_time2-openmpdecoding_time1;
    
    ODecodedFileDump(&uncoded);
    openmpend_time=clock();
    openmpalltime=(openmpend_time-openmpstart_time)+read_time;
    printf( "end" );

   

    free(uncoded.character);
    free(uncoded.new);
    free(coded.code);
    free(coded.number);
    
    runtime_display(allsequencialtime, palltime, openmpalltime, encoding_time, pencoding_time, openmpencoding_time, decoding_time, pdecoding_time, openmpdecoding_time);
    printf(" all end ");
    return 0;
}

void runtime_display(clock_t allsequencialtime, clock_t palltime, clock_t openmpalltime, clock_t encoding_time, clock_t pencoding_time, clock_t openmpencoding_time, clock_t decoding_time, clock_t pdecoding_time, clock_t openmpdecoding_time)
{
    FILE *fp;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf", allsequencialtime, palltime, openmpalltime, encoding_time, pencoding_time, openmpencoding_time, decoding_time, pdecoding_time, openmpdecoding_time);
        fclose(fp);
    }
    return;
}

void Scanfile(data* uncoded)
{
    int size=0, number_of_lines=0, i=0;
    char ch;
    FILE *fp;
    //printf("1size= %d\n",size);
    fp=fopen("text.txt","r");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        while((ch = fgetc(fp)) != EOF) 
        {
            
            //printf("i");
            uncoded->character[i]=ch; 
            //printf("%c",ch);
            //printf("i");
            i++;
            //printf("i");
            size++; 
            //printf("i");
            //printf("2size= %d\n",size);
        }
        if (size==0) 
        {
            printf("\nA fájl üres");
            return;
        }
        
        //printf("4size= %d\n",size);
        fclose(fp);
        //printf("5size= %d\n",size);
        uncoded->n=size;
    }
    return;
}

void EncodingText( data *uncoded, data2* code)
{
    
    code->n=(uncoded->n);
    int i;
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    for(i=0;i<(uncoded->n);i++)
    {
        switch(uncoded->character[i])
        {
            case ' ':
                code->number[i]=32;
                break;
            case '!':
                code->number[i]=33;
                break;
            case '%':
                code->number[i]=37;
                break;
            case '(':
                code->number[i]=40;
                break;
            case ')':
                code->number[i]=41;
                break;
            case '+':
                code->number[i]=43;
                break;
            case ',':
                code->number[i]=44;
                break;
            case '-':
                code->number[i]=45;
                break;
            case '.':
                code->number[i]=46;
                break;
            case '/':
                code->number[i]=47;
                break;
            case '0':
                code->number[i]=48;
                break;
            case '1':
                code->number[i]=49;
                break;
            case '2':
                code->number[i]=50;
                break;
            case '3':
                code->number[i]=51;
                break;
            case '4':
                code->number[i]=52;
                break;
            case '5':
                code->number[i]=53;
                break;
            case '6':
                code->number[i]=54;
                break;
            case '7':
                code->number[i]=55;
                break;
            case '8':
                code->number[i]=56;
                break;
            case '9':
                code->number[i]=57;
                break;
            case ':':
                code->number[i]=58;
                break;
            case ';':
                code->number[i]=59;
                break;
            case '<':
                code->number[i]=60;
                break;
            case '=':
                code->number[i]=61;
                break;
            case '>':
                code->number[i]=62;
                break;
            case '?':
                code->number[i]=63;
                break;
            case '@':
                code->number[i]=64;
                break;
            case 'A':
                code->number[i]=65;
                break;
            case 'B':
                code->number[i]=66;
                break;
            case 'C':
                code->number[i]=67;
                break;
            case 'D':
                code->number[i]=68;
                break;
            case 'E':
                code->number[i]=69;
                break;
            case 'F':
                code->number[i]=70;
                break;
            case 'G':
                code->number[i]=71;
                break;
            case 'H':
                code->number[i]=72;
                break;
            case 'I':
                code->number[i]=73;
                break;
            case 'J':
                code->number[i]=74;
                break;
            case 'K':
                code->number[i]=75;
                break;
            case 'L':
                code->number[i]=76;
                break;
            case 'M':
                code->number[i]=77;
                break;
            case 'N':
                code->number[i]=78;
                break;
            case 'O':
                code->number[i]=79;
                break;
            case 'P':
                code->number[i]=80;
                break;
            case 'Q':
                code->number[i]=81;
                break;
            case 'R':
                code->number[i]=82;
                break;
            case 'S':
                code->number[i]=83;
                break;
            case 'T':
                code->number[i]=84;
                break;
            case 'U':
                code->number[i]=85;
                break;
            case 'V':
                code->number[i]=86;
                break;
            case 'W':
                code->number[i]=87;
                break;
            case 'X':
                code->number[i]=88;
                break;
            case 'Y':
                code->number[i]=89;
                break;
            case 'Z':
                code->number[i]=90;
                break;
            case 'a':
                code->number[i]=97;
                break;
            case 'b':
                code->number[i]=98;
                break;
            case 'c':
                code->number[i]=99;
                break;
            case 'd':
                code->number[i]=100;
                break;
            case 'e':
                code->number[i]=101;
                break;
            case 'f':
                code->number[i]=102;
                break;
            case 'g':
                code->number[i]=103;
                break;
            case 'h':
                code->number[i]=104;
                break;
            case 'i':
                code->number[i]=105;
                break;
            case 'j':
                code->number[i]=106;
                break;
            case 'k':
                code->number[i]=107;
                break;
            case 'l':
                code->number[i]=108;
                break;
            case 'm':
                code->number[i]=109;
                break;
            case 'n':
                code->number[i]=110;
                break;
            case 'o':
                code->number[i]=111;
                break;
            case 'p':
                code->number[i]=112;
                break;
            case 'q':
                code->number[i]=113;
                break;
            case 'r':
                code->number[i]=114;
                break;
            case 's':
                code->number[i]=115;
                break;
            case 't':
                code->number[i]=116;
                break;
            case 'u':
                code->number[i]=117;
                break;
            case 'v':
                code->number[i]=118;
                break;
            case 'w':
                code->number[i]=119;
                break;
            case 'x':
                code->number[i]=120;
                break;
            case 'y':
                code->number[i]=121;
                break;
            case 'z':
                code->number[i]=122;
                break;
            default:
                code->number[i]=35;
                break;
        }
    }
    //titkosítás rész !!!
    for(i=0;i<(code->n);i++)
    {
        int M=code->number[i];
        long C=1;

        C=1%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        code->code[i]=(int)C;
    }
    printf("Encoding!");
    return;
}

void ParEncodingText( helper *help)
{
   int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;

        switch(help->character)
        {
            case ' ':
                help->number=32;
                break;
            case '!':
                help->number=33;
                break;
            case '%':
                help->number=37;
                break;
            case '(':
                help->number=40;
                break;
            case ')':
                help->number=41;
                break;
            case '+':
                help->number=43;
                break;
            case ',':
                help->number=44;
                break;
            case '-':
                help->number=45;
                break;
            case '.':
                help->number=46;
                break;
            case '/':
                help->number=47;
                break;
            case '0':
                help->number=48;
                break;
            case '1':
                help->number=49;
                break;
            case '2':
                help->number=50;
                break;
            case '3':
                help->number=51;
                break;
            case '4':
                help->number=52;
                break;
            case '5':
                help->number=53;
                break;
            case '6':
                help->number=54;
                break;
            case '7':
                help->number=55;
                break;
            case '8':
                help->number=56;
                break;
            case '9':
                help->number=57;
                break;
            case ':':
                help->number=58;
                break;
            case ';':
                help->number=59;
                break;
            case '<':
                help->number=60;
                break;
            case '=':
                help->number=61;
                break;
            case '>':
                help->number=62;
                break;
            case '?':
                help->number=63;
                break;
            case '@':
                help->number=64;
                break;
            case 'A':
                help->number=65;
                break;
            case 'B':
                help->number=66;
                break;
            case 'C':
                help->number=67;
                break;
            case 'D':
                help->number=68;
                break;
            case 'E':
                help->number=69;
                break;
            case 'F':
                help->number=70;
                break;
            case 'G':
                help->number=71;
                break;
            case 'H':
                help->number=72;
                break;
            case 'I':
                help->number=73;
                break;
            case 'J':
                help->number=74;
                break;
            case 'K':
                help->number=75;
                break;
            case 'L':
                help->number=76;
                break;
            case 'M':
                help->number=77;
                break;
            case 'N':
                help->number=78;
                break;
            case 'O':
                help->number=79;
                break;
            case 'P':
                help->number=80;
                break;
            case 'Q':
                help->number=81;
                break;
            case 'R':
                help->number=82;
                break;
            case 'S':
                help->number=83;
                break;
            case 'T':
                help->number=84;
                break;
            case 'U':
                help->number=85;
                break;
            case 'V':
                help->number=86;
                break;
            case 'W':
                help->number=87;
                break;
            case 'X':
                help->number=88;
                break;
            case 'Y':
                help->number=89;
                break;
            case 'Z':
                help->number=90;
                break;
            case 'a':
                help->number=97;
                break;
            case 'b':
                help->number=98;
                break;
            case 'c':
                help->number=99;
                break;
            case 'd':
                help->number=100;
                break;
            case 'e':
                help->number=101;
                break;
            case 'f':
                help->number=102;
                break;
            case 'g':
                help->number=103;
                break;
            case 'h':
                help->number=104;
                break;
            case 'i':
                help->number=105;
                break;
            case 'j':
                help->number=106;
                break;
            case 'k':
                help->number=107;
                break;
            case 'l':
                help->number=108;
                break;
            case 'm':
                help->number=109;
                break;
            case 'n':
                help->number=110;
                break;
            case 'o':
                help->number=111;
                break;
            case 'p':
                help->number=112;
                break;
            case 'q':
                help->number=113;
                break;
            case 'r':
                help->number=114;
                break;
            case 's':
                help->number=115;
                break;
            case 't':
                help->number=116;
                break;
            case 'u':
                help->number=117;
                break;
            case 'v':
                help->number=118;
                break;
            case 'w':
                help->number=119;
                break;
            case 'x':
                help->number=120;
                break;
            case 'y':
                help->number=121;
                break;
            case 'z':
                help->number=122;
                break;
            default:
                help->number=35;
                break;
        }
    //titkosítás rész !!!
    
    int M=help->number;
    long C=1;

    C=1%n;
    C=(M*C)%n;
    C=(C*C)%n;
    C=(C*C)%n;
    C=(M*C)%n;
    C=(C*C)%n;
    C=(M*C)%n;
    help->code=(int)C;
    //printf("ParEncoding!");
    return;
}

void CodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;
    //printf(" 951 ");
    fp=fopen("coded_text.txt","a");
    //printf(" 953 ");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n");
        for(i=0;i<coded->n;i++)
        {
            //printf(" j ");
            fprintf(fp, "%d ", coded->code[i]);
        }
        fclose(fp);
    }
    //printf("codedf");
    return;
}
void OCodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;
    //printf(" 951 ");
    fp=fopen("o_coded_text.txt","a");
    //printf(" 953 ");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n");
        for(i=0;i<coded->n;i++)
        {
            //printf(" j ");
            fprintf(fp, "%d ", coded->code_o[i]);
        }
        fclose(fp);
    }
    //printf("codedf");
    return;
}
void PCodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;
    printf(" 951 ");
    fp=fopen("p_coded_text.txt","a");
    printf(" 953 ");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n");
        for(i=0;i<coded->n;i++)
        {
            printf(" j ");
            fprintf(fp, "%d ", coded->code_p[i]); //idáig ment el!!!
        }
        fclose(fp);
    }
    printf("codedf");
    return;
}
void Decoding(data2 *coded, data *uncoded)
{
    int i;
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987

    for(i=1;i<coded->n;i++)
    {
        long C;
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

        switch(C)
        {
            case 32:
                uncoded->new[i]=' ';
                break;
            case 33:
                uncoded->new[i]='!';
                break;
            case 35:
                uncoded->new[i]='%';
                break;
            case 40:
                uncoded->new[i]='(';
                break;
            case 41:
                uncoded->new[i]=')';
                break;
            case 43:
                uncoded->new[i]='+';
                break;
            case 44:
                uncoded->new[i]=',';
                break;
            case 45:
                uncoded->new[i]='-';
                break;
            case 46:
                uncoded->new[i]='.';
                break;
            case 47:
                uncoded->new[i]='/';
                break;
            case 48:
                uncoded->new[i]='0';
                break;
            case 49:
                uncoded->new[i]='1';
                break;
            case 50:
                uncoded->new[i]='2';
                break;
            case 51:
                uncoded->new[i]='3';
                break;
            case 52:
                uncoded->new[i]='4';
                break;
            case 53:
                uncoded->new[i]='5';
                break;
            case 54:
                uncoded->new[i]='6';
                break;
            case 55:
                uncoded->new[i]='7';
                break;
            case 56:
                uncoded->new[i]='8';
                break;
            case 57:
                uncoded->new[i]='9';
                break;
            case 58:
                uncoded->new[i]=':';
                break;
            case 59:
                uncoded->new[i]=';';
                break;
            case 60:
                uncoded->new[i]='<';
                break;
            case 61:
                uncoded->new[i]='=';
                break;
            case 62:
                uncoded->new[i]='>';
                break;
            case 63:
                uncoded->new[i]='?';
                break;
            case 64:
                uncoded->new[i]='@';
                break;
            case 65:
                uncoded->new[i]='A';
                break;
            case 66:
                uncoded->new[i]='B';
                break;
            case 67:
                uncoded->new[i]='C';
                break;
            case 68:
                uncoded->new[i]='D';
                break;
            case 69:
                uncoded->new[i]='E';
                break;
            case 70:
                uncoded->new[i]='F';
                break;
            case 71:
                uncoded->new[i]='G';
                break;
            case 72:
                uncoded->new[i]='H';
                break;
            case 73:
                uncoded->new[i]='I';
                break;
            case 74:
                uncoded->new[i]='J';
                break;
            case 75:
                uncoded->new[i]='K';
                break;
            case 76:
                uncoded->new[i]='L';
                break;
            case 77:
                uncoded->new[i]='M';
                break;
            case 78:
                uncoded->new[i]='N';
                break;
            case 79:
                uncoded->new[i]='O';
                break;
            case 80:
                uncoded->new[i]='P';
                break;
            case 81:
                uncoded->new[i]='Q';
                break;
            case 82:
                uncoded->new[i]='R';
                break;
            case 83:
                uncoded->new[i]='S';
                break;
            case 84:
                uncoded->new[i]='T';
                break;
            case 85:
                uncoded->new[i]='U';
                break;
            case 86:
                uncoded->new[i]='V';
                break;
            case 87:
                uncoded->new[i]='W';
                break;
            case 88:
                uncoded->new[i]='X';
                break;
            case 89:
                uncoded->new[i]='Y';
                break;
            case 90:
                uncoded->new[i]='Z';
                break;
            case 97:
                uncoded->new[i]='a';
                break;
            case 98:
                uncoded->new[i]='b';
                break;
            case 99:
                uncoded->new[i]='c';
                break;
            case 100:
                uncoded->new[i]='d';
                break;
            case 101:
                uncoded->new[i]='e';
                break;
            case 102:
                uncoded->new[i]='f';
                break;
            case 103:
                uncoded->new[i]='g';
                break;
            case 104:
                uncoded->new[i]='h';
                break;
            case 105:
                uncoded->new[i]='i';
                break;
            case 106:
                uncoded->new[i]='j';
                break;
            case 107:
                uncoded->new[i]='k';
                break;
            case 108:
                uncoded->new[i]='l';
                break;
            case 109:
                uncoded->new[i]='m';
                break;
            case 110:
                uncoded->new[i]='n';
                break;
            case 111:
                uncoded->new[i]='o';
                break;
            case 112:
                uncoded->new[i]='p';
                break;
            case 113:
                uncoded->new[i]='q';
                break;
            case 114:
                uncoded->new[i]='r';
                break;
            case 115:
                uncoded->new[i]='s';
                break;
            case 116:
                uncoded->new[i]='t';
                break;
            case 117:
                uncoded->new[i]='u';
                break;
            case 118:
                uncoded->new[i]='v';
                break;
            case 119:
                uncoded->new[i]='w';
                break;
            case 120:
                uncoded->new[i]='x';
                break;
            case 121:
                uncoded->new[i]='y';
                break;
            case 122:
                uncoded->new[i]='z';
                break;
            default:
                uncoded->new[i]='#';
                break;
        }
    }
    printf("Decoding!");
    return;
}

void ParDecoding(helper *help)
{
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987

    long C;
    int bin=0;
    C=1%n;  //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->code*C)%n;
    C=(C*C)%n; //1
    C=(help->code*C)%n;

        switch(C)
        {
            case 32:
                help->new=' ';
                break;
            case 33:
                help->new='!';
                break;
            case 35:
                help->new='%';
                break;
            case 40:
                help->new='(';
                break;
            case 41:
                help->new=')';
                break;
            case 43:
                help->new='+';
                break;
            case 44:
                help->new=',';
                break;
            case 45:
                help->new='-';
                break;
            case 46:
                help->new='.';
                break;
            case 47:
                help->new='/';
                break;
            case 48:
                help->new='0';
                break;
            case 49:
                help->new='1';
                break;
            case 50:
                help->new='2';
                break;
            case 51:
                help->new='3';
                break;
            case 52:
                help->new='4';
                break;
            case 53:
                help->new='5';
                break;
            case 54:
                help->new='6';
                break;
            case 55:
                help->new='7';
                break;
            case 56:
                help->new='8';
                break;
            case 57:
                help->new='9';
                break;
            case 58:
                help->new=':';
                break;
            case 59:
                help->new=';';
                break;
            case 60:
                help->new='<';
                break;
            case 61:
                help->new='=';
                break;
            case 62:
                help->new='>';
                break;
            case 63:
                help->new='?';
                break;
            case 64:
                help->new='@';
                break;
            case 65:
                help->new='A';
                break;
            case 66:
                help->new='B';
                break;
            case 67:
                help->new='C';
                break;
            case 68:
                help->new='D';
                break;
            case 69:
                help->new='E';
                break;
            case 70:
                help->new='F';
                break;
            case 71:
                help->new='G';
                break;
            case 72:
                help->new='H';
                break;
            case 73:
                help->new='I';
                break;
            case 74:
                help->new='J';
                break;
            case 75:
                help->new='K';
                break;
            case 76:
                help->new='L';
                break;
            case 77:
                help->new='M';
                break;
            case 78:
                help->new='N';
                break;
            case 79:
                help->new='O';
                break;
            case 80:
                help->new='P';
                break;
            case 81:
                help->new='Q';
                break;
            case 82:
                help->new='R';
                break;
            case 83:
                help->new='S';
                break;
            case 84:
                help->new='T';
                break;
            case 85:
                help->new='U';
                break;
            case 86:
                help->new='V';
                break;
            case 87:
                help->new='W';
                break;
            case 88:
                help->new='X';
                break;
            case 89:
                help->new='Y';
                break;
            case 90:
                help->new='Z';
                break;
            case 97:
                help->new='a';
                break;
            case 98:
                help->new='b';
                break;
            case 99:
                help->new='c';
                break;
            case 100:
                help->new='d';
                break;
            case 101:
                help->new='e';
                break;
            case 102:
                help->new='f';
                break;
            case 103:
                help->new='g';
                break;
            case 104:
                help->new='h';
                break;
            case 105:
                help->new='i';
                break;
            case 106:
                help->new='j';
                break;
            case 107:
                help->new='k';
                break;
            case 108:
                help->new='l';
                break;
            case 109:
                help->new='m';
                break;
            case 110:
                help->new='n';
                break;
            case 111:
                help->new='o';
                break;
            case 112:
                help->new='p';
                break;
            case 113:
                help->new='q';
                break;
            case 114:
                help->new='r';
                break;
            case 115:
                help->new='s';
                break;
            case 116:
                help->new='t';
                break;
            case 117:
                help->new='u';
                break;
            case 118:
                help->new='v';
                break;
            case 119:
                help->new='w';
                break;
            case 120:
                help->new='x';
                break;
            case 121:
                help->new='y';
                break;
            case 122:
                help->new='z';
                break;
            default:
                help->new='#';
                break;
        }
    return;
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
        for(i=0;i<uncoded->n;i++)
        {
            fprintf(fp, "%d ", uncoded->new[i]);
        }
        fclose(fp);
    }
    return;
}
void PDecodedFileDump(data *uncoded)
{
    FILE *fp;
    int i;

    fp=fopen("p_decoded_text.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0;i<uncoded->n;i++)
        {
            fprintf(fp, "%d ", uncoded->new_p[i]);
        }
        fclose(fp);
    }
    return;
}
void ODecodedFileDump(data *uncoded)
{
    FILE *fp;
    int i;

    fp=fopen("o_decoded_text.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        for(i=0;i<uncoded->n;i++)
        {
            fprintf(fp, "%d ", uncoded->new_o[i]);
        }
        fclose(fp);
    }
    return;
}