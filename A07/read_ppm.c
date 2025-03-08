/*----------------------------------------------
 * Author: Maryam
 * Date: 03/07/2025
 * Description: this programs reads the data from a PPM (Portable Pixmap) image file
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

/**
 * last time I did read ppm it did not work. i think it was because i did not consider the possiblities of an extra space, or other characetrs that could have been after each ppm variable like width/height. This time, i implemented a fucntion that should ignore those possibilities so that only the numbers can be read.
 * i also did more research and realized that i was focusing too much on the read and write ppm and the "error" message i was getting when i was making the files and i did not consider the fact that it will run with the testing files.
 */

void skip_extra(FILE *fp)
/**
 * skips extra chatacters in the ppm file
 * includes spaces( ), neewlines ('\n'), comments (#)
 * @param fp: pointer to the file being read
 */
{
  int c = fgetc(fp);                        // read first character
  while (c == '#' || c == ' ' || c == '\n') // Keep skipping spaces, newlines, comments
  {
    if (c == '#') // if there is a comment
    {
      while ((c = fgetc(fp)) != '\n' && c != EOF)
        ; // skip it till end of file
    }
    c = fgetc(fp); // read next char
  }
  ungetc(c, fp); // Put back last valid character
}

struct ppm_pixel *read_ppm(const char *filename, int *w, int *h)
/**
 * reads ppm image file and extracts pixel data
 * reads image in p6 ppm format and extracts its width, heightm and pixel data while ensuring other unnecessary characters, spaces, and comments are ignored
 * @param filename: name of file to be read (PPM)
 * @param w: pointer to store width of image
 * @param h: pointer to store height of image
 * @return dynamically allocated array of pixels, or NULL if errors occur
 */
{
  FILE *fp = fopen(filename, "rb"); // open file in binary mode for reading
  if (!fp)                          // check if file openin failed
  {
    printf("Error: could not open file %s \n", filename);
    return NULL;
  }

  char format[3];                     // buffer storing format identifier (P6 eg)
  if (fscanf(fp, "%2s", format) != 1) // read first two character of the file
  {
    printf("Error, unsupported file format\n");
    fclose(fp); // close file after returning
    return NULL;
  }

  skip_extra(fp);                     // called skip extra function to skip any extra characters before reading image dimensions
  if (fscanf(fp, "%d %d", w, h) != 2) // read height & width, of the image
  {
    printf("Error: invalid image dimensions\n");
    fclose(fp);
    return NULL;
  }

  int max;

  if (fscanf(fp, "%d", &max) != 1 || max != 255) // read max color value
  {
    printf("Error: unsupported color value\n");
    fclose(fp);
    return NULL;
  }

  fgetc(fp);

  struct ppm_pixel *pixels = (struct ppm_pixel *)malloc((*w) * (*h) * sizeof(struct ppm_pixel)); // allocate memory to store pixel data. r,g,b all get 3 bytes
  if (!pixels)                                                                                   // checking for memory allocation failure
  {
    printf("Error: memory allocation failed\n");
    fclose(fp);
    return NULL;
  }

  fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), fp); // read pixel data from file into allocated memory
  fclose(fp);                                               // closer after reading
  return pixels;                                            // return pointer to allocated pixel
}

struct ppm_pixel **read_ppm_2d(const char *filename, int *w, int *h)
{
  return NULL;
}

// eof: https://en.cppreference.com/w/c/io/fgetc
// https://www.geeksforgeeks.org/eof-and-feof-in-c/
// fgetc: https://www.tutorialspoint.com/c_standard_library/c_function_fgetc.htm
//https://cplusplus.com/forum/general/208835/ 