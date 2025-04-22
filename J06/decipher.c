#include <stdio.h>
#include <stdlib.h>

//not too sure about this one. it keeps giving me the same output so i cant even check if it is correct
char decode(char c)
{
    return c >> 1 & 0x7F;
}

int main()
{
    FILE *fp = fopen("message", "r");
    char c = fgetc(fp);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(fp);
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(decode(ch));
        fclose(fp);

        return 0;
    }
}
