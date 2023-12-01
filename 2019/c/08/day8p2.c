/*
 * Advent of Code 2019 day 8 part 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define RESET 		"\x1B[0m"
#define BG_BLACK	"\x1B[40m"
#define BG_WHITE	"\x1B[47m"

const int image_width = 25;
const int image_height = 6;
const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    const int n_layers = 200;
    int layers[n_layers][image_width][image_height];
    int layer = 0, pixel_x = 0, pixel_y = 0;
    char c;
    while((c = fgetc(infile)) != EOF) {
        int digit = c - '0'; // Convert char to int
        layers[layer][pixel_x][pixel_y] = digit;
        
        pixel_x++;
        if(pixel_x == image_width) {
            pixel_x = 0;
            pixel_y++;
            if(pixel_y == image_height) {
                pixel_y = 0;
                layer++;
                if(layer == n_layers) {
                    fprintf(stderr, "Too many layers\n");
                    return EXIT_FAILURE;
                }
            }
        }
    }
    
    fclose(infile);
    
    /*
    for(int l = 0; l < layer; l++) {
        printf("Layer %3d: ", l);
        for(int y = 0; y < image_height; y++) {
            for(int x = 0; x < image_width; x++) {
                printf("%d ", layers[l][x][y]);
            }
            printf("\n");
        }
    }
    */
    
    int final_image[image_width][image_height];
    
    for(int x = 0; x < image_width; x++) {
        for(int y = 0; y < image_height; y++) {
            final_image[x][y] = 2; // Set every pixel to transparent
        }
    }
    
    for(int l = 0; l < layer; l++) {
        for(int x = 0; x < image_width; x++) {
            for(int y = 0; y < image_height; y++) {
                if(final_image[x][y] == 2) {
                    final_image[x][y] = layers[l][x][y];
                }
            }
        }
    }
    
    for(int y = 0; y < image_height; y++) {
        for(int x = 0; x < image_width; x++) {
            if(final_image[x][y]==1) {
                printf(BG_WHITE); // Background color: white
            } else {
                printf(BG_BLACK); // Background color: black
            }
            printf(" ");
        }
        printf(RESET); // Reset colors
        printf("\n");
    }
    
    return 0;
}