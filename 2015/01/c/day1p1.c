/*
 * Advent of Code 2015 day 1 part 1
 */

#include <stdio.h>
#include <stdlib.h>

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    long floor = 0;
    int c;
    while((c = fgetc(infile)) != EOF) {
        switch (c) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
            default:
                break;
        }
    }
    fclose(infile);

    printf("Final floor: %ld\n", floor);

    return 0;
}