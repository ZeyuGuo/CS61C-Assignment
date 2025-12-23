/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
int alive_or_die(Color color)
{
	if((color.R + color.G + color.B) == 0){
		return 0;	//die
	} else {
		return 1;	//alive
	}
}

Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color* new_color = (Color*) malloc(sizeof(Color));
	int row_map[8] = {-1, -1, -1,
					   0,      0,
					   1,  1,  1
	};
	int col_map[8] = {-1,  0,  1,
					  -1,      1,
					  -1,  0,  1
	};
	int count = 0;
	int rule_alive = (rule >> 9) & 0x01F;
	int rule_dead = rule & 0x01F;
	int alive_table[9];
	int dead_table[9];
	// update rule
	for(int i = 0; i < 9; i++){
		int alive_bit = (rule_alive >> i) & 0x001;
		int dead_bit = (rule_dead >> i) & 0x001;
		alive_table[i] = (alive_bit == 1) ? 1 : 0;
		dead_table[i] = (dead_bit == 1) ? 1 : 0;
		// printf("alive_table: %d, dead_table: %d\n", alive_table[i], dead_table[i]);
	}
	// count the number of alive neighbors
	for(int i = 0; i < 8; i++){
		int row_co = row + row_map[i];
		int col_co = col + col_map[i];
		// bound, top: -1; bottom: row+1; left: -1; right: col+1
		row_co = (row_co == -1) ? image->rows-1 : row_co;
		row_co = (row_co == image->rows) ? 0 : row_co;
		col_co = (col_co == -1) ? image->cols-1 : col_co;
		col_co = (col_co == image->cols) ? 0 : col_co;
		if(alive_or_die(image->image[row_co][col_co])){
			count++;
		}
		// printf("row_co: %d, col_co: %d\n", row_co, col_co);
		// printf("count: %d\n", count);
	}
	// printf("row: %d, col: %d, count: %d\n", row, col, count);
	// update the next state from rule
	for(int i = 0; i < 9; i++){
		if(alive_or_die(image->image[row][col])){
			if(alive_table[count]){ 
				new_color->R = (uint8_t)255;
				new_color->G = (uint8_t)255;
				new_color->B = (uint8_t)255;
			} else{
				new_color->R = (uint8_t)0;
				new_color->G = (uint8_t)0;
				new_color->B = (uint8_t)0;
			}
		} else{
			if(dead_table[count]){
				new_color->R = (uint8_t)255;
				new_color->G = (uint8_t)255;
				new_color->B = (uint8_t)255;
			} else{
				new_color->R = (uint8_t)0;
				new_color->G = (uint8_t)0;
				new_color->B = (uint8_t)0;
			}
		}
	}

	return new_color;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
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
			Color* new_color = evaluateOneCell(image, i, j, rule); // update cell
			new_image->image[i][j] = *new_color;
			free(new_color);
		}
	}
	return new_image;
}
void processCLI(int argc, char **argv, char **filename, uint32_t *rule) 
{
	if (argc != 3) {
		printf("usage: %s filename rule\n",argv[0]);
		printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
		printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(-1);
	}
	*filename = argv[1];

	uint32_t temp_rule;
    if (sscanf(argv[2], "%x", &temp_rule) != 1) {
        printf("Error: Invalid rule format: %s\n", argv[2]);
        exit(-1);
    }
    
    *rule = temp_rule;
}
/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	char *filename;
	uint32_t rule;
	processCLI(argc,argv,&filename,&rule);
	// printf("filename: %s\n", filename); // testInputs/JohnConway.ppm
    // printf("rule: %s\n", rule); // rule: 0x1808
	// printf("rule: 0x%X\n", rule);

	Image *image;
	image = readData(filename);

	// for(int i = 0; i < image->rows; i++){
	// 	for(int j = 0; j < image->cols; j++){
	// 		if(j < image->cols - 1)
    //         	printf("%3u %3u %3u   ", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
	// 		else
	// 			printf("%3u %3u %3u", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
    //     }
    //     printf("\n");
	// }
	// printf("\n");

	Image *new_image;
	new_image = life(image, rule);

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
