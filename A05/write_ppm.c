/*----------------------------------------------
 * Author: Maryam
 * Date: 02/22/2025
 * Description:  write a short test that reads in feep_raw.ppm and then writes it to a file test.ppm by calling your function. Then, read in test.ppm and print the contents. If it is working correctly, you will see the following pixel values.
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char *filename, struct ppm_pixel *pixels, int w, int h)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        fprintf(stderr, "error: cannot open file %s for writing\n", filename);
        return;
    }

    fprintf(file, "P6\n%d %d\n255\n", w, h);

    if(fwrite(pixels, sizeof(struct ppm_pixel), w * h, file)!=(size_t)(w * h)){
        fprintf(stderr, "error: failed to write pixel data\n");
        fclose(file);
        return;
    } 

    fclose(file);
}

void write_ppm_2d(const char *filename, struct ppm_pixel **pixels, int w, int h)
{
}
