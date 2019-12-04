/*
 * Advent of Code 2015 day 3 part 2
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
    int x[2] = {0,0};
    int y[2] = {0,0};
    int person = 0; // santa's or robot's turn

    int c;
    while((c = fgetc(infile)) != EOF) {
        switch (c) {
            case '^':
                y[person]++;
                break;
            case 'v':
                y[person]--;
                break;
            case '<':
                x[person]--;
                break;
            case '>':
                x[person]++;
                break;
            default:
                break;
        }

        int visited = 0;
        for(int i = 0; i < n_visited; i++) {
            if(visited_houses[i].x == x[person] && visited_houses[i].y == y[person]) {
                visited = 1;
            }
        }
        if(visited == 0) {
            visited_houses[n_visited].x = x[person];
            visited_houses[n_visited].y = y[person];
            n_visited++;
            if(n_visited == size) {
                fprintf(stderr, "Array is too small\n");
            }
        }

        person = (person+1)%2; // change person
    }
    fclose(infile);

    printf("%u houses got at least one present\n", n_visited);

    return 0;
}