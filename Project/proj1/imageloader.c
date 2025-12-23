/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.

// readData should read an Image struct from a .ppm file
Image *readData(char *filename) 
{
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
	// For Image, the rows and cols attributes should store the dimensions of the image.
	// The attributes (R, G, B) for Color should respectively be the red, green, and blue values for the stored pixel.
	// The image attribute should be a list of Color*, where each Color* stores the color of a single pixel.
	char file_format[2];
	fscanf(file, "%s", file_format);
	printf("%s\n", file_format);

	int row, col;
	fscanf(file, "%d %d", &col, &row);
	printf("%d %d\n", col, row);

	int max_num;
	fscanf(file, "%d", &max_num);
	printf("%d\n", max_num);

	Image* image = (Image *) malloc(sizeof(Image));
	image->rows = row;
	image->cols = col;
	image->image = (Color **) malloc(image->rows * sizeof(Color *));
    for (int i = 0; i < image->rows; i++) {
        image->image[i] = (Color *) malloc(image->cols * sizeof(Color));  
    }
	
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			fscanf(file, "%hhu %hhu %hhu", &(image->image[i][j].R), &(image->image[i][j].G), &(image->image[i][j].B));
		}
	}
	fclose(file);

	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
/* requirements:
Each of the R, G and B values should be formatted to have 3 characters, with a space between them.
There should be three spaces between columns.
Do not have any extraneous whitespace characters at the end of the row.
All rows end with a newline character.
After your program exits, the UNIX prompt should start on a new line and not on the same line
*/
void writeData(Image *image)
{
    for(int i = 0; i < image->rows; i++){
        for(int j = 0; j < image->cols; j++){
			if(j < image->cols - 1)
            	printf("%3u %3u %3u   ", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
			else
				printf("%3u %3u %3u", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
        }
        printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{
	for (int i = 0; i < image->rows; i++) {
        free(image->image[i]);  
    }
	free(image->image);
	free(image);
}