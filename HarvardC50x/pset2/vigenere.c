#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int GetKeyVal(char);
int VEncrypt(char,int);

int main(int argc,string argv[])
{
    if(argc!=2)
    {
        return 1;
    }
    
    string key = argv[1];
    int keyLength = strlen(key);
    int keyVal;
    string message = GetString();
    int currKeyIndex = 0;
    
    for(int i=0,n=strlen(message);i<n;i++)
    {   
        if(isalpha(message[i]))
        {
            keyVal = GetKeyVal(key[currKeyIndex]);
            currKeyIndex=(currKeyIndex+1)%keyLength;
            printf("%c",VEncrypt(message[i],keyVal));
        }
        else 
        {
            printf("%c",message[i]);
        }
    }
    
    printf("\n");
    return 0;  
}

int GetKeyVal(char keyChar)
{
    int keyVal;
    
    if(isupper(keyChar))
    {
        keyVal = keyChar-'A';
        return keyVal;
    }
    else if(islower(keyChar))
    {
        keyVal = keyChar-'a';
        return keyVal;
    }
    else return 0;
}

int VEncrypt(char messChar,int keyVal)
{
    if(isupper(messChar))
    {
        return (((messChar-'A'+keyVal)%26)+'A');   
    }
    else 
    {
        return (((messChar-'a'+keyVal)%26)+'a');   
    }
}
