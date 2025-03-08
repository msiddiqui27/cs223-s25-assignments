/*----------------------------------------------
 * Author: Maryam
 * Date: 03/07/2025
 * Description:  reads in a PPM file (raw, or binary, format) and then outputs any message that might be stored in the least significant bits of each color.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char **argv)
/**
 * main funciton to decode a hidden message from ppm image
 */
{
  if (argc != 2) // check if correct number of aguments provided
  {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }

  int width, height;
  struct ppm_pixel *pixels = read_ppm(argv[1], &width, &height); // read pixel data from ppm image

  if (pixels)
  {
    printf("Reading %s with width %d and height %d\n", argv[1], width, height);
    int max_characters = (width * height * 3) / 8; // maximum number of characters that can be stored in the image
    printf("Max number of characters in the image: %d\n", max_characters);

    char *message = (char *)malloc(max_characters + 1); // memory allocated for decoded message
    if (!message)
    {
      printf("Error: memory allocation failed for message\n");
      free(pixels);
      return 1;
    }
    message[max_characters] = '\0';

    int bit_index = 0;
    char curr = 0;

    for (int i = 0; i < width * height; i++) // get the message from the least significant bits of pixel values
    {
      curr |= (pixels[i].red & 1) << (7 - (bit_index % 8)); // for red
      bit_index++;

      if (bit_index % 8 == 0) // each ascii character is 8 bits, bit_index keeps track fo how many bits have been extracted
      {
        message[bit_index / 8 - 1] = curr; // 8-1: first character is complete
        if (curr == '\0')                  // Stop decoding at null terminator
          break;
        curr = 0;
      }

      curr |= (pixels[i].green & 1) << (7 - (bit_index % 8)); // for green
      bit_index++;
      if (bit_index % 8 == 0)
      {
        message[bit_index / 8 - 1] = curr;
        if (curr == '\0')
          break;
        curr = 0;
      }
      curr |= (pixels[i].blue & 1) << (7 - (bit_index % 8)); // for blue
      bit_index++;
      if (bit_index % 8 == 0)
      {
        message[bit_index / 8 - 1] = curr;
        if (curr == '\0')
          break;
        curr = 0;
      }
    }
    printf("%s\n", message); // print decoded message
    free(message);           // free allocated memory
    free(pixels);
  }
  return 0;
}
