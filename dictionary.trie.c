/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Define nodes for Trie
#define PATHSIZE 27

typedef struct _node
{
    bool is_word; // flag for word
    struct _node* path[PATHSIZE]; // 26 alpa (a-z) + apostrophe + spare
}
node;

node* new_node(void)
{
    // create and allocate new empty node
    node* newptr = malloc(sizeof(node));
    // return if something not working
    if (newptr == NULL) return false;
    
    // initialize values
    newptr->is_word = false;
    for (int i = 0; i < PATHSIZE; i++)
    {
        newptr->path[i] = NULL;
    }
    
    return newptr;
}

unsigned int total_words = 0;

// initialize Trie
node* root = NULL;
//node* t_node = NULL;

// prototypes
bool insert(char* word, int s, node* root);
bool remov(node* target);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO - OK
    int n = strlen(word), idx = 0;
    node* ptr = root;

    for (int i = 0; i < n; i++)
    {
        if(isalpha(word[i])) idx = (int) tolower(word[i]) - 'a';
        else if ( (int) word[i] == '\'' ) idx = 26;
        
        if ( ptr->path[idx] == NULL )
        {
            return false;
        }
        else
        {
            ptr = ptr->path[idx];
        }
    }
    
    if (ptr->is_word)
    {
        return true;
    }
    
    return false;
 }

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool loadNEW2(const char* dictionary)
{
    // Open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    
    root = new_node();
    node* ptr = root;

//int index = 0;
    int p;
    char buffer[LENGTH];
    
    while ( fgets (buffer, LENGTH, fp) != NULL ) 
    {
        int s = strlen(buffer);
        //printf("DEBUG: word %c\n", buffer[3]);
        
        for(int i = 0; i < s - 1; i++)
        {
            // calculate char index ()
            if (isalpha(buffer[i]))
            {
                // char is a-z
                p = (int)buffer[i] - (int) 'a';
            }
            else if ( (int) buffer[i] == '\'' )
                // char is apostrophe '
                p = 26;
            
            // check if index exists
            if ( ! ptr->path[p] )
                // create it
                ptr->path[p] = new_node();
            // set pointer to nex index
            ptr = ptr->path[p];
        }
        ptr->is_word = true;
        total_words++;
        ptr = root;
//        index = 0;
    }
    
    
    fclose(fp);
    
    return true;
}

bool loadNEW(const char* dictionary)
{
    // Open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    
    root = new_node();
    node* ptr = root;

    int index = 0;
    int p;
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            if (isalpha(c))
                p = (int) tolower(c) - (int) 'a';
            else if ( (int) c == '\'' )
                p = 26;

            if ( ! ptr->path[p] )
                // create it
                ptr->path[p] = new_node();
            // set pointer to nex index
            ptr = ptr->path[p];
            
            index++;
        }
        else
        {
            ptr->is_word = true;
            total_words++;
            ptr = root;
            index = 0;
        }
    }

    fclose(fp);
    
    return true;
}


bool load(const char* dictionary)
{
    // TODO - OK
    
    // Open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    
    root = new_node();
    
    // Read dictionary line by line
    char buffer[LENGTH];
    int index = 0;
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // char is alpha, not a number, or apostrophe
            // so it is inserted in the Trie
            buffer[index] = c;
            index++;
        }
        else if (index > 0)
        {
            // word ends with \0
            // index is re initalized for the next word
            insert(buffer, index, root);
            index = 0;
        }
    }

    fclose(fp);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    
    return total_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    // node* ptr = root;
    
    // while (ptr)
    // {
    //     for (int i = 0; i < PATHSIZE; i++)
    //     {
    //         if (ptr->path[i])
    //         {
    //             ptr = ptr->path[i];
    //         }
    //     }
    // }

    // remove nodes
    if (remov(root)) return true;
    return false;
}


bool remov(node* target)
{
    node* ptr = target;

    for (int i = 0; i < PATHSIZE; i++)
    {
        if (ptr->path[i] != NULL)
        {
            remov(ptr->path[i]);
        }
    }
    free(ptr);

    return true;
}

/**
 * Insert word from dictionary into Trie.
 */
bool insert(char* word, int s, node* trienode)
{
    int index = 0;
    //, level = 0;
    
    // define pointer
    node* ptr = trienode;
    
    // walk through the word
    for(int i = 0; i < s; i++)
    {
        // calculate char index ()
        if (isalpha(word[i]))
        {
            // char is a-z
            index = (int)word[i] - (int) 'a';
        }
        else
            // char is apostrophe '
            index = 26;
        
        // check if index exists
        if ( ! ptr->path[index] )
            // create it
            ptr->path[index] = new_node();
        // set pointer to nex index
        ptr = ptr->path[index];
    }
    
    // word inserted
    // flag it
    ptr->is_word = true;
    total_words++;

    return true;
}