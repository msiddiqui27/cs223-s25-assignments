/***************************************************
 * mathgame.c
 * Author: Maryam Siddiqui
 * Implements a math game where the user is given random addition questions based on how many times the user wants to play the math game
 */

#include <stdio.h>
#include <stdlib.h>//need this for using rand()

int main() {
printf("Welcome to Math Game!\n");
printf("How many rounds do you want to play? ");
  int questionNum;
  scanf("%d", &questionNum);

int correct=0;

for(int i=0; i<questionNum;++i){
  int value1=rand()% 9+1;// random number between 0 and 9. from my understanding, if i did %10, then the numbers generated would be between 0 and 9. Hence, I did %9 so that the numbers generated are between 0 and 8, and then shift the range by 1, so add 1. 
  int value2=rand()% 9+1;
  int question=value1+value2;//define the question
  printf("%d + %d = ?\n", value1, value2); //ask the question based on the random numbers generated
  int answer;//initialize the answer so that i can put it in the if condition
  scanf("%d", &answer); //get the user's answer
  

    if(answer==question){ //check if the answer is correct or not and display the next message
    correct++;
    printf("Correct!\n");}
    else {

    printf("Incorrect :(\n");
}
}
printf("You answered %d/%d correctly.\n", correct, questionNum);//print the number of correct answers out of the total number of questions asked 
return 0;
}

