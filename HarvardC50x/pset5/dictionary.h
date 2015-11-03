/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// define trie node
typedef struct node
{
   bool isWord;
   struct node* children[27];
} node;

// Global variables
node* dictTrie;      // dictionary head pointer

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**********************************
*                                 *
*      Additional Functions       *
*                                 *
**********************************/

/**
 * Returns a new trienode with correctly-initialized values
 */
node* NewNode(void);

/**
 * Returns correct hash value from input chars a-z or '
 *   Does not check if input not allowed - error checking
 *   occurs in dictionary.c functions
 */
int GetHash(int character);

/**
 * Recursive function that deletes all nodes in trie when 
 *   called at head pointer
 */
void DeleteTrie(node* trieNode);

#endif // DICTIONARY_H
