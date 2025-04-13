/**
 * name: maryam
 * date: 04.12.2025
 * assignment description:  this file applies a glow effect using multiple threads. It should run much faster than your the threaded version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct ThreadArgs
{
  /**
   * struct for holding arguements passed to each thread
   */
  int id;
  int width;
  int height;
  int start_row;
  int end_row;
  int threshold;
  int blursize;
  struct ppm_pixel *original;
  struct ppm_pixel *output;
};

void *thread_glow(void *arg)
/**
 * thread function that applies the glow effect to a portion of the image
 * function executed by each thread
 * processes a horizontal slice of image and applies glow effect by checking brightness of each pixel, applying a boc blur to the ones bright enough, and adding the blur result to the original pixel
 * @param arg: pointer to threadargs struct
 * @return null
 */
{
  struct ThreadArgs *args = (struct ThreadArgs *)arg;
  int w = args->width;
  int h = args->height;
  int offset = args->blursize / 2; // how far offset form actual pixels when applying box blur

  for (int y = args->start_row; y < args->end_row; y++)
  {
    for (int x = 0; x < w; x++)
    {
      int index = y * w + x; // 1D index into image array
      struct ppm_pixel p = args->original[index];

      int brightness = (p.red + p.green + p.blue) / 3; // computes brightness as average of R, G, B
      if (brightness < args->threshold)
      {
        // copy unchanged pixel to output if brightness is below threshold
        args->output[index].red = p.red;
        args->output[index].green = p.green;
        args->output[index].blue = p.blue;
      }
      else
      {
        int r = 0, g = 0, b = 0, count = 0; // otherwise, apply blur by averaging nearby pixels

        for (int row = -offset; row <= offset; row++) // Box blur averaging
        {
          for (int column = -offset; column <= offset; column++)
          {
            int new_r = y + row;
            int new_c = x + column;
            if (new_r >= 0 && new_r < h && new_c >= 0 && new_c < w) // check bounds to avoid accessing outside image
            {
              int idx = new_r * w + new_c;
              r += args->original[idx].red;
              g += args->original[idx].green;
              b += args->original[idx].blue;
              count++;
            }
          }
        }
        struct ppm_pixel blurred; // Compute average of surrounding pixels/ results of box blur
        blurred.red = r / count;
        blurred.green = g / count;
        blurred.blue = b / count;

        int final_r = p.red + blurred.red; // add blurred color to original pixel to create glow effect
        int final_g = p.green + blurred.green;
        int final_b = p.blue + blurred.blue;

        if (final_r > 255) // make sure color values are vlid range until 255
          final_r = 255;
        if (final_g > 255)
          final_g = 255;
        if (final_b > 255)
          final_b = 255;

        args->output[index].red = final_r; // write resulrs to output image
        args->output[index].green = final_g;
        args->output[index].blue = final_b;
      }
    }
  }
  return NULL;//made the mistake of putting this in the loop at first, completely ruined the glow.ppm image and it took so long to realize it was this one. 
}

int main(int argc, char *argv[])
/**
 * main function
 * parses command line arguments, loads image, spwans threads that will processes different sections of the image, writes results
 */
{
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char *filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1)
  {
    switch (opt)
    {
    case 'N':
      N = atoi(optarg);
      break;
    case 't':
      threshold = atof(optarg);
      break;
    case 'b':
      blursize = atof(optarg);
      break;
    case 'f':
      filename = optarg;
      break;
    case '?':
      printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]);
      break;
    }
  }

  int width, height; // loading image from file
  struct ppm_pixel *image = read_ppm(filename, &width, &height);
  struct ppm_pixel *output = malloc(width * height * sizeof(struct ppm_pixel));

  pthread_t threads[N];
  struct ThreadArgs args[N];

  int rows_per_thread = height / N; // split image

  for (int i = 0; i < N; i++) // create threads and assigned them their portion of the image
  {
    args[i].id = i,
    args[i].width = width,
    args[i].height = height,
    args[i].start_row = i * rows_per_thread,
    args[i].end_row = (i + 1) * rows_per_thread,
    args[i].threshold = threshold,
    args[i].blursize = blursize,
    args[i].original = image,
    args[i].output = output;

    printf("Thread sub-image slice: rows (%d,%d)\n", args[i].start_row, args[i].end_row);
    pthread_create(&threads[i], NULL, thread_glow, &args[i]);
  }

  for (int i = 0; i < N; i++) // waiting for all threads to finish
  {
    pthread_join(threads[i], NULL);
  }

  write_ppm("glow.ppm", output, width, height); // writing final image result

  free(image); // freeing memory
  free(output);
  return 0;
}