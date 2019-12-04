/*
 * Advent of Code 2015 day 3 part 1
 */

#include <stdio.h>
#include <stdlib.h>

const char *filename = "input.txt";

typedef struct position_s {
    int x;
    int y;
} position;

int main(void) {
    FILE *infile = fopen(filename, "r");

    const int size = 5000;
    position visited_houses[size];
    visited_houses[0].x = 0;
    visited_houses[0].y = 0;
    int n_visited = 1;
    int x = 0;
    int y = 0;

    int c;
    while((c = fgetc(infile)) != EOF) {
        switch (c) {
            case '^':
                y++;
                break;
            case 'v':
                y--;
                break;
            case '<':
                x--;
                break;
            case '>':
                x++;
                break;
            default:
                break;
        }
        int visited = 0;
        for(int i = 0; i < n_visited; i++) {
            if(visited_houses[i].x == x && visited_houses[i].y == y) {
                visited = 1;
            }
        }
        if(visited == 0) {
            visited_houses[n_visited].x = x;
            visited_houses[n_visited].y = y;
            n_visited++;
            if(n_visited == size) {
                fprintf(stderr, "Array is too small\n");
            }
        }
    }
    fclose(infile);

    printf("%u houses got at least one present\n", n_visited);

    return 0;
}