#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

void skip_extra(FILE *fp)
/**
 * skips extra chatacters in the ppm file
 * includes spaces( ), neewlines ('\n'), comments (#)
 * @param fp: pointer to the file being read
 */
{
  int c = fgetc(fp);
  while (c == '#' || c == ' ' || c == '\n')
  {
    if (c == '#')
    {
      while ((c = fgetc(fp)) != '\n' && c != EOF)
        ;
    }
    c = fgetc(fp);
  }
  ungetc(c, fp);
}

struct ppm_pixel *read_ppm(const char *filename, int *w, int *h)
{
  FILE *fp = fopen(filename, "rb");
  if (!fp)
  {
    printf("Error: could not open file %s \n", filename);
    return NULL;
  }

  char format[3];
  if (fscanf(fp, "%2s", format) != 1)
  {
    printf("Error, unsupported file format\n");
    fclose(fp);
    return NULL;
  }

  skip_extra(fp);
  if (fscanf(fp, "%d %d", w, h) != 2)
  {
    printf("Error: invalid image dimensions\n");
    fclose(fp);
    return NULL;
  }

  int max;

  if (fscanf(fp, "%d", &max) != 1 || max != 255)
  {
    printf("Error: unsupported color value\n");
    fclose(fp);
    return NULL;
  }

  fgetc(fp);

  struct ppm_pixel *pixels = (struct ppm_pixel *)malloc((*w) * (*h) * sizeof(struct ppm_pixel));
  if (!pixels)
  {
    printf("Error: memory allocation failed\n");
    fclose(fp);
    return NULL;
  }

  fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), fp);
  fclose(fp);
  return pixels;
  return NULL;
}

struct ppm_pixel **read_ppm_2d(const char *filename, int *w, int *h)
{

  return NULL;
}
