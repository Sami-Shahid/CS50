#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Getting name
    string name = get_string("What's your name? ");
    //Printing name
    printf("hello, %s\n", name);
}