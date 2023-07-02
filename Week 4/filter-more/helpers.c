#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double color = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0;
            int colour;
            if (color-((int)color)<0.5)
            {
                colour = (int)color;
            }
            else
            {
                colour = (int)color+1;
            }
            image[i][j].rgbtBlue = colour;
            image[i][j].rgbtRed = colour;
            image[i][j].rgbtGreen = colour;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = temp;

        }
    }

    return;
}

// Blur image
int rou(double num)
{
    if (num - ((int)num)<0.5)
    {
        return (int)num;
    }
    else
    {
        return (int)num+1;
    }
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0;
            float blue= 0;
            float green= 0;
            int counter= 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (!(i + k < 0 || i + k >= height || j + l < 0 || j + l >= width))
                    {

                    // Otherwise add to sums
                    red += temp[i + k][j + l].rgbtRed;
                    blue += temp[i + k][j + l].rgbtBlue;
                    green += temp[i + k][j + l].rgbtGreen;
                    counter++;
                    }
                }
            }
            // Get average and blur image
            image[i][j].rgbtRed = rou(red / counter);
            image[i][j].rgbtGreen = rou(green / counter);
            image[i][j].rgbtBlue = rou(blue / counter);
        }
    }
    return;
}






// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red = 0;
            float Gx_blue = 0;
            float Gx_green = 0;
            float Gy_red = 0;
            float Gy_blue = 0;
            float Gy_green = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (!(i + k < 0 || i + k >= height || j + l < 0 || j + l >= width))
                    {
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }
            int red = rou(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = rou(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = rou(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

            }
    }
    return;
}
