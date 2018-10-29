/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define SIZE 500

typedef struct node
{
    char word[LENGTH+1];
    struct node * next;
} node;

// Set hashtable like a global variable
node* hashtable[SIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int hashCode = hashFunction(word);
    for(node* trav = hashtable[hashCode]; trav!=NULL; trav= trav->next)
        if(strcasecmp(trav->word,word)==0)
            return true;
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* file = fopen(dictionary,"r");
    char word[LENGTH+1];

    // Set all elements (pointers) of hashtable to NULL
    for(int i=0; i<SIZE; i++)
        hashtable[i] = NULL;

    while(fscanf(file,"%s",word)!=EOF)
    {
        node* newNode = malloc(sizeof(node));
        if(newNode==NULL)
        {
            unload();
            return false;
        }

        strcpy(newNode->word,word);
        int hashCode = hashFunction(newNode->word);

        newNode->next = hashtable[hashCode];
        hashtable[hashCode] = newNode;
    }

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    int count=0;
    for(int i=0; i<SIZE;i++)
        for(node* trav=hashtable[i]; trav!=NULL;trav=trav->next)
            count++;
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for(int i=0; i<SIZE; i++)
    {
        node* trav = hashtable[i];
        while(trav!=NULL)
        {
            node* temp = trav;
            trav =  trav->next;
            free(temp);
        }
    }
    return true;
}

int hashFunction(const char* str)
{
    int sum=0;
    for(int i=0; *(str+i)!='\0'; i++)
        sum += tolower((int)*(str+i));
    return sum%SIZE;
}