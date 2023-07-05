// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 9999;

// Hash table
node *table[N];
long dsize = 0;

bool check(const char *word)
{
    node *temp = table[hash(word)];

    while (temp != NULL)
    {
        if(strcasecmp(temp -> word, word) == 0)
        {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    long sum = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += tolower(word[i]);
    }
    return(sum%9999);

}

// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    char next_[LENGTH + 1];
    while (fscanf(dict, "%s", next_) != EOF)
    {
        dsize++;
        node *n = malloc(sizeof(node));
        if (n==NULL)
        {
            printf("Memory Error");
            return false;
        }
        strcpy(n->word, next_);
        int x = hash(next_);
        n->next = table[x];
        table[x] = n;
    }
    fclose(dict);
    return true;
}


unsigned int size(void)
{
    // TODO
    return dsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while(n!=NULL)
        {
            node *temp = n;
            n = n->next;
            free(temp);
        }
    }
    return true;
}
