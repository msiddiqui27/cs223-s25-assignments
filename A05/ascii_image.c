/*----------------------------------------------
 * Author: Maryam
 * Date: 02/22/2025
 * Description:  takes a PPM image as a command line argument and displays it as ASCII Art.
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <stdlib.h>

char get_ascii_char(int intensity)
{
  if (intensity < 26)
    return '@';
  if (intensity < 51)
    return '#';
  if (intensity < 76)
    return '%';
  if (intensity < 101)
    return '*';
  if (intensity < 126)
    return 'o';
  if (intensity < 151)
    return ';';
  if (intensity < 176)
    return ':';
  if (intensity < 201)
    return ',';
  if (intensity < 226)
    return '.';
  return ' ';
}
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "error: %s failed\n", argv[0]);
    return 1;
  }

  int w, h;
  struct ppm_pixel *pixels = read_ppm(argv[1], &w, &h);
  if (!pixels)
  {
    fprintf(stderr, "Error: Failed to load PPM file %s\n", argv[1]);
    return 1;
  }

  printf("Reading %s with width %d and height %d\n", argv[1], w, h);

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      struct ppm_pixel pixel = pixels[i * w + j];
      int intensity = (pixel.red + pixel.green + pixel.blue) / 3;
      printf("%c", get_ascii_char(intensity));
    }
    printf("\n");
  }

  free(pixels);
  return 0;
}
