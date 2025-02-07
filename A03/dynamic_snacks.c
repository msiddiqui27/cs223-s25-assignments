/*----------------------------------------------
 * Author: Maryam Siddiqui
 * Date: 02/06/2025
 * Description: this program allows uses to add snacks to a snackbar
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Snack{
  /*define struct for all the variables being consdidered
  *@char name[50]= snack name
  *@float cost= snack cost
  @int quant= snack quantity
  */
  char name[50];
  float cost;
  int quant;
};

void add(struct Snack *snacks, int num_snacks){
  /*function to add snacks to the list*/
  for(int i=0;i< num_snacks;i++){
      printf("Enter a name: " );
      scanf("%s", snacks[i].name);//read snack name

      printf("Enter a cost: ");
      scanf("%f", &snacks[i].cost);//read snack cost

      printf("Enter a quanitity: ");
      scanf("%d", &snacks[i].quant);//read snack quantity
    }
  }

void print_snacks(struct Snack *snacks, int num_snacks){
  /*function to print the snack list*/
  printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");//2 \n to follow the example output provided
    for (int i = 0; i < num_snacks; i++) {
        printf("%d) %-20s cost: $%.2f\tquantity: %d\n",//saw %-20s on 2.8 of book to format the string based on theh example code
               i, snacks[i].name, snacks[i].cost, snacks[i].quant);
    }
}

int main() {
  /*main function to use malloc and free and get the output*/
    int num_snacks;

    printf("Enter a number of snacks: ");
    scanf("%d", &num_snacks);//read # of snacks from the user

    struct Snack *snacks = (struct Snack *)malloc(num_snacks * sizeof(struct Snack));//dynamically allocate memory for the snacks
    if (snacks == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;//exit if memory allocation fails
    }

    add(snacks, num_snacks);//call to add function to add snacks to the vending machine
    print_snacks(snacks, num_snacks);//call to print snacks function to print the output

    free(snacks);//free dynamically allocated memory
    return 0;
}
