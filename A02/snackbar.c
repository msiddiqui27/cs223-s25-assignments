/**
 * Snackbar program for Assignment 2
 * This program acts as a virtual vending machine/snackbar, asking the user to input how much money they have, and then what snack they want, out of three options. With the given information, the program either "gives" the user their desired snack if they can afford it and reduces the quanitity in its own system. If the user can't afford the snack, or asks for a snack outside of the range given, an error message will be produced.
 * @author: Maryam Siddiqui
 * @date: 01/31/2025
 *
 */
#include <stdio.h>

struct snack{
  /**
   * Keeps the struct snack infromation
   */
  char name[50];
  float cost;
  int quantity;
};

int main(){
  /**
   * main program logic of the snackbar program. list of snacks initialized here. Users are asked for their money budget, available snack options displayed, and then the user's choice is processed.
   * Based on the user's choice, the program determines if the user is able to afford the snack or not. If the user input a value out of the program's bounds, or doesn't have enough money, or asks for a snack that is out of stock, the program provides an error message.
   * if all conditions are met, the snack is "purchased" and the quantity is reduced in the program by 1.
   */
  int snackNum;
  float money;
  struct snack snacks[3] = {
    {"Coco Puffs", 1.50, 4},
    {"Chicken sandwich", 15.50, 6},
    {"Salted Caramel Brownie", 0.50, 0},
  };

   printf("Welcome to Steven Struct's Snack Bar.\n"); // welcome users
   printf("\nHow much money do you have?\n "); // ask users how much money they have
   scanf("%f", &money);

   for (int i = 0; i < 3; i++){ // display snack options
    printf("%d)%s\tcost: $%.2f\tquantity: %d\n", i, snacks[i].name, snacks[i].cost, snacks[i].quantity);
  }

    printf("\nWhat snack would you like to buy? [0,1,2]"); // get user's snack of choice
    scanf("%d", &snackNum);

  if (snackNum < 0 || snackNum >= 3){                                        // different output based on different conditions
    printf("Invalid choice. Try again\n"); // invalid snack choice
  }
  else if (snacks[snackNum].quantity == 0){
    printf("Sorry, we are out of %s.\n", snacks[snackNum].name); // out of stock item
  }
  else if (money < snacks[snackNum].cost){
    printf("You can't afford it!\n"); // not enough money
  }
  else {
    money -= snacks[snackNum].cost; // successful purchase: subtracts cose of choen snack from user's total money
    snacks[snackNum].quantity--; // decreased quantity of snack by 1;

    printf("You bought %s.\n", snacks[snackNum].name);
    printf("You have $%.2f left.\n", money);
  }
  return 0;
}
