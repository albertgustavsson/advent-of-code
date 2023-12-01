/*
 * Advent of Code 2019 day 15 part 2
 */

#include <stdio.h>
#include <stdlib.h>

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    while(!feof(infile)) {
        
    }
    
    fclose(infile);
    return 0;
}