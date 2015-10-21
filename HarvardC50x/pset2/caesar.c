#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc,string argv[])
{
    if(argc!=2)
    {
        return 1;
    }
    
    int key = atoi(argv[1]);
    string message = GetString();
    string coded = message;
    
    for(int i=0,n=strlen(message);i<n;i++)
    {   
        if(isupper(message[i]))
        {
            coded[i] = (char)(((message[i]-'A'+key)%26)+'A');
        }
        else if(islower(message[i]))
        {
            coded[i] = (char)(((message[i]-'a'+key)%26)+'a');
        }
    }
    
    printf("%s\n",coded);   
    return 0;
}
