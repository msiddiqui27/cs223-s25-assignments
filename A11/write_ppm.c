/*----------------------------------------------
 * Author: Maryam
 * Date: 03/07/2o25
 * Description:
 ---------------------------------------------*/
 #include "write_ppm.h"
 #include <stdio.h>
 #include <string.h>
 
 // implement *one* (but do not remove the other one)!
 
 void write_ppm(const char *filename, struct ppm_pixel *pixels, int w, int h)
 {
     /**
      * write pixel data to ppm image file in p6 format
      * @param filename: the name of the output ppm file
      * @param pixels: pointer to a 1d array of pixel data
      * @param w: width of image
      * @param h: height of image
      */
     FILE *fp = fopen(filename, "wb");
     if (!fp)
     {
         printf("eror: couldn't write file %s\n", filename);
         return; // return if file cant be found
     }
 
     fprintf(fp, "P6\n%d %d\n255\n", w, h);               // write ppm header with width, height, and max color value
     fwrite(pixels, sizeof(struct ppm_pixel), w * h, fp); // write pixel data to file in binary format
     fclose(fp);                                          // close file
 }
 
 void write_ppm_2d(const char *filename, struct ppm_pixel **pixels, int w, int h)
 {
 }
 