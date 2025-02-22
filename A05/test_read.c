/*----------------------------------------------
 * Author:
 * Date:
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"


int main()
{
  int w, h;
  struct ppm_pixel *pixels = read_ppm("feep-raw.ppm", &w, &h);
  if (!pixels)
  {
    fprintf(stderr, "error: failed to load ppm file\n");
    return 1;
  }
  if (write_ppm("test.ppm", pixels, w, h) != 0) {
    fprintf(stderr, "error: failed to write test.ppm\n");
    free(pixels);
    return 1;
  }

  struct ppm_pixel* new_pixels = read_ppm("test.ppm", &w, &h);
  if (!new_pixels) {
      fprintf(stderr, "error: failed to load test.ppm\n");
      free(pixels);
      return 1;
  }

  // todo: print out the grid of pixels
  
   printf("Testing file test.ppm: %d %d\n", w, h);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = new_pixels[i * w + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

  free(pixels);
  free(new_pixels);
  return 0;
}
