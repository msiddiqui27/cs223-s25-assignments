/*----------------------------------------------
 * Author: Maryam
 * Date: 03/07/2025
 * Description: this program reads in a single 64-bit unsigned integer (e.g. unsigned long) and outputs it as an 8x8 1bpp sprite.
 ---------------------------------------------*/
#include <stdio.h>

int main()
{
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);

  for (int i = 0; i < 8; i++) // i=row, looping through each bit from most to leas significant
  {
    for (int j = 0; j < 8; j++) // j=column, geting the bit position
    {
      unsigned long mask = 0x1ul << (63 - (i * 8 + j)); //
      if (img & mask)
      {
        printf("@"); // black pixel
      }
      else
      {
        printf(" "); // white pixel
      }
    }
    printf("\n");
  }
  return 0;
}
