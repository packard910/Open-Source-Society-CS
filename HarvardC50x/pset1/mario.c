#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    int i,j;

    while(true)
    {
        printf("height: ");
        height = GetInt();
        if((height>23) || (height<1))
        {
            printf("Please input a positive integer no greater than 24\n");
        }
        else break;
    }
    for(i=1;i<height+1;i++)
    {
        for(j=1;j<height+2;j++)
        {
            if(j>height-i)
            {
                printf("#");
            }
            else printf(" ");
        }
        printf("\n");
    }
    
}
