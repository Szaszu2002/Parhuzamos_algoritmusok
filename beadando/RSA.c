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
    int code;
}helper;

data* ScanFile();//szöveg beolvasása
data2* EncodingText( data *uncoded);//szöveg kódolása
data2* ParEncodingText( helper help);
void CodedFileDump(data2 *coded);//kódolt szöveg kiírása egy fájlba
data* Decoding(data2 *coded);//dekódolás
data* ParDecoding(helper help);
void DecodedFileDump(data *uncoded);//dekódolt szöveg kiírása egy fájlba 
void runtime_display(clock_t allsequencialtime, clock_t palltime, clock_t scanfile_time, clock_t pscanfile_time, clock_t encoding_time, clock_t pencoding_time, clock_t decoding_time, clock_t pdecoding_time, clock_t dump_time, clock_t pdump_time);     //futási idők kiírása egy fájlba



int main()
{
    clock_t allsequencialtime;  //
    clock_t palltime;
    clock_t start_time; //
    clock_t pstart_time; //
    clock_t encoding_time1; //
    clock_t encoding_time2; //
    clock_t encoding_time;  //
    clock_t pencoding_time1; //
    clock_t pencoding_time2;
    clock_t pencoding_time;
    clock_t decoding_time1; //
    clock_t decoding_time2; //
    clock_t decoding_time;  //
    clock_t pdecoding_time1;
    clock_t pdecoding_time2;
    clock_t pdecoding_time;
    clock_t end_time;
    clock_t pend_time;
    int i;

    start_time=clock();
    struct data *uncoded=Scanfile();

    encoding_time1=clock();
    struct data2 *coded=EncodingText(uncoded);
    encoding_time2=clock();
    encoding_time=encoding_time2-encoding_time1;

    CodedFileDump(coded);

    decoding_time1=clock();
    uncoded=Decoding(coded);
    decoding_time2=clock();
    decoding_time=decoding_time2-decoding_time1;

    DecodedFileDump(uncoded);
    end_time=clock();
    allsequencialtime=end_time-start_time;

    //párhuzamos rész!!
    
    pstart_time=clock();
    struct data *puncoded;
    struct data2 *pcoded;
    pcoded->n=(puncoded->n);
    *puncoded=Scanfile();
    struct helper *help;

    pencoding_time1=clock();
    for(i=0;i<puncoded.n;i++)
    {
        helper.i=i;
        helper.character=puncoded->character[i];
        //ParEncodingText()
    }
    pencoding_time2=clock();
    pencoding_time=pencoding_time2-pencoding_time1;

    CodedFileDump(pcoded);

    pdecoding_time1=clock();
    for(i=0;i<pcoded.n;i++)
    {
        help.i=i;
        help.code=pcoded->code[i];
        //ParDecoding()
    }
    
    pdecoding_time2=clock();
    pdecoding_time=pdecoding_time2-pdecoding_time1;

    DecodedFileDump(uncoded);
    pend_time=clock();
    palltime=pend_time-pstart_time;

    runtime_display(allsequencialtime, palltime, encoding_time, pencoding_time, decoding_time, pdecoding_time);
    return 0;
}

void runtime_display(clock_t allsequencialtime, clock_t palltime, clock_t encoding_time, clock_t pencoding_time, clock_t decoding_time, clock_t pdecoding_time)
{
    FILE *fp;
   
    fp=fopen("runtime.txt","a");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        fprintf(fp,"\n %.2lf; %.2lf; %.2lf; %.2lf; %.2lf; %.2lf;",allsequencialtime, palltime, encoding_time, pencoding_time, decoding_time, pdecoding_time);
        fclose(fp);
    }
    return;
}

data* ScanFile()
{
    struct data *uncoded;
    int size=0, number_of_lines, i=0;
    char ch;
    FILE *fp;

    fp=fopen("texts\text_quote.txt","r");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        while((ch = fgetc(fp)) != EOF) 
        {
            if(ch == '\n')
            {
                number_of_lines++;
            }
        }
        if (number_of_lines==0) 
        {
            printf("\nA fájl üres");
            return uncoded;
        }
        while(!feof(fp))
        {
            fscanf(fp,"%c",&(uncoded->character[i])); 
            i++;
            size++;   
        }
        fclose(fp);
        uncoded->n=size;
    }
    return uncoded;
}

data2* EncodingText( data *uncoded)
{
    struct data2 coded;
    coded.n=(uncoded->n);
    int i;
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    for(i=0;i<(uncoded->n);i++)
    {
        if(uncoded->character[i] == ' ')
        {
            coded.number[i]=32;
        }
        else if(uncoded->character[i] == '!')
        {
            coded.number[i]=33;
        }
        else if(uncoded->character[i] == '%')
        {
            coded.number[i]=37;
        }
        else if(uncoded->character[i] == '(')
        {
            coded.number[i]=40;
        }
        else if(uncoded->character[i] == ')')
        {
            coded.number[i]=41;
        }
        else if(uncoded->character[i] == '+')
        {
            coded.number[i]=43;
        }
        else if(uncoded->character[i] == ',')
        {
            coded.number[i]=44;
        }
        else if(uncoded->character[i] == '-')
        {
            coded.number[i]=45;
        }
        else if(uncoded->character[i] == '.')
        {
            coded.number[i]=46;
        }
        else if(uncoded->character[i] == '/')
        {
            coded.number[i]=47;
        }
        else if(uncoded->character[i] == '0')
        {
            coded.number[i]=48;
        }
        else if(uncoded->character[i] == '1')
        {
            coded.number[i]=49;
        }
        else if(uncoded->character[i] == '2')
        {
            coded.number[i]=50;
        }
        else if(uncoded->character[i] == '3')
        {
            coded.number[i]=51;
        }
        else if(uncoded->character[i] == '4')
        {
            coded.number[i]=52;
        }
        else if(uncoded->character[i] == '5')
        {
            coded.number[i]=53;
        }
        else if(uncoded->character[i] == '6')
        {
            coded.number[i]=54;
        }
        else if(uncoded->character[i] == '7')
        {
            coded.number[i]=55;
        }
        else if(uncoded->character[i] == '8')
        {
            coded.number[i]=56;
        }
        else if(uncoded->character[i] == '9')
        {
            coded.number[i]=57;
        }
        else if(uncoded->character[i] == ':')
        {
            coded.number[i]=58;
        }
        else if(uncoded->character[i] == ';')
        {
            coded.number[i]=59;
        }
        else if(uncoded->character[i] == '<')
        {
            coded.number[i]=60;
        }
        else if(uncoded->character[i] == '=')
        {
            coded.number[i]=61;
        }
        else if(uncoded->character[i] == '>')
        {
            coded.number[i]=62;
        }
        else if(uncoded->character[i] == '?')
        {
            coded.number[i]=63;
        }
        else if(uncoded->character[i] == '@')
        {
            coded.number[i]=64;
        }
        else if(uncoded->character[i] == 'A' || uncoded->character[i] == 'Á')
        {
            coded.number[i]=65;
        }
        else if(uncoded->character[i] == 'B')
        {
            coded.number[i]=66;
        }
        else if(uncoded->character[i] == 'C')
        {
            coded.number[i]=67;
        }
        else if(uncoded->character[i] == 'D')
        {
            coded.number[i]=68;
        }
        else if(uncoded->character[i] == 'E' || uncoded->character[i] == 'É')
        {
            coded.number[i]=69;
        }
        else if(uncoded->character[i] == 'F')
        {
            coded.number[i]=70;
        }
        else if(uncoded->character[i] == 'G')
        {
            coded.number[i]=71;
        }
        else if(uncoded->character[i] == 'H')
        {
            coded.number[i]=72;
        }
        else if(uncoded->character[i] == 'I')
        {
            coded.number[i]=73;
        }
        else if(uncoded->character[i] == 'J')
        {
            coded.number[i]=74;
        }
        else if(uncoded->character[i] == 'K')
        {
            coded.number[i]=75;
        }
        else if(uncoded->character[i] == 'L')
        {
            coded.number[i]=76;
        }
        else if(uncoded->character[i] == 'M')
        {
            coded.number[i]=77;
        }
        else if(uncoded->character[i] == 'N')
        {
            coded.number[i]=78;
        }
        else if(uncoded->character[i] == 'O' || uncoded->character[i] == 'Ó' || uncoded->character[i] == 'Ö' || uncoded->character[i] == 'Ő')
        {
            coded.number[i]=79;
        }
        else if(uncoded->character[i] == 'P')
        {
            coded.number[i]=80;
        }
        else if(uncoded->character[i] == 'Q')
        {
            coded.number[i]=81;
        }
        else if(uncoded->character[i] == 'R')
        {
            coded.number[i]=82;
        }
        else if(uncoded->character[i] == 'S')
        {
            coded.number[i]=83;
        }
        else if(uncoded->character[i] == 'T')
        {
            coded.number[i]=84;
        }
        else if(uncoded->character[i] == 'U' || uncoded->character[i] == 'Ú' || uncoded->character[i] == 'Ü' || uncoded->character[i] == 'Ű')
        {
            coded.number[i]=85;
        }
        else if(uncoded->character[i] == 'V')
        {
            coded.number[i]=86;
        }
        else if(uncoded->character[i] == 'W')
        {
            coded.number[i]=87;
        }
        else if(uncoded->character[i] == 'X')
        {
            coded.number[i]=88;
        }
        else if(uncoded->character[i] == 'Y')
        {
            coded.number[i]=89;
        }
        else if(uncoded->character[i] == 'Z')
        {
            coded.number[i]=90;
        }
        else if(uncoded->character[i] == 'a' || uncoded->character[i] == 'á')
        {
            coded.number[i]=97;
        }
        else if(uncoded->character[i] == 'b')
        {
            coded.number[i]=98;
        }
        else if(uncoded->character[i] == 'c')
        {
            coded.number[i]=99;
        }
        else if(uncoded->character[i] == 'd')
        {
            coded.number[i]=100;
        }
        else if(uncoded->character[i] == 'e' || uncoded->character[i] == 'é')
        {
            coded.number[i]=101;
        }
        else if(uncoded->character[i] == 'f')
        {
            coded.number[i]=102;
        }
        else if(uncoded->character[i] == 'g')
        {
            coded.number[i]=103;
        }
        else if(uncoded->character[i] == 'h')
        {
            coded.number[i]=104;
        }
        else if(uncoded->character[i] == 'i' || uncoded->character[i] == 'í')
        {
            coded.number[i]=105;
        }
        else if(uncoded->character[i] == 'j')
        {
            coded.number[i]=106;
        }
        else if(uncoded->character[i] == 'k')
        {
            coded.number[i]=107;
        }
        else if(uncoded->character[i] == 'l')
        {
            coded.number[i]=108;
        }
        else if((uncoded->character[i]) = 'm')
        {
            coded.number[i]=109;
        }
        else if(uncoded->character[i] == 'n')
        {
            coded.number[i]=110;
        }
        else if(uncoded->character[i] == 'o' || uncoded->character[i] == 'ó' || uncoded->character[i] ==  'ö' || uncoded->character[i] == 'ő')
        {
            coded.number[i]=111;
        }
        else if(uncoded->character[i] == 'p')
        {
            coded.number[i]=112;
        }
        else if(uncoded->character[i] == 'q')
        {
            coded.number[i]=113;
        }
        else if(uncoded->character[i] == 'r')
        {
            coded.number[i]=114;
        }
        else if(uncoded->character[i] == 's')
        {
            coded.number[i]=115;
        }
        else if(uncoded->character[i] == 't')
        {
            coded.number[i]=116;
        }
        else if(uncoded->character[i] == 'u' || uncoded->character[i] == 'ú' || uncoded->character[i] == 'ü' || uncoded->character[i] == 'ű')
        {
            coded.number[i]=117;
        }
        else if(uncoded->character[i] == 'v')
        {
            coded.number[i]=118;
        }
        else if(uncoded->character[i] == 'w')
        {
            coded.number[i]=119;
        }
        else if(uncoded->character[i] == 'x')
        {
            coded.number[i]=120;
        }
        else if(uncoded->character[i] == 'y')
        {
            coded.number[i]=121;
        }
        else if(uncoded->character[i] == 'z')
        {
            coded.number[i]=122;
        }
        else
        {
            coded.number[i]=35;
        }
    }
    //titkosítás rész !!!
    for(i=0;i<(coded.n);i++)
    {
        int M=coded.number[i];
        int C;

        C=1%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        C=(C*C)%n;
        C=(M*C)%n;
        coded.code[i]=C;
    }

    return coded;
}

data2* ParEncodingText( helper help)
{
    struct data2 coded;
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;

    if(help.character == ' ')
    {
        coded.number[help.i]=32;
    }
    else if(help.character == '!')
    {
        coded.number[help.i]=33;
    }
    else if(help.character == '%')
    {
        coded.number[help.i]=37;
    }
    else if(help.character == '(')
    {
        coded.number[help.i]=40;
    }
    else if(help.character == ')')
    {
        coded.number[help.i]=41;
    }
    else if(help.character == '+')
    {
        coded.number[help.i]=43;
    }
    else if(help.character == ',')
    {
        coded.number[help.i]=44;
    }
    else if(help.character == '-')
    {
        coded.number[help.i]=45;
    }
    else if(help.character == '.')
    {
        coded.number[help.i]=46;
    }
    else if(help.character == '/')
    {
        coded.number[help.i]=47;
    }
    else if(help.character == '0')
    {
        coded.number[help.i]=48;
    }
    else if(help.character == '1')
    {
        coded.number[help.i]=49;
    }
    else if(help.character == '2')
    {
        coded.number[help.i]=50;
    }
    else if(help.character == '3')
    {
        coded.number[help.i]=51;
    }
    else if(help.character == '4')
    {
        coded.number[help.i]=52;
    }
    else if(help.character == '5')
    {
        coded.number[help.i]=53;
    }
    else if(help.character == '6')
    {
        coded.number[help.i]=54;
    }
    else if(help.character == '7')
    {
        coded.number[help.i]=55;
    }
    else if(help.character == '8')
    {
        coded.number[help.i]=56;
    }
    else if(help.character == '9')
    {
        coded.number[help.i]=57;
    }
    else if(help.character == ':')
    {
        coded.number[help.i]=58;
    }
    else if(help.character == ';')
    {
        coded.number[help.i]=59;
    }
    else if(help.character == '<')
    {
        coded.number[help.i]=60;
    }
    else if(help.character == '=')
    {
        coded.number[help.i]=61;
    }
    else if(help.character == '>')
    {
        coded.number[help.i]=62;
    }
    else if(help.character == '?')
    {
        coded.number[help.i]=63;
    }
    else if(help.character == '@')
    {
        coded.number[help.i]=64;
    }
    else if(help.character == 'A' || help.character == 'Á')
    {
        coded.number[help.i]=65;
    }
    else if(help.character == 'B')
    {
        coded.number[help.i]=66;
    }
    else if(help.character == 'C')
    {
        coded.number[help.i]=67;
    }
    else if(help.character == 'D')
    {
        coded.number[help.i]=68;
    }
    else if(help.character == 'E' || help.character == 'É')
    {
        coded.number[help.i]=69;
    }
    else if(help.character == 'F')
    {
        coded.number[help.i]=70;
    }
    else if(help.character == 'G')
    {
        coded.number[help.i]=71;
    }
    else if(help.character == 'H')
    {
        coded.number[help.i]=72;
    }
    else if(help.character == 'I')
    {
        coded.number[help.i]=73;
    }
    else if(help.character == 'J')
    {
        coded.number[help.i]=74;
    }
    else if(help.character == 'K')
    {
        coded.number[help.i]=75;
    }
    else if(help.character == 'L')
    {
        coded.number[help.i]=76;
    }
    else if(help.character == 'M')
    {
        coded.number[help.i]=77;
    }
    else if(help.character == 'N')
    {
        coded.number[help.i]=78;
    }
    else if(help.character == 'O' || help.character == 'Ó' || help.character == 'Ö' || help.character == 'Ő')
    {
        coded.number[help.i]=79;
    }
    else if(help.character == 'P')
    {
        coded.number[help.i]=80;
    }
    else if(help.character == 'Q')
    {
        coded.number[help.i]=81;
    }
    else if(help.character == 'R')
    {
        coded.number[help.i]=82;
    }
    else if(help.character == 'S')
    {
        coded.number[help.i]=83;
    }
    else if(help.character == 'T')
    {
        coded.number[help.i]=84;
    }
    else if(help.character == 'U' || help.character == 'Ú' || uhelp.character == 'Ü' || help.character == 'Ű')
    {
        coded.number[help.i]=85;
    }
    else if(help.character == 'V')
    {
        coded.number[help.i]=86;
    }
    else if(help.character == 'W')
    {
        coded.number[help.i]=87;
    }
    else if(help.character == 'X')
    {
        coded.number[help.i]=88;
    }
    else if(help.character == 'Y')
    {
        coded.number[help.i]=89;
    }
    else if(help.character == 'Z')
    {
        coded.number[help.i]=90;
    }
    else if(help.character == 'a' || help.character == 'á')
    {
        coded.number[help.i]=97;
    }
    else if(help.character == 'b')
    {
        coded.number[help.i]=98;
    }
    else if(help.character == 'c')
    {
        coded.number[help.i]=99;
    }
    else if(help.character == 'd')
    {
        coded.number[help.i]=100;
    }
    else if(help.character == 'e' || help.character == 'é')
    {
        coded.number[help.i]=101;
    }
    else if(help.character == 'f')
    {
        coded.number[help.i]=102;
    }
    else if(help.character == 'g')
    {
        coded.number[help.i]=103;
    }
    else if(help.character == 'h')
    {
        coded.number[help.i]=104;
    }
    else if(help.character == 'i' || help.character == 'í')
    {
        coded.number[help.i]=105;
    }
    else if(help.character == 'j')
    {
        coded.number[help.i]=106;
    }
    else if(help.character == 'k')
    {
        coded.number[help.i]=107;
    }
    else if(help.character == 'l')
    {
        coded.number[help.i]=108;
    }
    else if(help.character = 'm')
    {
        coded.number[help.i]=109;
    }
    else if(help.character == 'n')
    {
        coded.number[help.i]=110;
    }
    else if(help.character== 'o' || help.character == 'ó' || help.character ==  'ö' || help.character == 'ő')
    {
        coded.number[help.i]=111;
    }
    else if(help.character == 'p')
    {
        coded.number[help.i]=112
    }
    else if(help.character == 'q')
    {
        coded.number[help.i]=113;
    }
    else if(help.character == 'r')
    {
        coded.number[help.i]=114;
    }
    else if(help.character == 's')
    {
        coded.number[help.i]=115;
    }
    else if(help.character == 't')
    {
        coded.number[help.i]=116;
    }
    else if(help.character == 'u' || help.character == 'ú' || help.character == 'ü' || help.character == 'ű')
    {
        coded.number[help.i]=117;
    }
    else if(help.character == 'v')
    {
        coded.number[help.i]=118;
    }
    else if(help.character == 'w')
    {
        coded.number[help.i]=119;
    }
    else if(help.character == 'x')
    {
        coded.number[help.i]=120;
    }
    else if(help.character == 'y')
    {
        coded.number[help.i]=121;
    }
    else if(help.character == 'z')
    {
        coded.number[help.i]=122;
    }
    else
    {
         coded.number[help.i]=35;
    }
    //titkosítás rész !!!
    
    int M=coded.number[help.i];
    int C;

    C=1%n;
    C=(M*C)%n;
    C=(C*C)%n;
    C=(C*C)%n;
    C=(M*C)%n;
    C=(C*C)%n;
    C=(M*C)%n;
    coded.code[help.i]=C;

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

data* Decoding(data2 *coded)
{
    int i;
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987
    struct data uncoded;

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
            uncoded.new[i]=' ';
        }
        else if(C == 33)
        {
            uncoded.new[i]='!';
        }
        else if(C == 35)
        {
            uncoded.new[i]='%';
        }
        else if(C == 40)
        {
            uncoded.new[i]='(';
        }
        else if(C == 41)
        {
            uncoded.new[i]=')';
        }
        else if(C == 43)
        {
            uncoded.new[i]='+';
        }
        else if(C == 44)
        {
            uncoded.new[i]=',';
        }
        else if(C == 45)
        {
            uncoded.new[i]='-';
        }
        else if(C == 46)
        {
            uncoded.new[i]='.';
        }
        else if(C == 47)
        {
            uncoded.new[i]='/';
        }
        else if(C == 48)
        {
            uncoded.new[i]='0';
        }
        else if(C == 49)
        {
            uncoded.new[i]='1';
        }
        else if(C == 50)
        {
            uncoded.new[i]='2';
        }
        else if(C == 51)
        {
            uncoded.new[i]='3';
        }
        else if(C == 52)
        {
            uncoded.new[i]='4';
        }
        else if(C == 53)
        {
            uncoded.new[i]='5';
        }
        else if(C == 54)
        {
            uncoded.new[i]='6';
        }
        else if(C == 55)
        {
            uncoded.new[i]='7';
        }
        else if(C == 56)
        {
            uncoded.new[i]='8';
        }
        else if(C == 57)
        {
            uncoded.new[i]='9';
        }
        else if(C == 58)
        {
            uncoded.new[i]=':';
        }
        else if(C == 59)
        {
            uncoded.new[i]=';';
        }
        else if(C == 60)
        {
            uncoded.new[i]='<';
        }
        else if(C == 61)
        {
            uncoded.new[i]='=';
        }
        else if(C == 62)
        {
            uncoded.new[i]='>';
        }
        else if(C == 63)
        {
            uncoded.new[i]='?';
        }
        else if(C == 64)
        {
            uncoded.new[i]='@';
        }
        else if(C == 65)
        {
            uncoded.new[i]='A';
        }
        else if(C == 66)
        {
            uncoded.new[i]='B';
        }
        else if(C == 67)
        {
            uncoded.new[i]='C';
        }
        else if(C == 68)
        {
            uncoded.new[i]='D';
        }
        else if(C == 69)
        {
            uncoded.new[i]='E';
        }
        else if(C == 70)
        {
            uncoded.new[i]='F';
        }
        else if(C == 71)
        {
            uncoded.new[i]='G';
        }
        else if(C == 72)
        {
            uncoded.new[i]='H';
        }
        else if(C == 73)
        {
            uncoded.new[i]='I';
        }
        else if(C == 74)
        {
            uncoded.new[i]='J';
        }
        else if(C == 75)
        {
            uncoded.new[i]='K';
        }
        else if(C == 76)
        {
            uncoded.new[i]='L';
        }
        else if(C == 77)
        {
            uncoded.new[i]='M';
        }
        else if(C == 78)
        {
            uncoded.new[i]='N';
        }
        else if(C == 79)
        {
            uncoded.new[i]='O';
        }
        else if(C == 80)
        {
            uncoded.new[i]='P';
        }
        else if(C == 81)
        {
            uncoded.new[i]='Q';
        }
        else if(C == 82)
        {
            uncoded.new[i]='R';
        }
        else if(C == 83)
        {
            uncoded.new[i]='S';
        }
        else if(C == 84)
        {
            uncoded.new[i]='T';
        }
        else if(C == 85)
        {
            uncoded.new[i]='U';
        }
        else if(C == 86)
        {
            uncoded.new[i]='V';
        }
        else if(C == 87)
        {
            uncoded.new[i]='W';
        }
        else if(C == 88)
        {
            uncoded.new[i]='X';
        }
        else if(C == 89)
        {
            uncoded.new[i]='Y';
        }
        else if(C == 90)
        {
            uncoded.new[i]='Z';
        }
        else if(C == 97)
        {
            uncoded.new[i]='a';
        }
        else if(C == 98)
        {
            uncoded.new[i]='b';
        }
        else if(C == 99)
        {
            uncoded.new[i]='c';
        }
        else if(C == 100)
        {
            uncoded.new[i]='d';
        }
        else if(C == 101)
        {
            uncoded.new[i]='e';
        }
        else if(C == 102)
        {
            uncoded.new[i]='f';
        }
        else if(C == 103)
        {
            uncoded.new[i]='g';
        }
        else if(C == 104)
        {
            uncoded.new[i]='h';
        }
        else if(C == 105)
        {
            uncoded.new[i]='i';
        }
        else if(C == 106)
        {
            uncoded.new[i]='j';
        }
        else if(C == 107)
        {
            uncoded.new[i]='k';
        }
        else if(C == 108)
        {
            uncoded.new[i]='l';
        }
        else if(C == 109)
        {
            uncoded.new[i]='m';
        }
        else if(C == 110)
        {
            uncoded.new[i]='n';
        }
        else if(C == 111)
        {
            uncoded.new[i]='o';
        }
        else if(C == 112)
        {
            uncoded.new[i]='p';
        }
        else if(C == 113)
        {
            uncoded.new[i]='q';
        }
        else if(C == 114)
        {
            uncoded.new[i]='r';
        }
        else if(C == 115)
        {
            uncoded.new[i]='s';
        }
        else if(C == 116)
        {
            uncoded.new[i]='t';
        }
        else if(C == 117)
        {
            uncoded.new[i]='u';
        }
        else if(C == 118)
        {
            uncoded.new[i]='v';
        }
        else if(C == 119)
        {
            uncoded.new[i]='w';
        }
        else if(C == 120)
        {
            uncoded.new[i]='x';
        }
        else if(C == 121)
        {
            uncoded.new[i]='y';
        }
        else if(C == 122)
        {
            uncoded.new[i]='z';
        }
        else
        {
            uncoded.new[i]='#';
        }
    }
    return uncoded;
}

data* ParDecoding(helper help)
{
    int p=1039;
    int q=2617;
    int n=p*q;
    int e=11;
    int d=((7*(p-1)*(q-1))+1)/e;  //1727987
    struct data uncoded;

    int C;
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
        uncoded.new[help.i]=' ';
    }
    else if(C == 33)
    {
        uncoded.new[help.i]='!';
    }
    else if(C == 35)
    {
        uncoded.new[help.i]='%';
    }
    else if(C == 40)
    {
        uncoded.new[help.i]='(';
    }
    else if(C == 41)
    {
        uncoded.new[help.i]=')';
    }
    else if(C == 43)
    {
        uncoded.new[help.i]='+';
    }
    else if(C == 44)
    {
        uncoded.new[help.i]=',';
    }
    else if(C == 45)
    {
        uncoded.new[help.i]='-';
    }
    else if(C == 46)
    {
        uncoded.new[help.i]='.';
    }
    else if(C == 47)
    {
        uncoded.new[help.i]='/';
    }
    else if(C == 48)
    {
        uncoded.new[help.i]='0';
    }
    else if(C == 49)
    {
        uncoded.new[help.i]='1';
    }
    else if(C == 50)
    {
        uncoded.new[help.i]='2';
    }
    else if(C == 51)
    {
        uncoded.new[help.i]='3';
    }
    else if(C == 52)
    {
        uncoded.new[help.i]='4';
    }
    else if(C == 53)
    {
        uncoded.new[help.i]='5';
    }
    else if(C == 54)
    {
        uncoded.new[help.i]='6';
    }
    else if(C == 55)
    {
        uncoded.new[help.i]='7';
    }
    else if(C == 56)
    {
        uncoded.new[help.i]='8';
    }
    else if(C == 57)
    {
        uncoded.new[help.i]='9';
    }
    else if(C == 58)
    {
        uncoded.new[help.i]=':';
    }
    else if(C == 59)
    {
        uncoded.new[help.i]=';';
    }
    else if(C == 60)
    {
        uncoded.new[help.i]='<';
    }
    else if(C == 61)
    {
        uncoded.new[help.i]='=';
    }
    else if(C == 62)
    {
        uncoded.new[help.i]='>';
    }
    else if(C == 63)
    {
        uncoded.new[help.i]='?';
    }
    else if(C == 64)
    {
        uncoded.new[help.i]='@';
    }
    else if(C == 65)
    {
        uncoded.new[help.i]='A';
    }
    else if(C == 66)
    {
        uncoded.new[help.i]='B';
    }
    else if(C == 67)
    {
        uncoded.new[help.i]='C';
    }
    else if(C == 68)
    {
        uncoded.new[help.i]='D';
    }
    else if(C == 69)
    {
        uncoded.new[help.i]='E';
    }
    else if(C == 70)
    {
        uncoded.new[help.i]='F';
    }
    else if(C == 71)
    {
        uncoded.new[help.i]='G';
    }
    else if(C == 72)
    {
        uncoded.new[help.i]='H';
    }
    else if(C == 73)
    {
        uncoded.new[help.i]='I';
    }
    else if(C == 74)
    {
        uncoded.new[help.i]='J';
    }
    else if(C == 75)
    {
        uncoded.new[help.i]='K';
    }
    else if(C == 76)
    {
        uncoded.new[help.i]='L';
    }
    else if(C == 77)
    {
        uncoded.new[help.i]='M';
    }
    else if(C == 78)
    {
        uncoded.new[help.i]='N';
    }
    else if(C == 79)
    {
        uncoded.new[help.i]='O';
    }
    else if(C == 80)
    {
        uncoded.new[help.i]='P';
    }
    else if(C == 81)
    {
        uncoded.new[help.i]='Q';
    }
    else if(C == 82)
    {
        uncoded.new[help.i]='R';
    }
    else if(C == 83)
    {
        uncoded.new[help.i]='S';
    }
    else if(C == 84)
    {
        uncoded.new[help.i]='T';
    }
    else if(C == 85)
    {
        uncoded.new[help.i]='U';
    }
    else if(C == 86)
    {
        uncoded.new[help.i]='V';
    }
    else if(C == 87)
    {
        uncoded.new[help.i]='W';
    }
    else if(C == 88)
    {
        uncoded.new[help.i]='X';
    }
    else if(C == 89)
    {
        uncoded.new[help.i]='Y';
    }
    else if(C == 90)
    {
        uncoded.new[help.i]='Z';
    }
    else if(C == 97)
    {
        uncoded.new[help.i]='a';
    }
    else if(C == 98)
    {
        uncoded.new[help.i]='b';
    }
    else if(C == 99)
    {
        uncoded.new[help.i]='c';
    }
    else if(C == 100)
    {
        uncoded.new[help.i]='d';
    }
    else if(C == 101)
    {
        uncoded.new[help.i]='e';
    }
    else if(C == 102)
    {
        uncoded.new[help.i]='f';
    }
    else if(C == 103)
    {
        uncoded.new[help.i]='g';
    }
    else if(C == 104)
    {
        uncoded.new[help.i]='h';
    }
    else if(C == 105)
    {
        uncoded.new[help.i]='i';
    }
    else if(C == 106)
    {
        uncoded.new[help.i]='j';
    }
    else if(C == 107)
    {
        uncoded.new[help.i]='k';
    }
    else if(C == 108)
    {
        uncoded.new[help.i]='l';
    }
    else if(C == 109)
    {
        uncoded.new[help.i]='m';
    }
    else if(C == 110)
    {
        uncoded.new[help.i]='n';
    }
    else if(C == 111)
    {
        uncoded.new[help.i]='o';
    }
    else if(C == 112)
    {
        uncoded.new[help.i]='p';
    }
    else if(C == 113)
    {
        uncoded.new[help.i]='q';
    }
    else if(C == 114)
    {
        uncoded.new[help.i]='r';
    }
    else if(C == 115)
    {
        uncoded.new[help.i]='s';
    }
    else if(C == 116)
    {
        uncoded.new[help.i]='t';
    }
    else if(C == 117)
    {
        uncoded.new[help.i]='u';
    }
    else if(C == 118)
    {
        uncoded.new[help.i]='v';
    }
    else if(C == 119)
    {
        uncoded.new[help.i]='w';
    }
    else if(C == 120)
    {
        uncoded.new[help.i]='x';
    }
    else if(C == 121)
    {
        uncoded.new[help.i]='y';
    }
    else if(C == 122)
    {
        uncoded.new[help.i]='z';
    }
    else
    {
        uncoded.new[help.i]='#';
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
        for(i=0;i<uncoded->n;i++)
        {
            fprintf(fp, "%d ", uncoded->new[i]);
        }
        fclose(fp);
    }
    return;
}