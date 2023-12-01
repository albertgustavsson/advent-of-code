/*
 * Advent of Code 2019 day 8 part 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int zeros;
    int zeros_min = INT_MAX;
    int zeros_min_layer = -1;
    for(int l = 0; l < layer; l++) {
        zeros = 0;
        for(int y = 0; y < image_height; y++) {
            for(int x = 0; x < image_width; x++) {
                if(layers[l][x][y] == 0) zeros++;
            }
        }
        if(zeros < zeros_min) {
            zeros_min = zeros;
            zeros_min_layer = l;
        }
    }
    
    printf("layer with fewest zeros was layer %d\n", zeros_min_layer);
    
    int ones = 0, twos = 0;
    for(int y = 0; y < image_height; y++) {
        for(int x = 0; x < image_width; x++) {
            if(layers[zeros_min_layer][x][y] == 1) ones++;
            else if(layers[zeros_min_layer][x][y] == 2) twos++;
        }
    }
    
    printf("Number of ones: %d, number of twos: %d\n", ones, twos);
    printf("Answer: %d\n", ones * twos);
    
    return 0;
}