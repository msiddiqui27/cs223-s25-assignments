/*----------------------------------------------
 * Author: Maryam Siddiqui
 * Date: 02/14/2025
 * Description: this program tests whether a given matrix is a magic square. A magic square is an N by N matrix where each row, column, and diagonal has the same sum, called the magic constant. ALl the magic_sqaure test files are given, located in the folder as "magic1.txt...magic4.txt". These txt files will be tested out in the program specifically. 
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
//everything was formatted using an extension, learned from the website about inddentations you linked in the first assignment. 


int is_magic(int **matrix, int N, int *magic_constant){
  /**
   * function to check if the given matrix is a magic square
   * checks if: all row sums are equal, all column sums are equal, if both diagonals um is the same value
   * @param **matrix: dynamically allocated 2d array representing the square matrix
   * @param N: size of the square matrix (NXN)
   * @param magic_constant: a pointer to store the computed magic constant if the matrix is a magic square
   * @return 1: if the matrix is a magic square, 0 otherwise
   */

  int sum, ref_sum;//variables to store sum calculations

  if (N == 1)//if matrix is 1x1, it is a magic square
  {
    *magic_constant = matrix[0][0];
    return 1;//return true
  }

  ref_sum = 0;//refernece sum using the first row
  for (int i = 0; i < N; i++)
  {
    ref_sum += matrix[0][i];
  }

  for (int i = 1; i < N; i++)//check if all row sums match reference sum. start from second row
  {
    sum = 0;//reset sum for each row
    for (int j = 0; j < N; j++)
    {
      sum += matrix[i][j];
    }
    if (sum != ref_sum)//if sum different, not a magic square aand returns false
    {
      return 0;
    }
  }

  for (int j = 0; j < N; j++)//check if all column sums match reference. same steps
  {
    sum = 0;
    for (int i = 0; i < N; i++)
    {
      sum += matrix[i][j];
    }
    if (sum != ref_sum)
    {
      return 0;
    }
  }

  sum = 0;

  for (int i = 0; i < N; i++)//check main diagonal sum, top left to bottom right. 
  {
    sum += matrix[i][i];
  }
  if (sum != ref_sum)
  {
    return 0;
  }

  sum = 0;//check secondaery diagonal sum, top right to bottom left. 
  for (int i = 0; i < N; i++)
  {
    sum += matrix[i][N - i - 1];
  }
  if (sum != ref_sum)
  {
    return 0;
  }
  *magic_constant = ref_sum;//once all conditions are met, magic constant is set and returns true. 
  return 1;//return true
}

int main(){
  /**
   * main function to read input, process matrix, and determine if it is magic square
   * reads NxN matrix, allocates dynamic memory for the matrix, reads and prints the matrix, calls "is_magic()" to check if the matrix is a magic square, frees allocated memory
    */

  int N, M;// variables to store the matrix dimensions 

  if (scanf("%d %d", &N, &M) != 2 || N != M)//read matrix dimensions from user
  {
    printf("Matrix must be a square!\n");
    exit(1);//exit program if input is invalid
  }

  int **matrix = (int **)malloc(N * sizeof(int *));//dynamicallu allocate memeory for the matrix

  if (matrix == NULL)//check if memory allocation was succesful
  {
    printf("Memory allocation failed.\n");
    exit(1);
  }

  for (int i = 0; i < N; i++)//allocate memory for each row
  {
    matrix[i] = (int *)malloc(N * sizeof(int));
    if (matrix[i] == NULL)
    {
      printf("Memory allocation failed.\n");
      exit(1);
    }
  }

  for (int i = 0; i < N; i++)//read the matrix elements from user input
  {
    for (int j = 0; j < N; j++)
    {
      if (scanf(" %d", &matrix[i][j]) != 1)
      {
        printf("Invalid matrix input.\n");
        exit(1);
      }
    }
  }

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d ", matrix[i][j]);//print each element of the matrix
    }
    printf("\n");
  }

  int magic_constant;//check if the matrix is a magic square
  if (is_magic(matrix, N, &magic_constant))
  {
    printf("M is a magic square (magic constant = %d)\n", magic_constant);
  }
  else
  {
    printf("M is NOT a magic square!\n");
  }

  for (int i = 0; i < N; i++)//free allocated memory, so no memory leaks
  {
    free(matrix[i]);
  }

  free(matrix);

  return 0;
}
