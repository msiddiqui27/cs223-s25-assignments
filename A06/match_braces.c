/**
 * Name: Maryam
 * Date: 02/28/2025
 * Assignment overview: this program takes a c file as a command line argument and uses a stack to check for matched braces. if not all braces are matched, the program prints the line where a mis-matched brace occurs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
/**
 * represents a single node in the stack tracking the position of braces
 */
{
  int line;//line # of braces
  int column;//column # of brace
  struct Node *next; // points to the next node in the stack
};

struct Stack
/**
 * simple stack to track opening braces "{"
 */
{
  struct Node *top; // points to top node of stack
};

void push(struct Stack *stack, int line, int column)
/**
 * pushes new opening brace position on stack
 * @param stack: pointer to the stack
 * @param line: line number where "{" is found
 * @param column: columb where opening brace is found
 */
{
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (!newNode)
  {
    fprintf(stderr, "Memory allocation error\n");//checks for memory allocation failure
    exit(1);
  }
  newNode->line = line;
  newNode->column = column;
  newNode->next = stack->top;//points to previous top node
  stack->top = newNode;//update the stack's top pointer
}
int pop(struct Stack *stack, int *line, int *column)
/**
 * pops the opening brace positoin from stack
 * @param stack: pointer to stack
 * @param line:pointer to store the popped line number
 * @param colimn: pointer to store the popped column number
 * @return int returns 1 if item popped, 0 if not
 */
{
  if (stack->top == NULL)
  {
    return 0; // checks for empty stack
  }
  struct Node *temporary = stack->top;
  *line = temporary->line;//store popped line numner
  *column = temporary->column;
  stack->top = temporary->next;//move top pointer to next node
  free(temporary);//free popped node
  return 1;//successful pop of element
}

void clearStack(struct Stack *stack)
/**
 * clear stack by freeing allocated memory
 * @param stack: pointer to stack 
 */
{
  struct Node *curr = stack->top;
  while (curr)//traverse stack and free each node
  {
    struct Node *temporary = curr;
    curr = curr->next;
    free(temporary);
  }
  stack->top = NULL;//reset stack to empty state
}
void checkBraces(const char *filename)
/**
 * reads file and checks or matched/unmatched '{}' braces
 * function processes file line by line and uses a stack to track opening or closing braces potisions
 * matches braces are printed, and unmatched braces are reported
 * @param filename: name of the file to check
 */
{
  FILE *file = fopen(filename, "r");
  if (!file)//handle file opening failure
  {
    printf("Cannot open file: %s\n", filename);
    return;
  }
  printf("Opening file: %s\n", filename);

  struct Stack stack = {NULL};//initialize stack
  int line = 1, column = 0;//track line and column posiitons
  char buffer[260];//buffer to store each line of file

  while (fgets(buffer, sizeof(buffer), file))
  {
    column = 0;//reset column at start of each line

    for (int i = 0; buffer[i] != '\0'; i++)//process each character in line
    {
      column++;//increment column counter

      if (buffer[i] == '\n')//if a newline character is found
      {
        line++;//move to the next line
        column = 0;//reset column count
      }
      else if (buffer[i] == '{')
      {
        push(&stack, line, column);//push opening brace to its position onto stack if found
      }
      else if (buffer[i] == '}')
      {
        int openLine, openColumn;
        if (pop(&stack, &openLine, &openColumn))//try to match closing bracket with opening bracket
        {
          printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
                 openLine, openColumn, line, column);
        }
        else
        {
          printf("Unmatched brace on Line %d and Column %d\n", line, column);
        }//if match not found
      }
    }
    line++;//move to next line
  }

  while (stack.top)
  {
    int openLine, openColumn;
    pop(&stack, &openLine, &openColumn);
    printf("Unmatched brace on Line %d and Column %d\n", openLine, openColumn);
  }

  clearStack(&stack);//free memory allocated to stack nodes
  fclose(file);//close file
}
int main(int argc, char *argv[])
/**main function processing user input anc calls checkBraces
 * @param argc: number of command-line arguments
 * @param argv: list of command line arguments
 * @return int exit
 */
{
  if (argc != 2)//make sure there is a file provided
  {
    printf("usage: ./match_braces <filename>\n");
    return EXIT_FAILURE;
  }
  checkBraces(argv[1]);//process file
  return EXIT_SUCCESS;
}
