#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string code = argv[1];
    if (argc != 2)
    {
        return 1;
    }
    else if(strlen(code)!=26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    for (int i = 0, n = strlen(code); i < n; i++)
    {
        if (!(isupper(code[i])||islower(code[i])))
        {
            return 1;
        }
        for (int j = i+1; j < n; j++)
        {
            if (toupper(code[i])==toupper(code[j]))
            {
                return 1;
            }
        }
    }

    string s = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isupper(s[i]))
        {
            printf("%c",toupper(code[s[i]-'A']));
        }
        else if (islower(s[i]))
        {
            printf("%c",s[i] = tolower(code[s[i]-'a']));
        }
        else
        {
            printf("%c",s[i]);
        }
    }
    printf("\n");
}
