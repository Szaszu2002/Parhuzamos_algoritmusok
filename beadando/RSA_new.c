#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> 
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
    unsigned long long *code;
    int n;
}data2;
typedef struct helper
{
    int i;
    data *uncoded;
    data2 *coded;
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
void runtime_display(unsigned long long allsequencialtime, unsigned long long palltime, unsigned long long openmpalltime, unsigned long long encoding_time, unsigned long long pencoding_time, unsigned long long openmpencoding_time, unsigned long long decoding_time, unsigned long long pdecoding_time, unsigned long long openmpdecoding_time);     //futási idők kiírása egy fájlba



int main()
{
    unsigned long long allsequencialtime;  //
    unsigned long long palltime; //
    unsigned long long openmpalltime;
    struct timeval start_time; //
    struct timeval pstart_time; //
    struct timeval openmpstart_time;
    struct timeval encoding_time1; //
    struct timeval encoding_time2; //
    unsigned long long encoding_time;  //
    struct timeval pencoding_time1; //
    struct timeval pencoding_time2;
    unsigned long long pencoding_time;
    struct timeval openmpencoding_time1;
    struct timeval openmpencoding_time2;
    unsigned long long openmpencoding_time;
    struct timeval decoding_time1; //
    struct timeval decoding_time2; //
    unsigned long long decoding_time;  //
    struct timeval pdecoding_time1;
    struct timeval pdecoding_time2;
    unsigned long long pdecoding_time;
    struct timeval openmpdecoding_time1;
    struct timeval openmpdecoding_time2;
    unsigned long long openmpdecoding_time;
    struct timeval end_time;
    struct timeval pend_time;
    struct timeval openmpend_time;
    unsigned long long read_time;
    struct timeval read_time1;
    struct timeval read_time2;
    int i,j;
    
    gettimeofday(&read_time1,NULL);
    struct data uncoded;
    uncoded.character=malloc(sizeof(char)*100000);
    uncoded.new=malloc(sizeof(char)*100000);
    Scanfile(&uncoded);
    gettimeofday(&read_time2,NULL);
    read_time=(read_time2.tv_sec/1000+read_time2.tv_usec)-(read_time1.tv_sec/1000+read_time1.tv_usec);
    
    struct helper help[uncoded.n];
    pthread_t threads[uncoded.n];
    pthread_t threadsomp[uncoded.n];

    gettimeofday(&start_time,NULL);
    gettimeofday(&encoding_time1,NULL);
    struct data2 coded;
    coded.code=malloc(sizeof(unsigned long long)*100000);
    coded.number=malloc(sizeof(int)*100000);
    EncodingText(&uncoded,&coded);
    gettimeofday(&encoding_time2,NULL);
    encoding_time=(encoding_time2.tv_sec/1000+encoding_time2.tv_usec)-(encoding_time1.tv_sec/1000+encoding_time1.tv_usec);

    CodedFileDump(&coded);
    
    gettimeofday(&decoding_time1,NULL);
    Decoding(&coded,&uncoded);
    gettimeofday(&decoding_time2,NULL);
    decoding_time=(decoding_time2.tv_sec/1000+decoding_time2.tv_usec)-(decoding_time1.tv_sec/1000+decoding_time1.tv_usec);
    DecodedFileDump(&uncoded);
    gettimeofday(&end_time,NULL);
    allsequencialtime=((end_time.tv_sec/1000+end_time.tv_usec)-(start_time.tv_sec/1000+start_time.tv_usec)+read_time);
  
    //párhuzamos rész !!!
    gettimeofday(&pstart_time,NULL);
    gettimeofday(&pencoding_time1,NULL);
    for(i=0;i<uncoded.n;i++)
    {
        help[i].i=i;
        help[i].uncoded=&uncoded;
        help[i].coded=&coded;
        pthread_create(&threads[i],NULL,ParEncodingText, &help[i]);
    }
    for(i=0;i<coded.n;i++)
    {
        pthread_join(threads[i],NULL);
    }
    gettimeofday(&pencoding_time2,NULL);
    pencoding_time=(pencoding_time2.tv_sec/1000+pencoding_time2.tv_usec)-(pencoding_time1.tv_sec/1000+pencoding_time1.tv_usec);
    PCodedFileDump(&coded);
    gettimeofday(&pdecoding_time1,NULL);
    for(i=0;i<coded.n;i++)
    {
        help[i].i=i;
        pthread_create(&threads[i],NULL,ParDecoding, &help[i]);
    }
    for(i=0;i<coded.n;i++)
    {
        pthread_join(threads[i],NULL);
    }
    gettimeofday(&pdecoding_time2,NULL);
    pdecoding_time=(pdecoding_time2.tv_sec/1000+pdecoding_time2.tv_usec)-(pdecoding_time1.tv_sec/1000+pdecoding_time1.tv_usec);
    PDecodedFileDump(&uncoded);
    gettimeofday(&pend_time,NULL);
    palltime=((pend_time.tv_sec/1000+pend_time.tv_usec)-(pstart_time.tv_sec/1000+pstart_time.tv_usec)+read_time);

    //OPENMP rész !!!
    gettimeofday(&openmpstart_time,NULL);
    gettimeofday(&openmpencoding_time1,NULL);
    
    #pragma omp parallel for
    for(j=0;j<coded.n;j++)
    {
        help[j].i=j;
        ParEncodingText(&help[j]);
    }
    gettimeofday(&openmpencoding_time2,NULL);
    openmpencoding_time=(openmpencoding_time2.tv_sec/1000+openmpencoding_time2.tv_usec)-(openmpencoding_time1.tv_sec/1000+openmpencoding_time1.tv_usec);
    OCodedFileDump(&coded);
    gettimeofday(&openmpdecoding_time1,NULL);
    
    #pragma omp parallel for
    for(j=0;j<coded.n;j++)
    {
        help[j].i=j;
        ParDecoding(&help[j]);
    }
    gettimeofday(&openmpdecoding_time2,NULL);
    openmpdecoding_time=(openmpdecoding_time2.tv_sec/1000+openmpdecoding_time2.tv_usec)-(openmpdecoding_time1.tv_sec/1000+openmpdecoding_time1.tv_usec);
    
    ODecodedFileDump(&uncoded);
    gettimeofday(&openmpend_time,NULL);
    openmpalltime=((openmpend_time.tv_sec/1000+openmpend_time.tv_usec)-(openmpstart_time.tv_sec/1000+openmpstart_time.tv_usec)+read_time);

    free(uncoded.character);
    free(uncoded.new);
    free(coded.code);
    free(coded.number);
    
    runtime_display(allsequencialtime, palltime, openmpalltime, encoding_time, pencoding_time, openmpencoding_time, decoding_time, pdecoding_time, openmpdecoding_time);
    return 0;
}

void runtime_display(unsigned long long allsequencialtime, unsigned long long palltime, unsigned long long openmpalltime, unsigned long long encoding_time, unsigned long long pencoding_time, unsigned long long openmpencoding_time, unsigned long long decoding_time, unsigned long long pdecoding_time, unsigned long long openmpdecoding_time)
{
    FILE *fp;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n %.lld; %.lld; %.lld; %.lld; %.lld; %.lld; %.lld; %.lld; %.lld", allsequencialtime, palltime, openmpalltime, encoding_time, pencoding_time, openmpencoding_time, decoding_time, pdecoding_time, openmpdecoding_time);
        fclose(fp);
    }
    return;
}

void Scanfile(data* uncoded)
{
    int size=0, number_of_lines=0, i=0;
    char ch;
    FILE *fp;
    
    fp=fopen("text_short_story.txt","r");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        while((ch = fgetc(fp)) != EOF) 
        {
            uncoded->character[i]=ch; 
            i++;
            size++; 
        }
        if (size==0) 
        {
            printf("\nA fájl üres");
            return;
        }
        fclose(fp);
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
    unsigned long n=p*q;
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
        unsigned long long M=code->number[i];
        unsigned long long C=1;
        C = 1 % n;
        C = (M * C) % n;    
        C = (C * C) % n;
        C = (C * C) % n; 
        C = (M * C) % n;    
        C = (C * C) % n;    
        C = (M * C) % n;    
        code->code[i] = (int) C;
    }
    return;
}

void ParEncodingText( helper *help)
{
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int i=help->i;

        switch(help->uncoded->character[i])
        {
            case ' ':
                help->coded->number[i]=32;
                break;
            case '!':
                help->coded->number[i]=33;
                break;
            case '%':
                help->coded->number[i]=37;
                break;
            case '(':
                help->coded->number[i]=40;
                break;
            case ')':
                help->coded->number[i]=41;
                break;
            case '+':
                help->coded->number[i]=43;
                break;
            case ',':
                help->coded->number[i]=44;
                break;
            case '-':
                help->coded->number[i]=45;
                break;
            case '.':
                help->coded->number[i]=46;
                break;
            case '/':
                help->coded->number[i]=47;
                break;
            case '0':
                help->coded->number[i]=48;
                break;
            case '1':
                help->coded->number[i]=49;
                break;
            case '2':
                help->coded->number[i]=50;
                break;
            case '3':
                help->coded->number[i]=51;
                break;
            case '4':
                help->coded->number[i]=52;
                break;
            case '5':
                help->coded->number[i]=53;
                break;
            case '6':
                help->coded->number[i]=54;
                break;
            case '7':
                help->coded->number[i]=55;
                break;
            case '8':
                help->coded->number[i]=56;
                break;
            case '9':
                help->coded->number[i]=57;
                break;
            case ':':
                help->coded->number[i]=58;
                break;
            case ';':
                help->coded->number[i]=59;
                break;
            case '<':
                help->coded->number[i]=60;
                break;
            case '=':
                help->coded->number[i]=61;
                break;
            case '>':
                help->coded->number[i]=62;
                break;
            case '?':
                help->coded->number[i]=63;
                break;
            case '@':
                help->coded->number[i]=64;
                break;
            case 'A':
                help->coded->number[i]=65;
                break;
            case 'B':
                help->coded->number[i]=66;
                break;
            case 'C':
                help->coded->number[i]=67;
                break;
            case 'D':
                help->coded->number[i]=68;
                break;
            case 'E':
                help->coded->number[i]=69;
                break;
            case 'F':
                help->coded->number[i]=70;
                break;
            case 'G':
                help->coded->number[i]=71;
                break;
            case 'H':
                help->coded->number[i]=72;
                break;
            case 'I':
                help->coded->number[i]=73;
                break;
            case 'J':
                help->coded->number[i]=74;
                break;
            case 'K':
                help->coded->number[i]=75;
                break;
            case 'L':
                help->coded->number[i]=76;
                break;
            case 'M':
                help->coded->number[i]=77;
                break;
            case 'N':
                help->coded->number[i]=78;
                break;
            case 'O':
                help->coded->number[i]=79;
                break;
            case 'P':
                help->coded->number[i]=80;
                break;
            case 'Q':
                help->coded->number[i]=81;
                break;
            case 'R':
                help->coded->number[i]=82;
                break;
            case 'S':
                help->coded->number[i]=83;
                break;
            case 'T':
                help->coded->number[i]=84;
                break;
            case 'U':
                help->coded->number[i]=85;
                break;
            case 'V':
                help->coded->number[i]=86;
                break;
            case 'W':
                help->coded->number[i]=87;
                break;
            case 'X':
                help->coded->number[i]=88;
                break;
            case 'Y':
                help->coded->number[i]=89;
                break;
            case 'Z':
                help->coded->number[i]=90;
                break;
            case 'a':
                help->coded->number[i]=97;
                break;
            case 'b':
                help->coded->number[i]=98;
                break;
            case 'c':
                help->coded->number[i]=99;
                break;
            case 'd':
                help->coded->number[i]=100;
                break;
            case 'e':
                help->coded->number[i]=101;
                break;
            case 'f':
                help->coded->number[i]=102;
                break;
            case 'g':
                help->coded->number[i]=103;
                break;
            case 'h':
                help->coded->number[i]=104;
                break;
            case 'i':
                help->coded->number[i]=105;
                break;
            case 'j':
                help->coded->number[i]=106;
                break;
            case 'k':
                help->coded->number[i]=107;
                break;
            case 'l':
                help->coded->number[i]=108;
                break;
            case 'm':
                help->coded->number[i]=109;
                break;
            case 'n':
                help->coded->number[i]=110;
                break;
            case 'o':
                help->coded->number[i]=111;
                break;
            case 'p':
                help->coded->number[i]=112;
                break;
            case 'q':
                help->coded->number[i]=113;
                break;
            case 'r':
                help->coded->number[i]=114;
                break;
            case 's':
                help->coded->number[i]=115;
                break;
            case 't':
                help->coded->number[i]=116;
                break;
            case 'u':
                help->coded->number[i]=117;
                break;
            case 'v':
                help->coded->number[i]=118;
                break;
            case 'w':
                help->coded->number[i]=119;
                break;
            case 'x':
                help->coded->number[i]=120;
                break;
            case 'y':
                help->coded->number[i]=121;
                break;
            case 'z':
                help->coded->number[i]=122;
                break;
            default:
                help->coded->number[i]=35;
                break;
        }
    //titkosítás rész !!!
    
    unsigned long long M=help->coded->number[i];
    unsigned long long C=1;

    C = 1 % n;
    C = (M * C) % n;          
    C = (C * C) % n;   
    C = (C * C) % n; 
    C = (M * C) % n;    
    C = (C * C) % n;    
    C = (M * C) % n;  
    help->coded->code[i]=(int)C;
    return;
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
void OCodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;
    
    fp=fopen("o_coded_text.txt","a");
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
void PCodedFileDump(data2 *coded)
{
    FILE *fp;
    int i;

    fp=fopen("p_coded_text.txt","a");
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
void Decoding(data2 *coded, data *uncoded)
{
    int i;
    int p=1039;
    int q=2617;
    unsigned long long n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987

    for(i=0;i<coded->n;i++)
    {
        unsigned long long C=0;
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
            case 37:
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
    return;
}

void ParDecoding(helper *help)
{
    int p=1039;
    int q=2617;
    unsigned long long n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987
    int i=help->i;
    unsigned long long C;
    int bin=0;
    C=1%n;  //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //0
    C=(C*C)%n; //0
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;
    C=(C*C)%n; //1
    C=(help->coded->code[i]*C)%n;

        switch(C)
        {
            case 32:
                help->uncoded->new[i]=' ';
                break;
            case 33:
                help->uncoded->new[i]='!';
                break;
            case 37:
                help->uncoded->new[i]='%';
                break;
            case 40:
                help->uncoded->new[i]='(';
                break;
            case 41:
                help->uncoded->new[i]=')';
                break;
            case 43:
                help->uncoded->new[i]='+';
                break;
            case 44:
                help->uncoded->new[i]=',';
                break;
            case 45:
                help->uncoded->new[i]='-';
                break;
            case 46:
                help->uncoded->new[i]='.';
                break;
            case 47:
                help->uncoded->new[i]='/';
                break;
            case 48:
                help->uncoded->new[i]='0';
                break;
            case 49:
                help->uncoded->new[i]='1';
                break;
            case 50:
                help->uncoded->new[i]='2';
                break;
            case 51:
                help->uncoded->new[i]='3';
                break;
            case 52:
                help->uncoded->new[i]='4';
                break;
            case 53:
                help->uncoded->new[i]='5';
                break;
            case 54:
                help->uncoded->new[i]='6';
                break;
            case 55:
                help->uncoded->new[i]='7';
                break;
            case 56:
                help->uncoded->new[i]='8';
                break;
            case 57:
                help->uncoded->new[i]='9';
                break;
            case 58:
                help->uncoded->new[i]=':';
                break;
            case 59:
                help->uncoded->new[i]=';';
                break;
            case 60:
                help->uncoded->new[i]='<';
                break;
            case 61:
                help->uncoded->new[i]='=';
                break;
            case 62:
                help->uncoded->new[i]='>';
                break;
            case 63:
                help->uncoded->new[i]='?';
                break;
            case 64:
                help->uncoded->new[i]='@';
                break;
            case 65:
                help->uncoded->new[i]='A';
                break;
            case 66:
                help->uncoded->new[i]='B';
                break;
            case 67:
                help->uncoded->new[i]='C';
                break;
            case 68:
                help->uncoded->new[i]='D';
                break;
            case 69:
                help->uncoded->new[i]='E';
                break;
            case 70:
                help->uncoded->new[i]='F';
                break;
            case 71:
                help->uncoded->new[i]='G';
                break;
            case 72:
                help->uncoded->new[i]='H';
                break;
            case 73:
                help->uncoded->new[i]='I';
                break;
            case 74:
                help->uncoded->new[i]='J';
                break;
            case 75:
                help->uncoded->new[i]='K';
                break;
            case 76:
                help->uncoded->new[i]='L';
                break;
            case 77:
                help->uncoded->new[i]='M';
                break;
            case 78:
                help->uncoded->new[i]='N';
                break;
            case 79:
                help->uncoded->new[i]='O';
                break;
            case 80:
                help->uncoded->new[i]='P';
                break;
            case 81:
                help->uncoded->new[i]='Q';
                break;
            case 82:
                help->uncoded->new[i]='R';
                break;
            case 83:
                help->uncoded->new[i]='S';
                break;
            case 84:
                help->uncoded->new[i]='T';
                break;
            case 85:
                help->uncoded->new[i]='U';
                break;
            case 86:
                help->uncoded->new[i]='V';
                break;
            case 87:
                help->uncoded->new[i]='W';
                break;
            case 88:
                help->uncoded->new[i]='X';
                break;
            case 89:
                help->uncoded->new[i]='Y';
                break;
            case 90:
                help->uncoded->new[i]='Z';
                break;
            case 97:
                help->uncoded->new[i]='a';
                break;
            case 98:
                help->uncoded->new[i]='b';
                break;
            case 99:
                help->uncoded->new[i]='c';
                break;
            case 100:
                help->uncoded->new[i]='d';
                break;
            case 101:
                help->uncoded->new[i]='e';
                break;
            case 102:
                help->uncoded->new[i]='f';
                break;
            case 103:
                help->uncoded->new[i]='g';
                break;
            case 104:
                help->uncoded->new[i]='h';
                break;
            case 105:
                help->uncoded->new[i]='i';
                break;
            case 106:
                help->uncoded->new[i]='j';
                break;
            case 107:
                help->uncoded->new[i]='k';
                break;
            case 108:
                help->uncoded->new[i]='l';
                break;
            case 109:
                help->uncoded->new[i]='m';
                break;
            case 110:
                help->uncoded->new[i]='n';
                break;
            case 111:
                help->uncoded->new[i]='o';
                break;
            case 112:
                help->uncoded->new[i]='p';
                break;
            case 113:
                help->uncoded->new[i]='q';
                break;
            case 114:
                help->uncoded->new[i]='r';
                break;
            case 115:
                help->uncoded->new[i]='s';
                break;
            case 116:
                help->uncoded->new[i]='t';
                break;
            case 117:
                help->uncoded->new[i]='u';
                break;
            case 118:
                help->uncoded->new[i]='v';
                break;
            case 119:
                help->uncoded->new[i]='w';
                break;
            case 120:
                help->uncoded->new[i]='x';
                break;
            case 121:
                help->uncoded->new[i]='y';
                break;
            case 122:
                help->uncoded->new[i]='z';
                break;
            default:
                help->uncoded->new[i]='#';
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
            fprintf(fp, "%c ", uncoded->new[i]);
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
            fprintf(fp, "%c ", uncoded->new[i]);
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
            fprintf(fp, "%c ", uncoded->new[i]);
        }
        fclose(fp);
    }
    return;
}