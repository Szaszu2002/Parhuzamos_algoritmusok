#include <stdio.h>

void Scanfile()
{
    int size=0;
    char ch;
    FILE *fp;
    printf("\n 1size= %d",size);
    fp=fopen("text.txt","r");
    if(fp==NULL)
    {
        printf("\nSikertelen fájl megnyitás");
    }
    else
    {
        while((ch = fgetc(fp)) != EOF) 
        {
            
            printf("%c",ch);
            size++; 
            printf("\n 2size= %d",size);
        }
        if (size==0) 
        {
            printf("\nA fájl üres");
            return;
        }
        
        fclose(fp);
        printf("\n size= %d",size);
    }
    return;
}

int main()
{
    Scanfile();
    return 0;
}
