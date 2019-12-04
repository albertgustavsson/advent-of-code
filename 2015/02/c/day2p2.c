/*
 * Advent of Code 2015 day 2 part 2
 */

#include <stdio.h>
#include <stdlib.h>

int get_smallest(int a, int b, int c);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    int total_ribbon = 0;

    while(!feof(infile)) {
        int l, w, h;
        fscanf(infile, "%dx%dx%d\n", &l, &w, &h);

        int wrap = 2 * get_smallest(l+w, l+h, w+h); // Smallest perimeter
        int bow = l*w*h;
        total_ribbon += wrap + bow;
    }

    fclose(infile);

    printf("Amount of ribbon needed: %d ft.\n", total_ribbon);

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