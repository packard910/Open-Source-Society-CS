/**
 * resize.c 
 * modification of original copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, outputting an image that
 *   is an integer n times larger than the original.  The
 *   program modifies the necessary fields in the BMP file
 *   header and makes sure to add the necessary 0 bytes
 *   at the end of pixel rows.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        printf("outfile will be n times larger than infile\n");
        return 1;
    }
    
    // get resize factor 
    int resizeFactor = atoi(argv[1]);
    if (resizeFactor > 100 || resizefactor < 1)
    {
        printf("Usage: ./copy n infile outfile\n");
        printf("ERROR: n must be an integer in [1,100]\n");
        return 10;
    }
    
    // make variables to store old image height, width before resize
    int oldImageWidth;
    int oldImageHeight;

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }
    
    // make necessary changes in BITMAPFILEHEADER and BITMAPINFOHEADER   
    bf.bfSize = bf.bfSize*resizeFactor*resizeFactor;  // bytes in file increase by factor of n^2    
    oldImageWidth = bi.biWidth;                       // store old image width and multiply by n
    bi.biWidth *= resizeFactor;
    oldImageHeight = bi.biHeight;                     // store old image height and multiply by n
    bi.biHeight *= resizeFactor; 
   
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // variable to store a full line of pixels
    RGBTRIPLE triples[oldImageWidth];
    
    // iterate over infile's scanlines
    for (int i = 0; i < abs(oldImageHeight); i++)
    {
        // read in one full line of pixels
        for (int j = 0; j < oldImageWidth; j++)
        {
            // read RGBTRIPLE for each pixel into array
            fread(&(triples[j]), sizeof(RGBTRIPLE), 1, inptr);
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // make n rows from this line
        for (int a = 0; a < resizeFactor; a++)
        {
            // write n of each pixel in each row
            for (int b = 0; b < oldImageWidth; b++)
            {
                for (int c = 0; c < resizeFactor; c++)
                {
                    fwrite(&(triples[b]), sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add the padding to the end of each line
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
