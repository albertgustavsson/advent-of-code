/*
 * Advent of Code 2015 day 2 part 1
 */

#include <stdio.h>
#include <stdlib.h>

int get_smallest(int a, int b, int c);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    int total_area = 0;

    while(!feof(infile)) {
        int l, w, h;
        fscanf(infile, "%dx%dx%d\n", &l, &w, &h);

        total_area += 2*l*w + 2*l*h + 2*w*h + get_smallest(l*w, l*h, w*h);
    }

    fclose(infile);

    printf("Amount of paper needed: %d sq.ft.\n", total_area);

    return 0;
}

int get_smallest(int a, int b, int c) {
    if(a < b && a < c) {
        return a;
    } else if(b < c) {
        return b;
    } else {
        return c;
    }
}