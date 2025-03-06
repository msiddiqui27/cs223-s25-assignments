//Olivia and Maryam 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASK 0xff

int hex_to_int(const char *val)
{
  int value=0;
  int i = 2;

  while (val[i] != '\0')
  {
    if (val[i] >= '0' && val[i] <= '9')
    {
      value = (value << 4) | (val[i] - '0');
    }
    else if (val[i] >= 'A' && val[i] <= 'F')
    {
      value = (value << 4) | (val[i] - 'A' + 10);
    }
    else
    {
      printf("invalid number");
      exit(1);
    }
    i++;
  }

  return value;
}

int bin2int(char *val)
{
  int value=0;
  int i = 2;

  while (val[i] != '\0')
  {
    if (val[i] == '0' || val[i] == '1')
    {
      value = (value << 1) | (val[i] - '0');

    }
    else
    {
      printf("invalid number\n");
      exit(1);
    }
    i++;

  }
  return value;
}
int main(int argc, char **argv)
{

  if (argc != 2)
  {
    printf("Error: please enter a value");
    exit(1);
  }

  char *v = argv[1];

  if (argv[1][0] == '0')
  {
    if (argv[1][1] == 'b')
    {
      printf("%d\n", bin2int(argv[1])) ;
    }
    else if (argv[1][1] == 'x')
    {
      printf("%d\n", hex_to_int(argv[1]));
    }
    else
    {
      printf("Error: please enter a value\n");
      exit(1);
    }
  }


  return 0;
}
