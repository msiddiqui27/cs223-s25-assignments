/*----------------------------------------------
 * Author: Maryam
 * Date: 02/22/2025
 * Description:  reads in a PPM file and "glitches" it. The program should save the modified PPM in a new file with the suffix "-glitch"
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

void apply_glitch(struct ppm_pixel *pixels, int w, int h)
{
  srand(time(NULL));

  for (int i = 0; i < w * h; i++)
  {
    int shift = rand() % 2 + 1;
    pixels[i].red = (pixels[i].red << shift) | (pixels[i].red >> (8 - shift));
    pixels[i].green = (pixels[i].green << shift) | (pixels[i].green >> (8 - shift));
    pixels[i].blue = (pixels[i].blue << shift) | (pixels[i].blue >> (8 - shift));
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "Error: %s <input.ppm>\n", argv[0]);
    return -1;
  }
  int w, h;
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);
  if (!pixels)
  {
    fprintf(stderr, "Error: Failed to load PPM file %s\n", argv[1]);
    return 1;
  }
  printf("Reading %s wiht width %d and height %d\n", argv[1], w, h);

  apply_glitch(pixels, w, h);
  char base_filename[256];
  strcpy(base_filename, argv[1]);
  char *dot = strrchr(base_filename, '.'); 
  if (dot) *dot = '\0'; 

  char new_filename[256];

  if (strlen(base_filename) > 245) {  
    fprintf(stderr, "Error: Filename too long\n");
    free(pixels);
    return 1;
}
  write_ppm(new_filename, pixels, w, h);
  free(pixels);
  return 0;
}
