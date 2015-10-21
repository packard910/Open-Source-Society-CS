/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int minIndex = 0;
    int maxIndex = n;
    int checkIndex;
    int currValue;
   
    if(n<0)
    {
        return false;
    }
    
    while(true)
    {
        checkIndex = (maxIndex-minIndex)/2 + minIndex;
        currValue = values[checkIndex];
        
        if(value==currValue)
        {
            return true;
        }
        else if(value < currValue)
        {
            maxIndex = checkIndex;
        }
        else if(value > currValue)
        {
            minIndex = checkIndex;
        }
        
        if(maxIndex-minIndex==1)
        {
            return false;
        }
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int madeSwitch = 0;
    int tempVal;
    
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(values[j]>values[j+1])
            {
                madeSwitch=1;
                tempVal=values[j+1];
                values[j+1]=values[j];
                values[j]=tempVal;
            }
        }
         
        if(madeSwitch==0)
        {
            return;
        }
        madeSwitch = 0;
    }
    return;
}
