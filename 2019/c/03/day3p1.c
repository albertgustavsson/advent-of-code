/*
 * Advent of Code 2019 day 3 part 1
 */

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <math.h>

typedef struct position_s {
    int x;
    int y;
    int wire;
} position;

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    const int size = 500000;
    position positions[size];
    int num_pos = 0;
    
    int closest_distance = INT_MAX;
    int wire = 0;
    int x=0,y=0;
    
    
    int c;
    while((c=fgetc(infile)) != EOF) {
        if(c == '\n') {
            x=0;
            y=0;
            wire++;
            continue;
        }
        
        int num;
        fscanf(infile, "%d,", &num);
        
        for(int i = 0; i < num; i++) {
            switch(c) {
                case 'U':
                    y++;
                    break;
                case 'D':
                    y--;
                    break;
                case 'L':
                    x--;
                    break;
                case 'R':
                    x++;
                    break;
                default:
                    break;
            }
            
            int distance = 0;
            if(x!=0 || y!=0) {
                for(int p = 0; p < num_pos; p++) {
                    if(positions[p].x == x && positions[p].y == y && positions[p].wire != wire) {
                        distance = abs(x)+abs(y);
                        closest_distance = (distance<closest_distance?distance:closest_distance);
                    }
                }
            }
            if(distance == 0) {
                positions[num_pos].x = x;
                positions[num_pos].y = y;
                positions[num_pos].wire = wire;
                num_pos++;
                if(num_pos == size) {
                    fprintf(stderr, "Array is too small\n");
                }
            }
            
        }
    }
    fclose(infile);
    
    printf("Closest intersection distance: %d\n", closest_distance);
    return 0;
}