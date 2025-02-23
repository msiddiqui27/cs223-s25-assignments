/*----------------------------------------------
 * Author: Maryam
 * Date: 02/21/2025
 * Description: this program implements a function, read_ppm(), that can read PPM files stored in binary format. This function should take a filename as input and return a 2D array of struct pixel
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"



struct ppm_pixel *read_ppm(const char *filename, int *w, int *h) {
    
    return NULL;
}

struct ppm_pixel **read_ppm_2d(const char *filename, int *w, int *h) {
        FILE *file = fopen(filename, "rb");
        if (!file) {
            perror("Error opening file");
            fprintf(stderr, "error: cannot open file %s\n", filename);
            return NULL;
        }
    
        char magic[3];
        if (!fgets(magic, sizeof(magic), file) || strcmp(magic, "P6") != 0) {
            fprintf(stderr, "invalid format for PPM, not P6\n");
            fclose(file);
            return NULL;
        }
    
        char line[256];
        do {
            if (fgets(line, sizeof(line), file) == NULL) {
                fprintf(stderr, "error: unexpected end of file\n");
                fclose(file);
                return NULL;
            }
        } while (line[0] == '#');
    
        if (sscanf(line, "%d %d", w, h) != 2) {
            fprintf(stderr, "Error: Failed to read width and height from PPM file\n");
            fclose(file);
            return NULL;
        }
    
        if (fgets(line, sizeof(line), file) == NULL) {
            fprintf(stderr, "error: unexpected end of file while reading maxval\n");
            fclose(file);
            return NULL;
        }
    
        int maxval;
        if (sscanf(line, "%d", &maxval) != 1) {
            fprintf(stderr, "error: failed to read maxval\n");
            fclose(file);
            return NULL;
        }
    
        struct ppm_pixel **pixels = malloc((*h) * sizeof(struct ppm_pixel *));
        if (!pixels) {
            fprintf(stderr, "error: memory allocation failed\n");
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
                fprintf(stderr, "error: failed to read pixel data\n");
                for (int j = 0; j < *h; j++) free(pixels[j]);
                free(pixels);
                fclose(file);
                return NULL;
            }
        }
    
        fclose(file);
        return pixels;
    }
