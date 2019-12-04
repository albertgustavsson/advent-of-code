/*
 * Advent of Code 2015 day 1 part 2
 */

#include <stdio.h>
#include <stdlib.h>

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    long floor = 0;
    int c, pos = 0;
    while((c = fgetc(infile)) != EOF) {
        pos++;
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
        if(floor < 0) {
            break;
        }
    }
    fclose(infile);

    printf("Entered basement on character %d\n", pos);

    return 0;
}