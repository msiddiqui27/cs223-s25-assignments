#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char string[32];
  printf("Enter a string: ");
  scanf("%s", string);

  char** grid = malloc(32 * sizeof(char*));

  for (int i = 0; i < strlen(string); i++) {
    grid[i] = malloc(32 * sizeof(char));
  }

  grid[0] = string;
  grid[strlen(string)-1] = string;
  for( int i = 1; i < strlen(string)-1; i++){
    for( int j = 0; j < strlen(string); j++){
      if( i == j ){
        grid[i][i] = *(string+i);
      } else {
        strcpy(&grid[i][j], " ");
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
