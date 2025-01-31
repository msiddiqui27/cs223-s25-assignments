/**
 * Shift Cypher program for assignment 2.
 * this program asks the user for a word and then encodes it usinf a shift cypher(through ASCII). It is assumed all inputs are lowercase and do not contain special characers
 * @author: Maryam Siddiqui
 * @date: 01/31/2025
 * 
 */
#include <stdio.h>
#include <string.h>

int main() {
 char word[100];//declare character array to hold input word. max length is 100 characters
 int shift;//declare integer variable to store the shift value for the cypher

//user input section
 printf("Enter a word: \n");
 scanf("%s", word);
 printf("Enter a shift: \n");
 scanf("%d", &shift);

 char wordLength=strlen(word);//calculate the length of the word and store it in wordLength

 for (int i=0 ;i<wordLength;i++){//loop through each character of the word
  word[i]=(word[i]-'a'+shift)%26+'a';//apply shift cypher: convert character to its new value after shifting
  if(word[i]<'a'){//adjusting range
  word[i]+=26;//adjusting character range to stay within a and z by adding 26
  }
  
  }  
  printf("Your cypher is %s\n", word);
  return 0;
}
