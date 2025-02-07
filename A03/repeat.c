/*----------------------------------------------
 * Author: Maryam Siddiqui
 * Date: 02/06/2025 
 * Description: In this program. the user is asked for a string s and a integer n. The program then creates a new string that repeats s, n number of times. 
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int max_count=100000;

char *repeat(char *s, int n){
  /* Function to reepeat a given string 's', 'n' number of times
   * @param s: the input strint to be repeated
   * @param n: number of times to repeat the string
   * @return: new dynamically allocated string containing the repeated input string
   */
 int length= strlen(s); //length of input string s
 int expectedLength= length*n; //total length expected by the compiler to return 

 char *result= (char*)malloc((expectedLength+1) * sizeof(char));//dynamic allocation of memory for the new string. size expectedLength +1 to account for null terminator at end of string s
 if(result==NULL || n> max_count){
  printf("Cannot allocate new string. Exiting...\n");
    exit(1);
 }

 int position=0;//track position in the result string, but starting off at 0
 for (int i=0;i<n; i++){//loop repeats the string n times and stores it in result
  for(int j=0;j<length;j++){
    result[position]=s[j];
    position++;
  }
  }
  result[position]='\0';//null-terminate new string
  return result;//returns new string

}

int main() {
  /* main function to get user input and print the repeated string. 
   * asks user to enter a word and the number of repitions, calls the repeat function to generate repeated string and prints the result. 
   */
  char s[33];
  int n;
  printf("Enter a word: ");
  scanf("%s", s);

  printf("Enter a count: ");
  scanf("%d", &n);

  char *result = repeat(s, n);//get repeated string from repeat function and store in 'result'
  
  printf("Your repeated word is: %s\n", result);//
  
  free(result);//free dynamically allocated memeory for result
  return 0;
  
}
