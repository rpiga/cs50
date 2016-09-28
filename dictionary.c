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

// constants
#define HASHTABLESIZE 1800

// total words in dictionary
unsigned int total_words = 0;

// structs
typedef struct 
_node
{
    char* wurd;
    int wurdl;
    struct _node* next;
}
node;

// prototypes
int     hash_this (const char* word);
void    init_hashtable(void);
bool    insert_node (const char* word);
void    navigate_array(void);
char*   strtolower(const char* s);

// define base hashtable array
node* hashtable[HASHTABLESIZE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    char* wordin = NULL;
    int wordl = strlen(word);
    
    // this is malloc'ed inside the function strtolower
    wordin = strtolower(word);
    int hash_idx = hash_this(wordin);

	node* ptr;

	for(ptr = hashtable[hash_idx]; ptr != NULL; ptr = ptr->next)
	{
	    if(ptr->wurdl == wordl)
	    {
            if (strcmp(wordin, ptr->wurd) == 0) 
            {
                free(wordin);
                return true;
            }
	    }
	}

    free(wordin);
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO

    // open dictionary file
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return false;
    }
    
    init_hashtable();
    
    // read file line by line
    char buffer[60];
    while ( fgets (buffer, 60, fp) != NULL )
    {
        // strip \n from tail
        strtok(buffer,"\n");
        // create node in the hashtable
        if (insert_node(buffer)) total_words++;
    }
    
    //navigate_array();
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
	node* ptr, *tmp;

	for(int i = 0; i < HASHTABLESIZE; i++)
	{
        ptr = hashtable[i];
        
        while(ptr != NULL)
        {
            tmp = ptr->next;
            free(ptr->wurd);
            free(ptr);
            ptr = tmp;
        }
	}
	
	return true;
}

/**
 * Hash function
 */
int hash_this (const char* word)
{
    int i = 0, sum = 0;
    
    while( (isalpha(word[i]) || word[i] == '\'') && word[i] != '\0' )
    {
        sum += (int) tolower(word[i]);
        i++;    
    }
    
    return sum % HASHTABLESIZE;
}

bool insert_node (const char* word)
{
    //printf("DEBUG: ** insert_node() **\n");
    
    node* newptr = malloc(sizeof(node));
    if (newptr == NULL) return false;
    
    node* ptr = NULL;
    
    newptr->wurd = (char*) malloc( (strlen(word) + 1) * sizeof(char) );
    strcpy(newptr->wurd, word);
    newptr->wurd[strlen(word)] = '\0';
    newptr->wurdl = strlen(newptr->wurd);
    newptr->next = NULL;
    
    int hash_idx = hash_this(word);
    // printf("DEBUG: hash %d\n", hash_idx);

    ptr = hashtable[hash_idx];

    // create last node
    // while(ptr->next != NULL)
    //     ptr = ptr->next;
    
    // ptr->next = newptr;
    
    // create first node
    // if (ptr->next == NULL)
    // {
    //     ptr->next = newptr;
    // }
    // else
    // {
        // if not, point new node to first element in hashtable
        newptr->next = ptr->next;
        // switch first element in hashtable to point new node 
        ptr->next = newptr;
        // printf("DEBUG: W %s next %s\n", hashtable[hash_idx]->wurd, (char*) hashtable[hash_idx]->next);
    // }

    return true;
}

/**
 * Navigate through the hashtable
 */
void navigate_array (void)
{
    // printf("DEBUG: ** navigate_array() **\n");
    // create pointer
	node* ptr;

	for( int i = 0; i < HASHTABLESIZE; i++)
	{
    	for(ptr = hashtable[i]; ptr != NULL; ptr = ptr->next)
    	{
			if(ptr->wurd)
			{
                printf("DEBUG: i %d wurd %s\n", i, ptr->wurd);
			}
		}

	}
}

/**
 * Init the hashtable
 */
void init_hashtable(void)
{

    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        node* tmp = calloc(1, sizeof(node));
        if(tmp == NULL) exit (1);
        
        tmp->next = NULL;
        
        hashtable[i] = tmp;
    }
    
    return;
}

/**
 * string to lower
 */
char* strtolower(const char* s)
{
    char* result;
    int i = 0;
    
    result = malloc( (strlen(s) + 1) * sizeof(char));
    
    while(s[i])
    {
        result[i] = tolower(s[i]);
        i++;
    }
    result[i] = '\0';
    
    return result;
}