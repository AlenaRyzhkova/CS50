#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

typedef uint8_t  BYTE;

bool isStartJPEG(BYTE block[512]);


int main(void)
{
    // open memory card file
    FILE* fp = fopen("card.raw","r");
    // check that operation has been succeed
    if(fp == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }

    BYTE buffer[512];
    int countJPG=0;
    FILE * jpg;

    while(fread(buffer, 512, 1, fp)>0)
    {
        if(isStartJPEG(buffer))
        {
            if(countJPG>0)
                fclose(jpg);
            char filename[8];
            sprintf(filename,"%03i.jpg", countJPG);
            jpg = fopen(filename,"w");
            countJPG++;
        }
        if(countJPG>0)
            fwrite(buffer,512,1,jpg);
    }
    if(countJPG>0)
        fclose(jpg);
    fclose(fp);
}

bool isStartJPEG(BYTE block[512])
{
    if(
        block[0] == 0xff &&
        block[1] == 0xd8 &&
        block[2] == 0xff &&
        (block[3] & 0xf0) == 0xe0
    )
        return true;
    else
        return false;
}

