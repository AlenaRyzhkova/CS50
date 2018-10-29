#include <cs50.h>
#include <stdio.h>

void printCh(int q, char ch);

int main (void)
{
    int h=0;
    do
    {
        h = get_int("Please, give me possitive int:");
        if(h<=0 || h>23)
            continue;
        for(int i=0; i<h;i++)
        {
            printCh(h-i-1,' ');
            printCh(i+2,'#');
            printf("  ");
            printCh(i+2,'#');
            printf("\n");
        }
    }while(h<=0 || h>23);
}

void printCh(int q, char ch)
{
    for(int s=0; s<q;s++)
        {
            printf("%c",ch);
        }
}