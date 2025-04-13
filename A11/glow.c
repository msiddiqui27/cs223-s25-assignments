/**
 * name: maryam
 * date: 04.12.2025
 * assignment description:  this file implements a single-threaded program that applies a glow effect to the image "earth-small.ppm". 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char *argv[])
/**
 * main
 */
{

  int width, height; // read og image from file and retrieve its width/height

  struct ppm_pixel *original = read_ppm("earth-small.ppm", &width, &height);

  int threshold = 200;       // brightness threshold as given
  int box_size = 25;         // box blur size
  int offset = box_size / 2; // radius of blur

  struct ppm_pixel *bright = malloc(width * height * sizeof(struct ppm_pixel)); // allocate memory for bright pixrl buffer
  for (int i = 0; i < width * height; i++)                                      // create bright image, filter pixels above threshold
  {
    int brightness = (original[i].red + original[i].green + original[i].blue) / 3;
    if (brightness >= threshold)
    {
      bright[i] = original[i]; // keep og pixels
    }
    else
    {
      bright[i].red = bright[i].green = bright[i].blue = 0; // dim pixels are black
    }
  }

  struct ppm_pixel *blurred = malloc(width * height * sizeof(struct ppm_pixel));

 
  for (int y = 0; y < height; y++) // apply box blur to bright image
  {
    for (int x = 0; x < width; x++)
    {
      int r = 0, g = 0, b = 0, count = 0;

      for (int row = -offset; row <= offset; row++) // iterate over blur box
      {
        for (int col = -offset; col <= offset; col++)
        {
          int new_r = y + row;
          int new_c = x + col;

          if (new_r >= 0 && new_r < height && new_c >= 0 && new_c < width) // not outside image
          {
            int idx = new_r * width + new_c;

            r += bright[idx].red;// add neighbor pixel color values
            g += bright[idx].green;
            b += bright[idx].blue;
            count++;
          }
        }
      }
      
      int i = y * width + x;// compute average of blur box because arverage smooths out the sharp differences in pixel values
      blurred[i].red = r / count;
      blurred[i].green = g / count;
      blurred[i].blue = b / count;
    }
  }

  struct ppm_pixel *glow = malloc(width * height * sizeof(struct ppm_pixel)); // allocate memory for final glow image
  for (int i = 0; i < width * height; i++)                                    // add blurred bright image to the og image
  {
    int red_sum = original[i].red + blurred[i].red;
    int green_sum = original[i].red + blurred[i].green;
    int blue_sum = original[i].blue + blurred[i].blue;

    if (red_sum > 255)// make sure each red value max is 225
    { 
      glow[i].red = 255;
    }
    else
    {
      glow[i].red = red_sum;
    }

    if (green_sum > 225)
    {
      glow[i].green = 255;
    }
    else
    {
      glow[i].green = green_sum;
    }
    if (blue_sum > 255)
    {
      glow[i].blue = 255;
    }
    else
    {
      glow[i].blue = blue_sum;
    }
  }

  write_ppm("glow.ppm", glow, width, height); // write result to output file
  free(original);                             // free all mallocs
  free(bright);
  free(blurred);
  free(glow);

  // printf("Output written to glow.ppm\n"); not needed, but was useful me to know when the process ended when i was running
  return 0;
}

// i was pretty confused with this assignment, so i was trying to find similar projects online to help me understand how to go about coding this
// some include: https://learn.microsoft.com/en-us/cpp/parallel/sample-multithread-c-program?view=msvc-170
//https://faculty.college.emory.edu/sites/weeks/graphics/mkppm.html
//https://www.scratchapixel.com/lessons/digital-imaging/simple-image-manipulations/reading-writing-images.html
//https://cboard.cprogramming.com/c-programming/162082-editing-image-ppm-format.html 
//none of these really ahd code/explanations i was looking for, but they gave me a general idea of what to expect