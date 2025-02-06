#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
printf("Enter digits:");
char* input = malloc(sizeof(char) * 32);
scanf("%s", input);
int size = strlen(input);

int* arr = malloc(sizeof(int)* 10);
memset(arr, 0, sizeof(int) * 10);


for (int i = 0; i < size; i++) {
   if (input[i] >= '0' && input[i] <= '9') {
         arr[input[i] - '0']++;
   }
}

for (int i = 0; i < 10; i++) {
   for (int j = 0; j < arr[i]; j++) {
      printf("%d", i);
   }
}


free(input);
free(arr);
   return 0;
}
