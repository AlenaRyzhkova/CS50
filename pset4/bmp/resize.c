/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resize BMP, increasint it in n times (n between 1 and 100).
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize n infile outfile\n");
        return 1;
    }

    // remember resize factor
    int n = atoi(argv[1]);
    if(n<1 || n>100)
    {
        printf("Usage: resize n infile outfile\n");
        printf("Resize factor n must be integer between 1 and 100\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // cuonstruct output file's headers
    BITMAPFILEHEADER bfOut;
    BITMAPINFOHEADER biOut;

    bfOut = bf;
    biOut = bi;

    biOut.biWidth = bi.biWidth*n;
    biOut.biHeight = bi.biHeight*n;
    int paddingInput = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut =  (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    biOut.biSizeImage = ((sizeof(RGBTRIPLE)*biOut.biWidth + paddingOut))*abs(biOut.biHeight);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // create array - row in outputfile
        RGBTRIPLE arrTriple[biOut.biWidth];
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // write to array n times
            for(int k=j*n; k<j*n+n; k++)
                arrTriple[k]=triple;
        }

        // write triple array and output padding to outfile n times
        for(int r = 0; r<n; r++)
        {
            fwrite(arrTriple, sizeof(RGBTRIPLE)*biOut.biWidth, 1, outptr);
            for (int k = 0; k < paddingOut; k++)
                fputc(0x00, outptr);
        }
        // skip over padding in input filed
        fseek(inptr, paddingInput, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
