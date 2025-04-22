#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 32

int main()
{
    int boolean, num;
    printf("Boolean: ");
    scanf("%d", &boolean);
    printf("Number: ");
    scanf("%d", &num);

    char **adjectives = malloc(num * sizeof(char *));

    for (int i = 0; i < num; i++)
    {
        adjectives[i] = malloc(MAXSIZE * sizeof(char));
        printf("Adjective: ");
        scanf("%s", adjectives[i]);
    }

    printf("You are the most ");
    for (int i = num - 1; i >= 0; i--)
    {
        printf("%s", adjectives[i]);
        if (i > 1)
        {
            printf(", ");
        }
        else if (i == 1)
        {
            printf(", and ");
        }
    }

    printf(" person that I know and you know it's %s!\n", boolean ? "true" : "false"); 

    for (int i = 0; i < num; i++)
    {
        free(adjectives[i]);
    }
    free(adjectives);

    return 0;
}
