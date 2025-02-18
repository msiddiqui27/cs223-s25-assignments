//Max and Maryam

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char string[32];
  printf("Enter a string: ");
  scanf("%31s", string);
  int len = strlen(string);
  char** grid = malloc(len * sizeof(char*));

  for (int i = 0; i < strlen(string); i++) {
    grid[i] = malloc(32 * sizeof(char));
  }

  strcpy(grid[0], string);
  strcpy(grid[strlen(string)-1], string);
  for( int i = 1; i < strlen(string)-1; i++){
    for( int j = 0; j < strlen(string); j++){
      if( i == j ){
        grid[i][i] = *(string+i);
      } else {
        grid[i][j] = ' ';
      }
    }
  }

  for( int i = 0; i < strlen(string); i++){
    for( int j = 0; j < strlen(string); j++){
      printf("%c ", grid[i][j]);
    }

    printf("\n");
  }

  for(int i = 0; i< strlen(string); i++){
    free(grid[i]);
  }
  free(grid);

  return 0;
}
