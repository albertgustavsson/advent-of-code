/*
 * Advent of Code 2019 day 3 part 2
 */

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>

typedef struct position_s {
    int x;
    int y;
    int wire;
    int steps;
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
    
    int fewest_steps = INT_MAX;
    int wire = 0;
    int steps = 0;
    int x=0,y=0;
    
    int c;
    while((c=fgetc(infile)) != EOF) {
        if(c == '\n') {
            x=0;
            y=0;
            wire++;
            steps = 0;
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
            steps++;
            
            int total_steps = 0;
            if(x!=0 || y!=0) {
                for(int p = 0; p < num_pos; p++) {
                    if(positions[p].x == x && positions[p].y == y && positions[p].wire != wire) {
                        total_steps = steps + positions[p].steps;
                        fewest_steps = (total_steps<fewest_steps?total_steps:fewest_steps);
                    }
                }
            }
            if(total_steps == 0) {
                positions[num_pos].x = x;
                positions[num_pos].y = y;
                positions[num_pos].wire = wire;
                positions[num_pos].steps = steps;
                num_pos++;
                if(num_pos == size) {
                    fprintf(stderr, "Array is too small\n");
                }
            }
            
        }
    }
    fclose(infile);
    
    printf("Fewest steps to intersection is: %d\n", fewest_steps);
    return 0;
}