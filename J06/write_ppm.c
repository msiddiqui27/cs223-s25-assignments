#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

void write_ppm(const char *filename, struct ppm_pixel *pixels, int w, int h)
{

    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("eror: couldn't write file %s\n", filename);
        return;
    }

    fprintf(fp, "P6\n%d %d\n255\n", w, h);
    fwrite(pixels, sizeof(struct ppm_pixel), w * h, fp);
    fclose(fp);
}

void write_ppm_2d(const char *filename, struct ppm_pixel **pxs, int w, int h)
{
}