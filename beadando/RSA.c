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
    int n;
}data;
typedef struct data2
{
    int *number;
    int *code;
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
void Decoding(data2 *coded, data *uncoded);//dekódolás
void ParDecoding(helper *help);
void DecodedFileDump(data *uncoded);//dekódolt szöveg kiírása egy fájlba 
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
    int i;
    int j;
    struct helper help;
    
    

    start_time=clock();
    struct data uncoded;
    uncoded.character=malloc(sizeof(char)*100000);
    uncoded.new=malloc(sizeof(char)*100000);
    printf("Before\n");
    Scanfile(&uncoded);
    printf("Beolvas");
    pthread_t threads[uncoded.n];
    pthread_t threadsomp[uncoded.n];

    encoding_time1=clock();
    struct data2 coded;
    coded.code=malloc(sizeof(int)*100000);
    coded.number=malloc(sizeof(int)*100000);
    EncodingText(&uncoded,&coded);
    encoding_time2=clock();
    encoding_time=encoding_time2-encoding_time1;

    CodedFileDump(&coded);
    
    //printf(" 91 ");
    decoding_time1=clock();
    Decoding(&coded,&uncoded);
    //printf(" 94 ");
    decoding_time2=clock();
    decoding_time=decoding_time2-decoding_time1;
    //printf(" 97 ");
    DecodedFileDump(&uncoded);
    end_time=clock();
    allsequencialtime=end_time-start_time;
    printf(" end ");
 //OPENMP rész !!!

    openmpstart_time=clock();
    struct data ouncoded;
    ouncoded.character=malloc(sizeof(char)*100000);
    ouncoded.new=malloc(sizeof(char)*100000);
    struct data2 ocoded;
    ocoded.code=malloc(sizeof(int)*100000);
    ocoded.number=malloc(sizeof(int)*100000);
    ocoded.n=(ouncoded.n);
    Scanfile(&ouncoded);

    openmpencoding_time1=clock();
    printf("%d", ocoded.n);
    #pragma omp parallel
    {
        printf(" 166 ");
        #pragma omp for
        for(j=0;j<ocoded.n;j++)
        {
            help.i=j;
            help.character=ouncoded.character[j];
            ParEncodingText(&help);
            ocoded.number[i]=help.number;
            ocoded.code[i]=help.code;
        }
        printf(" 175 ");
    }
    openmpencoding_time2=clock();
    openmpencoding_time=openmpencoding_time2-openmpencoding_time1;
    printf(" 175 ");
    CodedFileDump(&ocoded);
    printf(" 177 ");
    openmpdecoding_time1=clock();
    
    #pragma omp parallel for
    for(j=0;j<ocoded.n;j++)
    {
        help.i=i;
        help.code=ocoded.code[j];
        ParDecoding(&help);
        ouncoded.new[i]=help.new;
    }
    
    openmpdecoding_time2=clock();
    openmpdecoding_time=openmpdecoding_time2-openmpdecoding_time1;

    DecodedFileDump(&ouncoded);
    openmpend_time=clock();
    openmpalltime=openmpend_time-openmpstart_time;
    printf( "end" );

    //párhuzamos rész !!!
    
    pstart_time=clock();
    struct data puncoded;
    puncoded.character=malloc(sizeof(char)*100000);
    puncoded.new=malloc(sizeof(char)*100000);
    struct data2 pcoded;
    pcoded.code=malloc(sizeof(int)*100000);
    pcoded.number=malloc(sizeof(int)*100000);
    pcoded.n=(puncoded.n);
    Scanfile(&puncoded);
    
    //printf(" 113 ");
    
    pencoding_time1=clock();
    for(i=0;i<puncoded.n;i++)
    {
        help.i=i;
        help.character=puncoded.character[i];
        
        pthread_create(&threads[i],NULL,ParEncodingText,&help);
        pcoded.number[i]=help.number;
        pcoded.code[i]=help.code;
    }
    pencoding_time2=clock();
    pencoding_time=pencoding_time2-pencoding_time1;
    //printf(" 128 ");
    CodedFileDump(&pcoded);
    //printf(" 130 ");
    pdecoding_time1=clock();
    for(i=0;i<pcoded.n;i++)
    {
        help.i=i;
        help.code=pcoded.code[i];
        
        pthread_create(&threads[i],NULL,ParDecoding,&help);
        puncoded.new[i]=help.new;
    }
    //printf( " 138 ");
    pdecoding_time2=clock();
    pdecoding_time=pdecoding_time2-pdecoding_time1;

    DecodedFileDump(&puncoded);
    pend_time=clock();
    palltime=pend_time-pstart_time;
    printf(" end ");
   

    free(uncoded.character);
    free(uncoded.new);
    free(coded.code);
    free(coded.number);
    free(puncoded.character);
    free(puncoded.new);
    free(pcoded.code);
    free(pcoded.number);
    free(ouncoded.character);
    free(ouncoded.new);
    free(ocoded.code);
    free(ocoded.number);
    runtime_display(allsequencialtime, palltime, openmpalltime, encoding_time, pencoding_time, openmpencoding_time, decoding_time, pdecoding_time, openmpdecoding_time);
    printf(" end ");
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
    printf("1size= %d\n",size);
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
            printf("%c",ch);
            //printf("i");
            i++;
            //printf("i");
            size++; 
            //printf("i");
            printf("2size= %d\n",size);
        }
        if (size==0) 
        {
            printf("\nA fájl üres");
            return;
        }
        
        printf("4size= %d\n",size);
        fclose(fp);
        printf("5size= %d\n",size);
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
        if(uncoded->character[i] == ' ')
        {
            code->number[i]=32;
        }
        else if(uncoded->character[i] == '!')
        {
            code->number[i]=33;
        }
        else if(uncoded->character[i] == '%')
        {
            code->number[i]=37;
        }
        else if(uncoded->character[i] == '(')
        {
            code->number[i]=40;
        }
        else if(uncoded->character[i] == ')')
        {
            code->number[i]=41;
        }
        else if(uncoded->character[i] == '+')
        {
            code->number[i]=43;
        }
        else if(uncoded->character[i] == ',')
        {
            code->number[i]=44;
        }
        else if(uncoded->character[i] == '-')
        {
            code->number[i]=45;
        }
        else if(uncoded->character[i] == '.')
        {
            code->number[i]=46;
        }
        else if(uncoded->character[i] == '/')
        {
            code->number[i]=47;
        }
        else if(uncoded->character[i] == '0')
        {
            code->number[i]=48;
        }
        else if(uncoded->character[i] == '1')
        {
            code->number[i]=49;
        }
        else if(uncoded->character[i] == '2')
        {
            code->number[i]=50;
        }
        else if(uncoded->character[i] == '3')
        {
            code->number[i]=51;
        }
        else if(uncoded->character[i] == '4')
        {
            code->number[i]=52;
        }
        else if(uncoded->character[i] == '5')
        {
            code->number[i]=53;
        }
        else if(uncoded->character[i] == '6')
        {
            code->number[i]=54;
        }
        else if(uncoded->character[i] == '7')
        {
            code->number[i]=55;
        }
        else if(uncoded->character[i] == '8')
        {
            code->number[i]=56;
        }
        else if(uncoded->character[i] == '9')
        {
            code->number[i]=57;
        }
        else if(uncoded->character[i] == ':')
        {
            code->number[i]=58;
        }
        else if(uncoded->character[i] == ';')
        {
            code->number[i]=59;
        }
        else if(uncoded->character[i] == '<')
        {
            code->number[i]=60;
        }
        else if(uncoded->character[i] == '=')
        {
            code->number[i]=61;
        }
        else if(uncoded->character[i] == '>')
        {
            code->number[i]=62;
        }
        else if(uncoded->character[i] == '?')
        {
            code->number[i]=63;
        }
        else if(uncoded->character[i] == '@')
        {
            code->number[i]=64;
        }
        else if(uncoded->character[i] == 'A')
        {
            code->number[i]=65;
        }
        else if(uncoded->character[i] == 'B')
        {
            code->number[i]=66;
        }
        else if(uncoded->character[i] == 'C')
        {
            code->number[i]=67;
        }
        else if(uncoded->character[i] == 'D')
        {
            code->number[i]=68;
        }
        else if(uncoded->character[i] == 'E')
        {
            code->number[i]=69;
        }
        else if(uncoded->character[i] == 'F')
        {
            code->number[i]=70;
        }
        else if(uncoded->character[i] == 'G')
        {
            code->number[i]=71;
        }
        else if(uncoded->character[i] == 'H')
        {
            code->number[i]=72;
        }
        else if(uncoded->character[i] == 'I')
        {
            code->number[i]=73;
        }
        else if(uncoded->character[i] == 'J')
        {
            code->number[i]=74;
        }
        else if(uncoded->character[i] == 'K')
        {
            code->number[i]=75;
        }
        else if(uncoded->character[i] == 'L')
        {
            code->number[i]=76;
        }
        else if(uncoded->character[i] == 'M')
        {
            code->number[i]=77;
        }
        else if(uncoded->character[i] == 'N')
        {
            code->number[i]=78;
        }
        else if(uncoded->character[i] == 'O')
        {
            code->number[i]=79;
        }
        else if(uncoded->character[i] == 'P')
        {
            code->number[i]=80;
        }
        else if(uncoded->character[i] == 'Q')
        {
            code->number[i]=81;
        }
        else if(uncoded->character[i] == 'R')
        {
            code->number[i]=82;
        }
        else if(uncoded->character[i] == 'S')
        {
            code->number[i]=83;
        }
        else if(uncoded->character[i] == 'T')
        {
            code->number[i]=84;
        }
        else if(uncoded->character[i] == 'U')
        {
            code->number[i]=85;
        }
        else if(uncoded->character[i] == 'V')
        {
            code->number[i]=86;
        }
        else if(uncoded->character[i] == 'W')
        {
            code->number[i]=87;
        }
        else if(uncoded->character[i] == 'X')
        {
            code->number[i]=88;
        }
        else if(uncoded->character[i] == 'Y')
        {
            code->number[i]=89;
        }
        else if(uncoded->character[i] == 'Z')
        {
            code->number[i]=90;
        }
        else if(uncoded->character[i] == 'a')
        {
            code->number[i]=97;
        }
        else if(uncoded->character[i] == 'b')
        {
            code->number[i]=98;
        }
        else if(uncoded->character[i] == 'c')
        {
            code->number[i]=99;
        }
        else if(uncoded->character[i] == 'd')
        {
            code->number[i]=100;
        }
        else if(uncoded->character[i] == 'e')
        {
            code->number[i]=101;
        }
        else if(uncoded->character[i] == 'f')
        {
            code->number[i]=102;
        }
        else if(uncoded->character[i] == 'g')
        {
            code->number[i]=103;
        }
        else if(uncoded->character[i] == 'h')
        {
            code->number[i]=104;
        }
        else if(uncoded->character[i] == 'i')
        {
            code->number[i]=105;
        }
        else if(uncoded->character[i] == 'j')
        {
            code->number[i]=106;
        }
        else if(uncoded->character[i] == 'k')
        {
            code->number[i]=107;
        }
        else if(uncoded->character[i] == 'l')
        {
            code->number[i]=108;
        }
        else if((uncoded->character[i]) = 'm')
        {
            code->number[i]=109;
        }
        else if(uncoded->character[i] == 'n')
        {
            code->number[i]=110;
        }
        else if(uncoded->character[i] == 'o')
        {
            code->number[i]=111;
        }
        else if(uncoded->character[i] == 'p')
        {
            code->number[i]=112;
        }
        else if(uncoded->character[i] == 'q')
        {
            code->number[i]=113;
        }
        else if(uncoded->character[i] == 'r')
        {
            code->number[i]=114;
        }
        else if(uncoded->character[i] == 's')
        {
            code->number[i]=115;
        }
        else if(uncoded->character[i] == 't')
        {
            code->number[i]=116;
        }
        else if(uncoded->character[i] == 'u')
        {
            code->number[i]=117;
        }
        else if(uncoded->character[i] == 'v')
        {
            code->number[i]=118;
        }
        else if(uncoded->character[i] == 'w')
        {
            code->number[i]=119;
        }
        else if(uncoded->character[i] == 'x')
        {
            code->number[i]=120;
        }
        else if(uncoded->character[i] == 'y')
        {
            code->number[i]=121;
        }
        else if(uncoded->character[i] == 'z')
        {
            code->number[i]=122;
        }
        else
        {
            code->number[i]=35;
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
    //printf("Encoding!");
    return;
}

void ParEncodingText( helper *help)
{
   int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;

    if(help->character == ' ')
    {
        help->number=32;
    }
    else if(help->character == '!')
    {
        help->number=33;
    }
    else if(help->character == '%')
    {
        help->number=37;
    }
    else if(help->character == '(')
    {
        help->number=40;
    }
    else if(help->character == ')')
    {
        help->number=41;
    }
    else if(help->character == '+')
    {
        help->number=43;
    }
    else if(help->character == ',')
    {
        help->number=44;
    }
    else if(help->character == '-')
    {
        help->number=45;
    }
    else if(help->character == '.')
    {
        help->number=46;
    }
    else if(help->character == '/')
    {
        help->number=47;
    }
    else if(help->character == '0')
    {
        help->number=48;
    }
    else if(help->character == '1')
    {
        help->number=49;
    }
    else if(help->character == '2')
    {
        help->number=50;
    }
    else if(help->character == '3')
    {
        help->number=51;
    }
    else if(help->character == '4')
    {
        help->number=52;
    }
    else if(help->character == '5')
    {
        help->number=53;
    }
    else if(help->character == '6')
    {
        help->number=54;
    }
    else if(help->character == '7')
    {
        help->number=55;
    }
    else if(help->character == '8')
    {
        help->number=56;
    }
    else if(help->character == '9')
    {
        help->number=57;
    }
    else if(help->character == ':')
    {
        help->number=58;
    }
    else if(help->character == ';')
    {
        help->number=59;
    }
    else if(help->character == '<')
    {
        help->number=60;
    }
    else if(help->character == '=')
    {
        help->number=61;
    }
    else if(help->character == '>')
    {
        help->number=62;
    }
    else if(help->character == '?')
    {
        help->number=63;
    }
    else if(help->character == '@')
    {
        help->number=64;
    }
    else if(help->character == 'A')
    {
        help->number=65;
    }
    else if(help->character == 'B')
    {
        help->number=66;
    }
    else if(help->character == 'C')
    {
        help->number=67;
    }
    else if(help->character == 'D')
    {
        help->number=68;
    }
    else if(help->character == 'E')
    {
        help->number=69;
    }
    else if(help->character == 'F')
    {
        help->number=70;
    }
    else if(help->character == 'G')
    {
        help->number=71;
    }
    else if(help->character == 'H')
    {
        help->number=72;
    }
    else if(help->character == 'I')
    {
        help->number=73;
    }
    else if(help->character == 'J')
    {
        help->number=74;
    }
    else if(help->character == 'K')
    {
        help->number=75;
    }
    else if(help->character == 'L')
    {
        help->number=76;
    }
    else if(help->character == 'M')
    {
        help->number=77;
    }
    else if(help->character == 'N')
    {
        help->number=78;
    }
    else if(help->character == 'O')
    {
        help->number=79;
    }
    else if(help->character == 'P')
    {
        help->number=80;
    }
    else if(help->character == 'Q')
    {
        help->number=81;
    }
    else if(help->character == 'R')
    {
        help->number=82;
    }
    else if(help->character == 'S')
    {
        help->number=83;
    }
    else if(help->character == 'T')
    {
        help->number=84;
    }
    else if(help->character == 'U')
    {
        help->number=85;
    }
    else if(help->character == 'V')
    {
        help->number=86;
    }
    else if(help->character == 'W')
    {
        help->number=87;
    }
    else if(help->character == 'X')
    {
        help->number=88;
    }
    else if(help->character == 'Y')
    {
        help->number=89;
    }
    else if(help->character == 'Z')
    {
        help->number=90;
    }
    else if(help->character == 'a')
    {
        help->number=97;
    }
    else if(help->character == 'b')
    {
        help->number=98;
    }
    else if(help->character == 'c')
    {
        help->number=99;
    }
    else if(help->character == 'd')
    {
        help->number=100;
    }
    else if(help->character == 'e')
    {
        help->number=101;
    }
    else if(help->character == 'f')
    {
        help->number=102;
    }
    else if(help->character == 'g')
    {
        help->number=103;
    }
    else if(help->character == 'h')
    {
        help->number=104;
    }
    else if(help->character == 'i')
    {
        help->number=105;
    }
    else if(help->character == 'j')
    {
        help->number=106;
    }
    else if(help->character == 'k')
    {
        help->number=107;
    }
    else if(help->character == 'l')
    {
        help->number=108;
    }
    else if(help->character = 'm')
    {
        help->number=109;
    }
    else if(help->character == 'n')
    {
        help->number=110;
    }
    else if(help->character == 'o')
    {
        help->number=111;
    }
    else if(help->character == 'p')
    {
        help->number=112;
    }
    else if(help->character == 'q')
    {
        help->number=113;
    }
    else if(help->character == 'r')
    {
        help->number=114;
    }
    else if(help->character == 's')
    {
        help->number=115;
    }
    else if(help->character == 't')
    {
        help->number=116;
    }
    else if(help->character == 'u')
    {
        help->number=117;
    }
    else if(help->character == 'v')
    {
        help->number=118;
    }
    else if(help->character == 'w')
    {
        help->number=119;
    }
    else if(help->character == 'x')
    {
        help->number=120;
    }
    else if(help->character == 'y')
    {
        help->number=121;
    }
    else if(help->character == 'z')
    {
        help->number=122;
    }
    else
    {
         help->number=35;
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
        if(C == 32)
        {
            uncoded->new[i]=' ';
        }
        else if(C == 33)
        {
            uncoded->new[i]='!';
        }
        else if(C == 35)
        {
            uncoded->new[i]='%';
        }
        else if(C == 40)
        {
            uncoded->new[i]='(';
        }
        else if(C == 41)
        {
            uncoded->new[i]=')';
        }
        else if(C == 43)
        {
            uncoded->new[i]='+';
        }
        else if(C == 44)
        {
            uncoded->new[i]=',';
        }
        else if(C == 45)
        {
            uncoded->new[i]='-';
        }
        else if(C == 46)
        {
            uncoded->new[i]='.';
        }
        else if(C == 47)
        {
            uncoded->new[i]='/';
        }
        else if(C == 48)
        {
            uncoded->new[i]='0';
        }
        else if(C == 49)
        {
            uncoded->new[i]='1';
        }
        else if(C == 50)
        {
            uncoded->new[i]='2';
        }
        else if(C == 51)
        {
            uncoded->new[i]='3';
        }
        else if(C == 52)
        {
            uncoded->new[i]='4';
        }
        else if(C == 53)
        {
            uncoded->new[i]='5';
        }
        else if(C == 54)
        {
            uncoded->new[i]='6';
        }
        else if(C == 55)
        {
            uncoded->new[i]='7';
        }
        else if(C == 56)
        {
            uncoded->new[i]='8';
        }
        else if(C == 57)
        {
            uncoded->new[i]='9';
        }
        else if(C == 58)
        {
            uncoded->new[i]=':';
        }
        else if(C == 59)
        {
            uncoded->new[i]=';';
        }
        else if(C == 60)
        {
            uncoded->new[i]='<';
        }
        else if(C == 61)
        {
            uncoded->new[i]='=';
        }
        else if(C == 62)
        {
            uncoded->new[i]='>';
        }
        else if(C == 63)
        {
            uncoded->new[i]='?';
        }
        else if(C == 64)
        {
            uncoded->new[i]='@';
        }
        else if(C == 65)
        {
            uncoded->new[i]='A';
        }
        else if(C == 66)
        {
            uncoded->new[i]='B';
        }
        else if(C == 67)
        {
            uncoded->new[i]='C';
        }
        else if(C == 68)
        {
            uncoded->new[i]='D';
        }
        else if(C == 69)
        {
            uncoded->new[i]='E';
        }
        else if(C == 70)
        {
            uncoded->new[i]='F';
        }
        else if(C == 71)
        {
            uncoded->new[i]='G';
        }
        else if(C == 72)
        {
            uncoded->new[i]='H';
        }
        else if(C == 73)
        {
            uncoded->new[i]='I';
        }
        else if(C == 74)
        {
            uncoded->new[i]='J';
        }
        else if(C == 75)
        {
            uncoded->new[i]='K';
        }
        else if(C == 76)
        {
            uncoded->new[i]='L';
        }
        else if(C == 77)
        {
            uncoded->new[i]='M';
        }
        else if(C == 78)
        {
            uncoded->new[i]='N';
        }
        else if(C == 79)
        {
            uncoded->new[i]='O';
        }
        else if(C == 80)
        {
            uncoded->new[i]='P';
        }
        else if(C == 81)
        {
            uncoded->new[i]='Q';
        }
        else if(C == 82)
        {
            uncoded->new[i]='R';
        }
        else if(C == 83)
        {
            uncoded->new[i]='S';
        }
        else if(C == 84)
        {
            uncoded->new[i]='T';
        }
        else if(C == 85)
        {
            uncoded->new[i]='U';
        }
        else if(C == 86)
        {
            uncoded->new[i]='V';
        }
        else if(C == 87)
        {
            uncoded->new[i]='W';
        }
        else if(C == 88)
        {
            uncoded->new[i]='X';
        }
        else if(C == 89)
        {
            uncoded->new[i]='Y';
        }
        else if(C == 90)
        {
            uncoded->new[i]='Z';
        }
        else if(C == 97)
        {
            uncoded->new[i]='a';
        }
        else if(C == 98)
        {
            uncoded->new[i]='b';
        }
        else if(C == 99)
        {
            uncoded->new[i]='c';
        }
        else if(C == 100)
        {
            uncoded->new[i]='d';
        }
        else if(C == 101)
        {
            uncoded->new[i]='e';
        }
        else if(C == 102)
        {
            uncoded->new[i]='f';
        }
        else if(C == 103)
        {
            uncoded->new[i]='g';
        }
        else if(C == 104)
        {
            uncoded->new[i]='h';
        }
        else if(C == 105)
        {
            uncoded->new[i]='i';
        }
        else if(C == 106)
        {
            uncoded->new[i]='j';
        }
        else if(C == 107)
        {
            uncoded->new[i]='k';
        }
        else if(C == 108)
        {
            uncoded->new[i]='l';
        }
        else if(C == 109)
        {
            uncoded->new[i]='m';
        }
        else if(C == 110)
        {
            uncoded->new[i]='n';
        }
        else if(C == 111)
        {
            uncoded->new[i]='o';
        }
        else if(C == 112)
        {
            uncoded->new[i]='p';
        }
        else if(C == 113)
        {
            uncoded->new[i]='q';
        }
        else if(C == 114)
        {
            uncoded->new[i]='r';
        }
        else if(C == 115)
        {
            uncoded->new[i]='s';
        }
        else if(C == 116)
        {
            uncoded->new[i]='t';
        }
        else if(C == 117)
        {
            uncoded->new[i]='u';
        }
        else if(C == 118)
        {
            uncoded->new[i]='v';
        }
        else if(C == 119)
        {
            uncoded->new[i]='w';
        }
        else if(C == 120)
        {
            uncoded->new[i]='x';
        }
        else if(C == 121)
        {
            uncoded->new[i]='y';
        }
        else if(C == 122)
        {
            uncoded->new[i]='z';
        }
        else
        {
            uncoded->new[i]='#';
        }
    }
    //printf("Decoding!");
    return;
}

void ParDecoding(helper *help)
{
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987

    long C=1;
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

    if(C == 32)
    {
        help->new=' ';
    }
    else if(C == 33)
    {
        help->new='!';
    }
    else if(C == 35)
    {
        help->new='%';
    }
    else if(C == 40)
    {
        help->new='(';
    }
    else if(C == 41)
    {
        help->new=')';
    }
    else if(C == 43)
    {
        help->new='+';
    }
    else if(C == 44)
    {
        help->new=',';
    }
    else if(C == 45)
    {
        help->new='-';
    }
    else if(C == 46)
    {
        help->new='.';
    }
    else if(C == 47)
    {
        help->new='/';
    }
    else if(C == 48)
    {
        help->new='0';
    }
    else if(C == 49)
    {
        help->new='1';
    }
    else if(C == 50)
    {
        help->new='2';
    }
    else if(C == 51)
    {
        help->new='3';
    }
    else if(C == 52)
    {
        help->new='4';
    }
    else if(C == 53)
    {
        help->new='5';
    }
    else if(C == 54)
    {
        help->new='6';
    }
    else if(C == 55)
    {
        help->new='7';
    }
    else if(C == 56)
    {
        help->new='8';
    }
    else if(C == 57)
    {
        help->new='9';
    }
    else if(C == 58)
    {
        help->new=':';
    }
    else if(C == 59)
    {
        help->new=';';
    }
    else if(C == 60)
    {
        help->new='<';
    }
    else if(C == 61)
    {
        help->new='=';
    }
    else if(C == 62)
    {
        help->new='>';
    }
    else if(C == 63)
    {
        help->new='?';
    }
    else if(C == 64)
    {
        help->new='@';
    }
    else if(C == 65)
    {
        help->new='A';
    }
    else if(C == 66)
    {
        help->new='B';
    }
    else if(C == 67)
    {
        help->new='C';
    }
    else if(C == 68)
    {
        help->new='D';
    }
    else if(C == 69)
    {
        help->new='E';
    }
    else if(C == 70)
    {
        help->new='F';
    }
    else if(C == 71)
    {
        help->new='G';
    }
    else if(C == 72)
    {
        help->new='H';
    }
    else if(C == 73)
    {
        help->new='I';
    }
    else if(C == 74)
    {
        help->new='J';
    }
    else if(C == 75)
    {
        help->new='K';
    }
    else if(C == 76)
    {
        help->new='L';
    }
    else if(C == 77)
    {
        help->new='M';
    }
    else if(C == 78)
    {
        help->new='N';
    }
    else if(C == 79)
    {
        help->new='O';
    }
    else if(C == 80)
    {
        help->new='P';
    }
    else if(C == 81)
    {
        help->new='Q';
    }
    else if(C == 82)
    {
        help->new='R';
    }
    else if(C == 83)
    {
        help->new='S';
    }
    else if(C == 84)
    {
        help->new='T';
    }
    else if(C == 85)
    {
        help->new='U';
    }
    else if(C == 86)
    {
        help->new='V';
    }
    else if(C == 87)
    {
        help->new='W';
    }
    else if(C == 88)
    {
        help->new='X';
    }
    else if(C == 89)
    {
        help->new='Y';
    }
    else if(C == 90)
    {
        help->new='Z';
    }
    else if(C == 97)
    {
        help->new='a';
    }
    else if(C == 98)
    {
        help->new='b';
    }
    else if(C == 99)
    {
        help->new='c';
    }
    else if(C == 100)
    {
        help->new='d';
    }
    else if(C == 101)
    {
        help->new='e';
    }
    else if(C == 102)
    {
        help->new='f';
    }
    else if(C == 103)
    {
        help->new='g';
    }
    else if(C == 104)
    {
        help->new='h';
    }
    else if(C == 105)
    {
        help->new='i';
    }
    else if(C == 106)
    {
        help->new='j';
    }
    else if(C == 107)
    {
        help->new='k';
    }
    else if(C == 108)
    {
        help->new='l';
    }
    else if(C == 109)
    {
        help->new='m';
    }
    else if(C == 110)
    {
        help->new='n';
    }
    else if(C == 111)
    {
        help->new='o';
    }
    else if(C == 112)
    {
        help->new='p';
    }
    else if(C == 113)
    {
        help->new='q';
    }
    else if(C == 114)
    {
        help->new='r';
    }
    else if(C == 115)
    {
        help->new='s';
    }
    else if(C == 116)
    {
        help->new='t';
    }
    else if(C == 117)
    {
        help->new='u';
    }
    else if(C == 118)
    {
        help->new='v';
    }
    else if(C == 119)
    {
        help->new='w';
    }
    else if(C == 120)
    {
        help->new='x';
    }
    else if(C == 121)
    {
        help->new='y';
    }
    else if(C == 122)
    {
        help->new='z';
    }
    else
    {
        help->new='#';
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
    //printf("decode");
    return;
}