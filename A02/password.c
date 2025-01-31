/**
 * Bad Password program for assignment 2.
 * this program asks the user for a word and creates a bad password from it, assuming all characters are lowercase. 
 * @author: Maryam Siddiqui
 * @date: 01/31/2025
 *
 */
#include <stdio.h>
#include <string.h>

int main(){
 char str[3040];
 printf("Enter a word: ");
 scanf("%s", str);

 int strLength = strlen(str);
  for (int i = 0; i < strLength; i++){
   if (str[i] == 'e'){
      str[i] = '3';
    }
   if (str[i] == 'l'){
      str[i] = '1';
    }
   if (str[i] == 'a'){
      str[i] = '@';
    }
  }

 printf("Your bad password is:%s \n ", str);
  return 0;
}
