#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int x = 0; x < width; x++)
        {
            if (image[i][x].rgbtBlue==0x00&&image[i][x].rgbtGreen==0x00&&image[i][x].rgbtRed==0x00)
            {
                image[i][x].rgbtBlue = 0xff;
            }
        }
    }
}
