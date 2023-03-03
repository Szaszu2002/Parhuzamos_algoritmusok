#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char ch;
    char filename[50];
    printf("Adja meg a fájl nevét! ");
    scanf("%s",filename);
    fp=fopen(filename,"w");
    printf("Szöveg kiírása");
    while((ch=getchar())!='#')
    {
        putc(ch,fp);
    }
    fclose(fp);

    return 0;
}