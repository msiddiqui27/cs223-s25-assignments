#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
printf("Welcome to the Price is Right");
printf("Enter a guess to win a luxurious dishwasher: ");
int val;
scanf("%d", &val);

   srand(time(NULL)); 

    int min_price = 3000;
    int max_price = 5000;

   int aiGuess1=rand()%(max_price-min_price+1)+min_price;
   int aiGuess2=rand()%(max_price-min_price+1)+min_price;

   int dishwaherPrice=rand()%(max_price-min_price+1)+min_price;
   
   printf("AI Contestant Guess 1: %d\n", aiGuess1);
    printf("AI Contestant Guess 2: %d\n", aiGuess2);
    printf("Dishwasher Cost: %d\n", dishwaherPrice);

    int winner = -1; 
    int closest = -1; 

    if (val <= dishwaherPrice && val > closest) {
        closest = val;
        winner = 0;
    }


    if (aiGuess1 <= dishwaherPrice && aiGuess2 > closest) {
        closest = aiGuess1;
        winner = 1;
    }

    if (aiGuess2 <= dishwaherPrice && aiGuess2 > closest) {
        closest = aiGuess2;
        winner = 2;
    }


    if (winner == 0) {
        printf("Congratulations! You win!\n");
    } else if (winner == 1) {
        printf("AI Contestant 1 wins!\n");
    } else if (winner == 2) {
        printf("AI Contestant 2 wins!\n");
    } else {
        printf("Sorry, no one wins!\n");
    }


   return 0;
}

