/*----------------------------------------------
 * Author: Maryam
 * Date: 02/21/2025
 * Description: this program implements a function, read_ppm(), that can read PPM files stored in binary format. This function should take a filename as input and return a 2D array of struct pixel
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel *read_ppm(const char *filename, int *w, int *h) {
    struct ppm_pixel** pixels_2d = read_ppm_2d(filename, w, h);
    if (!pixels_2d) return NULL;

    struct ppm_pixel* pixels = malloc((*w) * (*h) * sizeof(struct ppm_pixel));
    if (!pixels) {
        fprintf(stderr, "Error: Memory allocation failed for flat array\n");
        return NULL;
    }

    for (int i = 0; i < *h; i++) {
        memcpy(pixels + (i * (*w)), pixels_2d[i], (*w) * sizeof(struct ppm_pixel));
        free(pixels_2d[i]);
    }
    free(pixels_2d);

    return pixels;
}

struct ppm_pixel **read_ppm_2d(const char *filename, int *w, int *h) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    char magic[3];
    if (!fgets(magic, sizeof(magic), file) || strcmp(magic, "P6") != 0) {
        fprintf(stderr, "Invalid format for PPM, not P6\n");
        fclose(file);
        return NULL;
    }

    char line[256];
    do {
        fgets(line, sizeof(line), file);
    } while (line[0] == '#');

    sscanf(line, "%d %d", w, h);

    fgets(line, sizeof(line), file);
    int maxval;
    sscanf(line, "%d", &maxval);

    if (maxval > 255) {
        fprintf(stderr, "Error: Max color value too high\n");
        fclose(file);
        return NULL;
    }

    struct ppm_pixel **pixels = malloc((*h) * sizeof(struct ppm_pixel *));
    if (!pixels) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *h; i++) {
        pixels[i] = malloc((*w) * sizeof(struct ppm_pixel));
        if (!pixels[i]) {
            fprintf(stderr, "Error: Memory allocation failed for row %d\n", i);
            for (int j = 0; j < i; j++) free(pixels[j]);
            free(pixels);
            fclose(file);
            return NULL;
        }
    }

    for (int i = 0; i < *h; i++) {
        if (fread(pixels[i], sizeof(struct ppm_pixel), (*w), file) != (size_t)(*w)) {
            fprintf(stderr, "Error: Incomplete pixel data read\n");
            for (int j = 0; j <= i; j++) free(pixels[j]);
            free(pixels);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return pixels;
}