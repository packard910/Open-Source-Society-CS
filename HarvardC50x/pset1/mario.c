#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    int i,j;

    do{
        printf("height: ");
        height = GetInt();      
    }
    while((height>23) || (height<1));
    
    for(i=0;i<height;i++)
    {
        for(j=0;j<height+1;j++)
        {
            if(j>height-i+1)
            {
                printf("#");
            }
            else printf(" ");
        }
        printf("\n");
    }
}
