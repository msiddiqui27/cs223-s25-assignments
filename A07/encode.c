/*----------------------------------------------
 * Author: Maryam
 * Date: 03/07/2024
 * Description: program that reads in a PPM file (raw, or binary, format) and asks the user for a message to embed within it.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char **argv)
/**
 * main function that encodes a message into a ppm image
 * reads existing ppm image, takes user-input message and encoces it using the least significanrt bits of pixel data
 * modified image saved with "-encoded.ppm", added to its relevant filename
 */
{
  if (argc != 2) // check if correct number of arguments provided
  {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }

  int width, height;
  struct ppm_pixel *pixels = read_ppm(argv[1], &width, &height);
  if (!pixels)
  {
    printf("Error: count not read PPM file.\n");
    return 1;
  }
  printf("Reading %s with width %d and height %d\n", argv[1], width, height);
  int max_characters = (width * height * 3) / 8 - 1; // calculate maximum number of characters that be hidden in image. 8-1 so the last bit is used for the null terminator
  printf("Max number of characters in the image: %d\n", max_characters);

  char *message = (char *)malloc(max_characters + 1);
  if (!message)
  {
    printf("Error: Memory allocation failed\n");
    free(pixels);
    return 1;
  }
  printf("Enter a phrase: ");
  fgets(message, max_characters + 1, stdin);
  message[strcspn(message, "\n")] = '\0';

  int message_length = strlen(message);
  if (message_length >= max_characters) // message does not exceed message_length
  {
    message[max_characters - 1] = '\0'; // so the last index is null terminator
  }

  int bit_index = 0;
  for (int i = 0; i < width * height; i++) // encode message in least sig bits of pixel val
  {
    if (bit_index / 8 < message_length + 1)
    {
      pixels[i].red = (pixels[i].red & ~1) | ((message[bit_index / 8] >> (7 - (bit_index % 8))) & 1);
      bit_index++;
    }
    if (bit_index / 8 < message_length + 1)
    {
      pixels[i].blue = (pixels[i].blue & ~1) | ((message[bit_index / 8] >> (7 - (bit_index % 8))) & 1);
      bit_index++;
    }
  }
  char output[256]; // output filename "-encoded.ppm"
  snprintf(output, sizeof(output), "%s-encoded.ppm", argv[1]);

  printf("Writing file %s\n", output);
  write_ppm(output, pixels, width, height);
  free(pixels);
  return 0;
}
