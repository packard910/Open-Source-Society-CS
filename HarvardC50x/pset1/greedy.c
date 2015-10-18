#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int numberofCents;
    int totalCoins = 0;
    
    do{
        printf("O hai! How much change is owed?\n"); 
        change = GetFloat();
    }
    while(change<0);
    
    numberofCents=round(change*100);
    
    while(numberofCents>=25){
        numberofCents=numberofCents-25;
        totalCoins++;
    }
    while(numberofCents>=10){
        numberofCents=numberofCents-10;
        totalCoins++;
    }
    while(numberofCents>=5){
        numberofCents=numberofCents-5;
        totalCoins++;
    }
    while(numberofCents>=1){
        numberofCents=numberofCents-1;
        totalCoins++;
    }
    
    printf("%i\n",totalCoins);
}   
