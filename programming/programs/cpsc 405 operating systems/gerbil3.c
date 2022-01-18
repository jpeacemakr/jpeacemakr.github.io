/*
Rhodium - highest value
Platinum
Gold
Ruthenium - lowest value
*/


#include <stdio.h>
#define GERBIL_CAN_CARRY 20

void found(int *rhodium, int *platinum, int *gold, int *ruthenium)
{
      int total = GERBIL_CAN_CARRY;
      int * metalarray[4] = {rhodium, platinum, gold, ruthenium}; 
      for(int i=0; i<4; i++)
     {
                if (*metalarray[i] > total) *metalarray[i] = total;
                total = total - *metalarray[i];
     }
}



int main() 
{
    int rhodium = 10, platinum = 5, gold = 4, ruthenium = 2;
    found(&rhodium, &platinum, &gold, &ruthenium);
    printf("rhodium: %d, platinum: %d, gold: %d, ruthenium: %d\n", rhodium, platinum, gold, ruthenium);
    rhodium = 15;
    platinum = 3;
    found(&rhodium, &platinum, &gold, &ruthenium);
    printf("rhodium: %d, platinum: %d, gold: %d, ruthenium: %d\n", rhodium, platinum, gold, ruthenium);
}