#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct Color 
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
} Color;

int main() {
   const char *filename = "example1.txt";
   FILE *file = fopen(filename, "r");

   // If the file does not exist, create and write initial data to it
//    if (file == NULL) {
       file = fopen(filename, "w");
       if (file == NULL) {
           perror("Error creating file");
           return 1;
       }
       fprintf(file, "P3\n");
       fprintf(file, "200 200\n");
       fprintf(file, " 22  24  19    21  23  19    \n");
       fclose(file);
       file = fopen(filename, "r");
       if (file == NULL) {
           perror("Error opening file");
           return 1;
       }
//    }

    int row, col;
    char file_format[2];

    fscanf(file, "%s", file_format);
    printf("file_format: %s\n", file_format);
    printf("size of file_format: %ld\n", sizeof(file_format));

    fscanf(file, "%d %d", &row, &col);
    printf("row: %d, col: %d\n", row, col);

    // int R, G, B;
    // fscanf(file, "%d %d %d", &R, &G, &B);
    // printf("%d, %d, %d\n", R, G, B);
    // fscanf(file, "%d %d %d", &R, &G, &B);
    // printf("%d, %d, %d\n", R, G, B);

    // Color color;
    // fscanf(file, "%u %u %u", &color.R, &color.G, &color.B);
    // printf("%u, %u, %u\n", color.R, color.G, color.B);
    // fscanf(file, "%u %u %u", &color.R, &color.G, &color.B);
    // printf("%u, %u, %u\n", color.R, color.G, color.B);

    Color* color = (Color*) malloc(sizeof(Color));
    fscanf(file, "%u %u %u", &(color->R), &(color->G), &(color->B));
    printf("%u, %u, %u\n", color->R, color->G, color->B);
    fscanf(file, "%u %u %u", &(color->R), &(color->G), &(color->B));
    printf("%u, %u, %u\n", color->R, color->G, color->B);

   fclose(file);
   return 0;
}