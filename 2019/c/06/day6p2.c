/*
 * Advent of Code 2019 day 6 part 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct orbit {
     char *center; // The object that is orbited
     char *outer; // The object that is orbiting the center
} orbit;

/* 
 * Minimum number of transfers to get from src to dest with an intermediate 
 * object. Intermediate should be set to "COM" when called. This will always 
 * find at least one posible solution since every object is indirectly orbiting 
 * COM. The function will call iself recursively with different intermediates
 */
int min_transfers(orbit orbits[], int n, char *src, char *dest, char *intermediate);

/*
 * The number of transfers to get from src to dest by only going to an orbiting 
 * object, never to the center. Kind of like only going to a child node in a 
 * tree, and never going to a parent node.
 */
int transfers(orbit orbits[], int n, char *src, char *dest);

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
    
    char *source, *destination;
    for(int i = 0; i < n_read; i++) {
        if(strcmp(orbits[i].outer, "YOU") == 0) {
            source = orbits[i].center;
        }
        if(strcmp(orbits[i].outer, "SAN") == 0) {
            destination = orbits[i].center;
        }
    }
    int min = min_transfers(orbits, n_read, source, destination, "COM");
    printf("Minimum number of transfers is %d\n", min);
    
    fclose(infile);
    return 0;
}

int min_transfers(orbit orbits[], int n, char *src, char *dest, char *intermediate) {
    int min_steps = INT_MAX;
    
    char *temp = intermediate;
    
    // Get the number of steps from src to dest. This is the distance from 
    // intermediate to src added to the distance from intermediate to dest. 
    // If no route exists min_steps will not be updated.
    int res1 = transfers(orbits, n, temp, src);
    int res2 = transfers(orbits, n, temp, dest);
    if(res1 != -1 && res2 != -1) {
        int steps = res1+res2;
        min_steps = (steps<min_steps?steps:min_steps);
    }
    
    // Find every child object that orbits temp
    for(int i = 0; i < n; i++) {
        if(strcmp(orbits[i].center,temp) == 0) {
            // Get the smallest number of steps from src to dest with this 
            // child object as the intermediate.
            int steps = min_transfers(orbits, n, src, dest, orbits[i].outer);
            if(steps != -1) {
                min_steps = (steps<min_steps?steps:min_steps);
            }
        }
    }
    
    if(min_steps == INT_MAX) {
        return -1; // If no route was found
    } else {
        return min_steps;
    }
}

int transfers(orbit orbits[], int n, char *src, char *dest) {
    if(strcmp(src, dest) == 0) {
        return 0;
    }
    for(int i = 0; i < n; i++) {
        if(strcmp(orbits[i].center,src)==0) {
            int res = transfers(orbits, n, orbits[i].outer, dest);
            if(res != -1) {
                return 1+res;
            }
        }
    }
    return -1;
}