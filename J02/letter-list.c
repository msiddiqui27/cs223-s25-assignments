//Max and Maryam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct letter
{
  char letter;
  struct letter *next;
};

struct letter *insertFirst(struct letter *head, char letter)
{

  struct letter *newLetter = malloc(sizeof(struct letter));


  newLetter->letter = letter;

  newLetter->next = head;

  return newLetter;
}

void print(struct letter *head)
{

  struct letter *temp = head;


  int index = 0;


  while (temp)
  {
    printf("%c", temp->letter);
    temp = temp->next;
    index++;
  }
}

void clear(struct letter *head)
{

  struct letter *next;


  while (head)
  {
    next = head;
    head = head->next;
    free(next);
  }
}

int main()
{
  char word[32];

  char character;
  printf("Enter a word: ");
  scanf(" %s", word);

  printf("Enter a char to remove: ");
  scanf(" %c", &character);

  struct letter *head = NULL;

  for (int i = strlen(word); i >= 0; i--)
  {
    if (word[i] != character)
    {
      head = insertFirst(head, word[i]);
    }
  }

  print(head);
  printf("\n");

  clear(head);

  return 0;
}