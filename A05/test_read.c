/*----------------------------------------------
 * Author: Maryam
 * Date: 02/22/2025
 * Description: test file for reading, writing, and verifying ppm image
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main()
{
  int w, h;//variables sotring image width and height

  struct ppm_pixel *pixels = read_ppm("feep-raw.ppm", &w, &h);//read ppm file "feep-raw,ppm" into dynamiclly allocated pixel array
  if (!pixels)//check if file was loaded successfully
  {
    fprintf(stderr, "error: failed to load ppm file\n");
    return 1;
  }
  write_ppm("test.ppm", pixels, w, h);//write image to new file "test.ppm"
  struct ppm_pixel *new_pixels = read_ppm("test.ppm", &w, &h);//read newly written "test.pm" file back into memory

  if (!new_pixels)//check if file loaded successfullyhow
  {
    fprintf(stderr, "error: failed to write test.ppm\n");
    free(pixels);
    return 1;
  }
  if (!new_pixels)
  {
    fprintf(stderr, "error: failed to load test.ppm\n");
    free(pixels);
    return 1;
  }

  // todo: print out the grid of pixels

  for (int i = 0; i < h; i++)//loop through rows
  {
    for (int j = 0; j < w; j++)//loop through image columns
    {
      struct ppm_pixel pixel = new_pixels[i * w + j];//get pixel at (i,j)
      printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);//print rgb vals
    }
    printf("\n");
  }
//freeing memory
  free(pixels);
  free(new_pixels);
  return 0;
}
