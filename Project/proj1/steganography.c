/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	uint8_t LSB = image->image[row][col].B & 0x01;
	Color* new_color = (Color*) malloc(sizeof(Color));
	
	if(LSB == 1){
		new_color->R = (uint8_t)255;
		new_color->G = (uint8_t)255;
		new_color->B = (uint8_t)255;
	}
	if(LSB == 0){
		new_color->R = (uint8_t)0;
		new_color->G = (uint8_t)0;
		new_color->B = (uint8_t)0;
	}

	return new_color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* new_image = (Image*)malloc(sizeof(Image));
	new_image->rows = image->rows;
	new_image->cols = image->cols;

	new_image->image = (Color**)malloc(new_image->rows*sizeof(Color*));
	for(int i = 0; i < new_image->rows; i++){
		new_image->image[i] = (Color*)malloc(new_image->cols*sizeof(Color));
	}
	for(int i = 0; i < new_image->rows; i++){
		for(int j = 0; j < new_image->cols; j++){
			Color* new_color = evaluateOnePixel(image, i, j);
			new_image->image[i][j] = *new_color;
			free(new_color);
		}
	}
	return new_image;
}
void processCLI(int argc, char **argv, char **filename) 
{
	if (argc != 2) {
		printf("usage: %s filename\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		exit(-1);
	}
	*filename = argv[1];
}
/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{	
	char *filename;
	processCLI(argc,argv,&filename);

	Image *image;
	image = readData(filename);
	Image *new_image;
	new_image = steganography(image);

	for(int i = 0; i < new_image->rows; i++){
		for(int j = 0; j < new_image->cols; j++){
			if(j < new_image->cols - 1)
            	printf("%3u %3u %3u   ", (new_image->image[i][j].R), (new_image->image[i][j].G), (new_image->image[i][j].B));
			else
				printf("%3u %3u %3u", (new_image->image[i][j].R), (new_image->image[i][j].G), (new_image->image[i][j].B));
        }
        printf("\n");
	}

	freeImage(image);
	freeImage(new_image);

	return 0;
}
