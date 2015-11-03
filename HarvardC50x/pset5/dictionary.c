/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

int dictTrieSize=0;  // number of words in dictionary trie

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* checkptr;        // used to traverse trie
    int charNum=0;         // index for char in word
    int charHash;          // hash value of current char
    
    // checkptr starts at head of dictionary
    checkptr = dictTrie;
    
    // loop until reaching null terminator '/0'
    //   move checkptr with every char in string
    //   if pointer to NULL reached, return false
    while(1)
    {
        // break on reaching end of word
        if(word[charNum]=='\0')
        {
            break;
        }
        // move to next node, returning false if NULL
        charHash = GetHash(tolower(word[charNum]));
        if(checkptr->children[charHash] == NULL)
        {
            return false;
        }
        // ignore characters not in expected hash range
        else if(charHash>=0 && charHash<27)
        {
            checkptr = checkptr->children[charHash];
            charNum++;
        }
    }
    // return true or false depending on isWord value in node
    if(checkptr->isWord == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* inputFile;     // pointer to dictionary file
    node* nodeptr;       // pointer used to traverse trie
    char* lineBuff=NULL; // contains current line in file
    int buffIndex;       // index over buffered file string
    int hashVal;         // hash value of current buffer char
   
    // load dictionary file - return false if this fails
    inputFile = fopen(dictionary, "r");
    if (inputFile == NULL)
    {
        return false;
    }
    
    // allocate memory for line buffer
    lineBuff = (char *) malloc((LENGTH+2)*sizeof(char));
        
    // loop over lines in dictionary file
    while(1)
    {      
        // read next line into buffer    
        if(fgets(lineBuff,(LENGTH+2)*sizeof(char),inputFile)==NULL)
        {
            break;
        }
    
        // reset buffer index and node pointer
        buffIndex = 0;
        nodeptr = dictTrie;

        // loop over buffer until reaching terminator or EOF  
        while(1)
        {
            if(lineBuff[buffIndex]=='\0')
            {
                nodeptr->isWord = true;
                dictTrieSize++;
                break;   
            }
            else if(lineBuff[buffIndex]!='\n')
            {
                hashVal = GetHash(lineBuff[buffIndex]);
                if(nodeptr->children[hashVal]==NULL)
                {    
                    nodeptr->children[hashVal] = NewNode();
                }
                nodeptr = nodeptr->children[hashVal]; 
                buffIndex++;
            }
            else
            {
                buffIndex++;
            }
        }
    }
        
    // finished - close file, free buffer and return
    free(lineBuff);
    fclose(inputFile);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictTrieSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    DeleteTrie(dictTrie);
    dictTrieSize = 0;
    return true;
}

/**********************************
*                                 *
*      Additional Functions       *
*                                 *
**********************************/

/**
 * Returns a new trienode with correctly-initialized values
 */
node* NewNode(void)
{
    node* newNodePtr;

    newNodePtr = (node*) malloc(sizeof(node));
    newNodePtr->isWord = false;
    for(int i=0; i<27; i++)
    {
        newNodePtr->children[i] = NULL; 
    }
    return newNodePtr;
}   

/**
 * Returns correct hash value from input chars a-z or '
 *   Does not check if input not allowed - error checking
 *   occurs in previously-defined functions above
 */
int GetHash(int strchar)
{
    strchar = tolower(strchar) - 'a';
    if(strchar == -58)
    {
        strchar = 26;
    }   
    return strchar;
}

/**
 * Recursive function that deletes all nodes in trie when 
 *   called at head pointer
 */
void DeleteTrie(node* trieNode)
{
    for(int i=0; i<27; i++)
    {
        if(trieNode->children[i]!=NULL)
        {
            DeleteTrie(trieNode->children[i]);
        }
    }
    free(trieNode);
    return;
}
