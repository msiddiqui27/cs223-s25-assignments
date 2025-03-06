// Olivia and Maryam

#include <stdio.h>
#include <stdlib.h>

#define MASK 0x80000000 // 32 bits

#define hexMASK 0xF0000000 // last 4 bits converted to hex

void binVal(int num)
{
  printf("0b ");
  for (int i = 0; i < 8; i++)
  {
    for (int i = 0; i < 4; i++)
    {
      if ((MASK & num) == MASK)
      {
        printf("1");
      }
      else
      {
        printf("0");
      }

      num = num << 1;
    }
    printf(" ");
  }
  printf("\n");
}

void bitVal(int num)
{
  printf("0x ");
  unsigned int temp;
  for (int i = 0; i < 4; i++)
  {
    for (int i = 0; i < 2; i++)
    {
      temp = hexMASK & num;
      temp = temp >> 28;

      if (temp < 10)
      {
        printf("%d", temp);
      }
      else
      {
        printf("%c", 'A' + (temp - 10));
      }
      num = num << 4;
    }
    printf(" ");
  }
  printf("\n");
}

int main(int argc, char **argv)
{

  if (argc == 1)
  {
    printf("Error: please enter a value");
    exit(1);
  }

  int v = atoi(argv[1]);

  bitVal(v);
  binVal(v);

  return 0;
}
