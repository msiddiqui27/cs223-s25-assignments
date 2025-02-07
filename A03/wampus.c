/*----------------------------------------------
 * Author: Maryam Siddiqui
 * Date: 02/07/2025
 * Description: this program randomly places a Wampus within a NxM grid. Then, it fills in the remaining cells with their distance from the Wampus (using the Manhattan distance)
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Grid{
  /*Struct function for Grid
  *@int **cells: pointer to 2d array
  *@int rows: number of rows in grid
  *@int cols: number oc columns in grid
  *@return pointer to created grid
  */
   int **cells;//pointer to 2d array, as shown in chapter 2.5 of book
    int rows;
    int cols;
} ;

struct Grid* create_grid(int rows, int cols){
  /*Create function to new grid
  *@param int rows: number of rows in grid
  *@param int cols: number of columns in grid
  */
  struct Grid *grid=malloc(sizeof(struct Grid));//allocate memory for Grid struct
  if(grid==NULL){//check if allocation was successful ot not
     printf("Memory allocation failed...\n");
     exit(1);
  }

  grid->rows=rows;//special operator -> found in 2.7 of book for dereferencing struct and accessing one of its field values
  grid->cols=cols;

  grid->cells=malloc(rows * sizeof(int *));//allocate memory for rows in grid
  if (grid->cells == NULL) {
    printf("Memory allocation failed...\n");
    free(grid);
    exit(1);  
}
  for (int i = 0; i < rows; i++) {
        grid->cells[i] = malloc(cols * sizeof(int));//allocate memory for each individual row
        if (grid->cells[i] == NULL) {//check if row allocation passed
          printf("Memory allocation failed...\n");
          for (int j = 0; j < i; j++) {
            free(grid->cells[j]);//free previously allocated memory
          }
          free(grid->cells);
          free(grid);
          exit(1);//exit if allocation fails
        }
      }
    return grid;//return pointer to created grid

}

void free_grid(struct Grid *grid){
  /*function to free allocated memory for grid
  *@param grid: Pointer to a Grid struct that represents the NxM grid.
  */

  for(int i=0; i<grid->rows;i++){
    free(grid->cells[i]);//free each row
  }
  free(grid->cells);//free array of row pointers
  free(grid);//free grid struct
}

int manhattan_dist(int x1, int y1, int x2, int y2) {
  /*function to calculate Manhattan distance between two points
  *@param x1: The x-coordinate of the first point.
  *@param y1: The y-coordinate of the first point.
  *@param x2: The x-coordinate of the second point.
  *@param y2: The y-coordinate of the second point.
  *@return: The Manhattan distance between the two points.
  */
    return abs(x1 - x2) + abs(y1 - y2);
}

void generate_wampus(struct Grid *grid){
  /*
  *function to generate random wampus in grid and calculate the manhattan distance
  *@param grid: Pointer to a Grid struct that represents the NxM grid.
*/
  srand(time(NULL));//random number generator is initialized

  int wampus_row=rand() % grid->rows;//randomly generates the row position of the wampus
  int wampus_column=rand() % grid->cols;//randomly generates the position of the wampus

  for (int i=0; i<grid->rows; i++){//randomly generate row position of wampus
    for(int j=0; j<grid->cols; j++){//randomly generate column position of wampus
      if(i==wampus_row && j== wampus_column){
        printf("W ");
      }else{
         grid->cells[i][j] = manhattan_dist(i,j, wampus_row, wampus_column);//calculate distance
           printf("%d ", grid->cells[i][j]);//print the distance
      }
    }
      printf("\n");
  }
}

int main() {
  /*Main function of the program. 
  *prompts user foe the number of rows and columns, creates grid, generates the wampus, prints the grid. 
  */
  int rows, cols;

  printf("Number of rows: ");
  scanf("%d", &rows);//get the number of rows from the user

  printf("Number of columns: ");
  scanf("%d", &cols);//get the number of columbs from the user

  struct Grid *grid=create_grid(rows, cols);//create grid based on user input
  generate_wampus(grid);//generate wampus and print grid with distances

  free_grid(grid);//free allocated memory for grid

  return 0;
}

//i didn't fully understand what a wampus is and how to implement it, so i relied heavily on different websites to teach me how to even attempt the 2d arrays and the "manhattan  distance"
//https://www.datacamp.com/tutorial/manhattan-distance
//https://github.com/Kumar-laxmi/Algorithms/blob/main/C/Maths/Manhattan_distance.c
//https://beginnersbook.com/2014/01/2d-arrays-in-c-example/
//https://www.geeksforgeeks.org/minimum-number-of-integers-required-to-fill-the-nxm-grid/?ref=header_outind
