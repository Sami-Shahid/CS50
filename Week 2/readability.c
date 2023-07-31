#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    double letters = 0;
    double sen = 0;
    double word = 1;
    for (int i = 0; i < strlen(text); i++)
    {

        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sen++;
        }
        else if (text[i] != ' ')
        {
            letters++;
        }
        else
        {
            word++;
        }
    }

    sen = (sen / word ) * 100;
    letters = (letters / word) * 100;
    double index = 0.0588 * letters - 0.296 * sen - 15.7;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
}
