#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Invalid Command lines\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    char *infile = argv[1];
    char *outfile = argv[2];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }
    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header)==1)
    {
        printf("Invalid file format\n");
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *out = fopen(outfile, "w");
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, out);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block = get_block_size(header);
    // Write reversed audio to file
    // TODO #8
    // Write reversed audio to file
    // TODO #8
    BYTE arr[block];

    fseek(inptr, 0, SEEK_END);

    long audio_size = ftell(inptr) - sizeof(WAVHEADER);
    int audio_block = (int) audio_size / block;


    for (int i = audio_block - 1; i >= 0; i--)
    {
        fseek(inptr, sizeof(WAVHEADER) + i * block, SEEK_SET);
        fread(arr, block, 1, inptr);
        fwrite(arr, block, 1, out);
    }
    fclose(inptr);
    fclose(out);}

int check_format(WAVHEADER header)
{
    // TODO #4
    char arr[] = {'W','A','V','E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != arr[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * header.bitsPerSample / 8);
}
