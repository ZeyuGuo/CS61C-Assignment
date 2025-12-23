#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Color 
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} Color;
typedef struct Image
{
	Color **image;
	uint32_t rows;
	uint32_t cols;
} Image;

int main() {
    const char *filename = "glider.ppm";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char file_format[2];
    fscanf(file, "%s", file_format);
    printf("file_format: %s\n", file_format);
    printf("size of file_format: %ld\n", sizeof(file_format));

    int row, col;
    fscanf(file, "%d %d", &row, &col);
    printf("row: %d, col: %d\n", row, col);

    int max_num = fscanf(file, "%d", &max_num);

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
            // printf("%u, %u, %u\n", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
        }
    }

    fclose(file);

    filename = "answer.ppm";
    file = fopen(filename, "w");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    printf("writing data to answer.ppm ...\n");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fprintf(file, "%3u %3u %3u   ", (image->image[i][j].R), (image->image[i][j].G), (image->image[i][j].B));
        }
        fprintf(file, "\n");
    }

    fclose(file);

   return 0;
}

