/*
 * Advent of Code 2019 day 1 part 2
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
    
    unsigned long total_fuel = 0;
    while(!feof(infile)) {
        // Read mass of module
        long temp;
        fscanf(infile, "%ld\n", &temp);
        
        // Calculate fuel needed
        long fuel_req = temp/3-2;
        while(fuel_req > 0) {
            total_fuel += fuel_req;
            fuel_req = fuel_req/3-2;
        }
    }
    
    fprintf(stdout, "%ld\n", total_fuel);
    
    fclose(infile);
    return 0;
}