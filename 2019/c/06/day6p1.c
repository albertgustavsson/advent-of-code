/*
 * Advent of Code 2019 day 6 part 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct orbit {
     char *center;
     char *outer;
} orbit;

typedef struct ret_data {
    int direct;
    int indirect;
    int total;
} ret_data;

ret_data count_orbits(orbit orbits[], int n, char *source);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    const int size = 5000;
    orbit orbits[size];
    int n_read = 0;
    
    while(!feof(infile)) {
        char temp[10];
        fscanf(infile, "%s\n", temp);
        char *line = strdup(temp);
        
        char *center = strdup(strsep(&line, ")"));
        char *outer = strdup(line);
        orbits[n_read].center = center;
        orbits[n_read].outer = outer;
        //fprintf(stderr, "Orbit: %s around %s\n", orbits[n_orbits].outer, orbits[n_orbits].center);
        n_read++;
        if(n_read >= size) {
            fprintf(stderr, "Array is too small\n");
        }
    }
    
    /*
    for(int i = 0; i < n_read; i++) {
        fprintf(stderr, "%s orbits %s\n", orbits[i].outer, orbits[i].center);
    }
    */
    
    ret_data ret = count_orbits(orbits, n_read, "COM");
    printf("Total number of orbits is %d\n", ret.total);
    
    
    fclose(infile);
    return 0;
}


// Find orbits arround and object
ret_data count_orbits(orbit orbits[], int n, char *source) {
    ret_data ret = {0,0,0};
    for(int i = 0; i < n; i++) {
        if(strcmp(orbits[i].center,source) == 0) {
            // Found an object that orbits arround source
            // Find orbits arround that object
            ret_data temp = count_orbits(orbits,n,orbits[i].outer);
            ret.direct++;
            ret.indirect += temp.direct + temp.indirect;
            ret.total += temp.total;
        }
    }
    ret.total += ret.direct + ret.indirect;
    //fprintf(stderr, "Orbits around %s: %d direct, %d indirect, %d total\n", source, ret.direct, ret.indirect, ret.total);
    return ret;
}