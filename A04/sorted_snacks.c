/*----------------------------------------------
 * Author: Maryam Siddiqui
 * Date: 02/14/2025
 * Description: this program allows a user to add snacks ot the snackbar and displays them in alphabetical order. This program has featues as last week's snackbar, but uses a linked list to store the snacks instad of an array.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Snack
{                     // initially was just struct Snack but it was not working so I am implementing typdef from ch2.9
  char name[50];      // stores name of snack
  float cost;         // stores cost of snack
  int quantity;       // stores quantity of snack
  struct Snack *next; // pointer to the next snack in the linked list
} Snack;

void insert_first(Snack **head, char *name, float cost, int quantity)
{
  /**
   * insert a new snack at the beginnign of the linked list
   * @param head: pointer to the head of the list
   * @param name: name of snack
   * @param cost: cost of snack
   * @param quantity: quantity of snack
   */
  Snack *new_snack = (Snack *)malloc(sizeof(Snack)); // allocate memory for the new snack node
  if (!new_snack)
  {
    printf("Memory allocation failed\n");
    exit(1); // exit program if allocation fails
  }
  strcpy(new_snack->name, name); // copy values to new node
  new_snack->cost = cost;
  new_snack->quantity = quantity;
  new_snack->next = *head; // insert at the beginning

  *head = new_snack; // update head pointer;
}

void printList(Snack *head)
{
  /**
   * print all snacks in linked list
   * @param head: pointer to the head of the list
   */
  printf("\nWelcome to Sorted Sally's Snack Bar\n\n");

  Snack *curr = head; // pointer to traverse ist
  int index = 0;      // index counter for display

  while (curr)
  {
    printf("%d) %-20s cost:$%.2f    quantity:%d\n", index, curr->name, curr->cost, curr->quantity);
    curr = curr->next; // moce to next snack
    index++;
  }
  printf("\n"); // print new line for better formatting
}

void clear(Snack **head)
{
  /**free all ememory allocated for the linked lsit
   * @param head: pointer to the head of the list
   */
  Snack *curr = *head;//pointer to traverse list
  Snack *next;

  while (curr)//free each node
  {
    next = curr->next;
    free(curr);//free memory allocated to current node
    curr = next;
  }
  *head = NULL; // head is set to NULL after freeing
}

void sortName(Snack **head)
{
  /**
   * sort linked list by name alphabetically
   * @param head: pointer to head of list
   */
  if (!(*head) || !((*head)->next))
  {
    return; // since it is void
  }
  Snack *i, *j;
  char temp_name[50];
  float temp_cost;
  int temp_quantity;

  for (i = *head; i != NULL; i = i->next)//doing a bubble sort to implement linked list
  {
    for (j = i->next; j != NULL; j = j->next)
    {
      if (strcmp(i->name, j->name) > 0)
      { // using the string compare to ensure the list is sorted in ascending order since it will return negative if str1 is before str2 and positive if str1 is after str2
        strcpy(temp_name, i->name);
        strcpy(i->name, j->name);
        strcpy(j->name, temp_name);//swap snack data

        temp_cost = i->cost;
        i->cost = j->cost;
        j->cost = temp_cost;

        temp_quantity = i->quantity;
        i->quantity = j->quantity;
        j->quantity = temp_quantity;
      }
    }
  }
}

void sortCost(Snack **head)
{
  /**
   * sorts linked list by cost in ascending order
   * @param head: pointer to head of list
   */
  if (!(*head) || !((*head)->next))
  {
    return;
  }

  Snack *i, *j;
  char temp_name[50];
  float temp_cost;
  int temp_quantity;

  for (i = *head; i != NULL; i = i->next)
  {
    for (j = i->next; j != NULL; j = j->next)
    {
      if (i->cost > j->cost)
      { // Swap if not in order
        strcpy(temp_name, i->name);
        strcpy(i->name, j->name);
        strcpy(j->name, temp_name);

        temp_cost = i->cost;
        i->cost = j->cost;
        j->cost = temp_cost;

        temp_quantity = i->quantity;
        i->quantity = j->quantity;
        j->quantity = temp_quantity;
      }
    }
  }
}

void sortQuantity(Snack **head)
{
  if (!(*head) || !((*head)->next))
  {
    return;
  }
  Snack *i, *j;
  char temp_name[50];
  float temp_cost;
  int temp_quantity;

  for (i = *head; i != NULL; i = i->next)
  {
    for (j = i->next; j != NULL; j = j->next)
    {
      if (i->quantity > j->quantity)
      { // swap if not in order
        strcpy(temp_name, i->name);
        strcpy(i->name, j->name);
        strcpy(j->name, temp_name);

        temp_cost = i->cost;
        i->cost = j->cost;
        j->cost = temp_cost;

        temp_quantity = i->quantity;
        i->quantity = j->quantity;
        j->quantity = temp_quantity;
      }
    }
  }
}

int main()
{
  /**
   * main function to run snackbar program
   */
  Snack *head = NULL;

  int num_snacks;
  printf("Enter a number of snacks: ");
  scanf("%d", &num_snacks);
  getchar(); // reads the value and returns the ascii value of the cahracter that is read.  also foudn this in chapter 2.8

  for (int i = 0; i < num_snacks; i++)
  {
    char name[50];
    float cost;
    int quant;
    printf("Enter a name: ");
    fgets(name, sizeof(name), stdin); // found fgets on chapter 2.6 for reading and writing individual characters or strings to file streams.
    for (int i = 0; i < sizeof(name); i++)
    {
      if (name[i] == '\n')
      {
        name[i] = '\0'; // replace newline with null terminator
        break;          // stop after replacing
      }
    }
    printf("Enter a cost: ");
    scanf("%f", &cost);
    getchar();

    printf("Enter a quantity: ");
    scanf("%d", &quant);
    getchar();

    insert_first(&head, name, cost, quant);
  }

  sortName(&head); // sorting before printgng
  printList(head);
  clear(&head); // freeing memory

  return 0;
}
