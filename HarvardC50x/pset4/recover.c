/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    FILE* inputRaw;                                 // raw file to scan for jpegs
    FILE* imageFile;                                // image file to write
    char imageName[7];                              // name of image file to write
    int imageNumber = 0;                            // counts found images for filenames
    BYTE buffer[512];                               // buffer containing bytes from raw data
    const BYTE signature1[4] = {255,216,255,224};   // JPEG signatures
    const BYTE signature2[4] = {255,216,255,225};
    int signatureDetected = 0;                      // flag for jpeg signature detection
    int jpegFound = 0;                              // flag to indicate first jpeg in data found
    int bytesRead;                                  // stores the number of bytes read from file -> buffer
    
    // ensure program has one argument
    if (argc != 2)
    {
        printf("This program requires one argument!\n");
        printf("Usage: ./recover filename\n");
        return 1;
    }   
    
    // open selected file, ensure that it opens correctly
    inputRaw = fopen(argv[1],"r");
    if(inputRaw == NULL)
    {
        printf("ERROR: could not open data file\n");
        return 2;
    }   
    
    // main loop
    while(1)
    {
        // read 512B from file into buffer
        bytesRead = fread(&buffer,sizeof(BYTE),512,inputRaw);
        
        // determine if new jpeg signature detected
        for(int i=0; i<4; i++)
        {
            if((signature1[i]!=buffer[i]) && (signature2[i]!=buffer[i]))
            {
                break;
            }
            if(i==3)
            {
                signatureDetected = 1;   
            }
        }
        
        // handle buffer data - put into new jpeg, old jpeg, or neither
        if(jpegFound == 0)
        {
            if(signatureDetected==1)
            {
                jpegFound = 1;
                sprintf(imageName,"000.jpg");   
                imageFile = fopen(imageName,"w");
                fwrite(&buffer,sizeof(BYTE),bytesRead,imageFile);
            }
        }
        else
        {
            if(signatureDetected==0)
            {
                fwrite(&buffer,sizeof(BYTE),bytesRead,imageFile);
            }
            else if(signatureDetected==1)
            {
                fclose(imageFile);
                imageNumber++;
                sprintf(imageName,"%.3d.jpg", imageNumber); 
                imageFile = fopen(imageName,"w");
                fwrite(&buffer,sizeof(BYTE),bytesRead,imageFile);
            }
        }        
        
        // check size of current buffer for eof and reset signature flag
        //   if eof found, close all files and return 0
        if(bytesRead<512)
        {
            fclose(imageFile);
            fclose(inputRaw);
            return 0;
        }
        else
        {
            signatureDetected = 0;        
        }
    }    
}

