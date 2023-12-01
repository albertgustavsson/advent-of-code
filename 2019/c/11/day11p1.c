/*
 * Advent of Code 2019 day 11 part 1
 */

#include <stdio.h>
#include <stdlib.h>

void run_robot(long instructions[]);

const int memory_size = 10000;
const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    long instructions[memory_size];
    for(int i = 0; i < memory_size; i++) {
        instructions[i] = 0;
    }
    long size = 0;
    
    // Read instructions from file
    while(!feof(infile)) {
        long code;
        fscanf(infile, "%ld,", &code);
        if(size >= memory_size) {
            fprintf(stderr, "Array is too small\n");
            exit(EXIT_FAILURE);
        }
        instructions[size++] = code;
    }
    fclose(infile);
    
    run_robot(instructions);
    
    return 0;
}

void run_robot(long instructions[]) {
    
    const int hull_size = 200;
    int hull[hull_size][hull_size];
    for(int i = 0; i < hull_size; i++) {
        for(int j = 0; j < hull_size; j++) {
            hull[i][j] = -1; // not painted yet (black)
        }
    }
    
    /* x and y goes from 0 to hull_size
     * direction is 0,1,2,3 where 0:up , 1:right, 2:down, 3:left
     */
    int x = hull_size/2, y = hull_size/2, direction = 0;
    int output_type = 0;
    
    int done = 0, mode;
    long pos = 0, rel_base = 0;
    while(!done) {
        long param1, param2, output_pos;
        long operation = instructions[pos]%100;
        long parameter_types = instructions[pos]/100;
        switch(operation) {
            case 1: // Add instruction
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    output_pos = instructions[pos+3];
                } else if(mode == 1) { // Immediate mode
                } else if (mode == 2) { // Relative mode
                    output_pos = rel_base+instructions[pos+3];
                }
                
                instructions[output_pos] = param1 + param2;
                pos += 4;
                break;
            case 2: // Multiply instruction
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    output_pos = instructions[pos+3];
                } else if(mode == 1) { // Immediate mode
                } else if (mode == 2) { // Relative mode
                    output_pos = rel_base+instructions[pos+3];
                }
                
                instructions[output_pos] = param1 * param2;
                pos += 4;
                break;
            case 3:
                // Input
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[pos+1];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = rel_base+instructions[pos+1];
                }
                //printf("Input: ");
                long input = (hull[x][y]==1?1:0); // Color of panel. (-1 also gives black)
                //scanf("%ld", &input);
                instructions[param1] = input;
                pos += 2;
                break;
            case 4:
                // Output
                //printf("Output: ");
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                //printf("%ld\n", param1);
                if(output_type == 0) { // 0 = color
                    hull[x][y] = param1;
                    output_type = 1;
                } else if(output_type == 1) {
                    if(param1 == 0) { // Turn left
                        direction = (direction==0?3:direction-1);
                    } else if(param1 == 1) { // Turn right
                        direction = (direction==3?0:direction+1);
                    }
                    switch (direction) {
                        case 0:
                            y--; // Move upwards
                            break;
                        case 1:
                            x++; // Move to the right
                            break;
                        case 2:
                            y++; // Move downwards
                            break;
                        case 3:
                            x--; // Move to the left
                            break;
                        default:
                            fprintf(stderr, "Unknown direction: %d\n", direction);
                            break;
                    }
                    if(x < 0 || x >= hull_size || y < 0 || y >= hull_size) {
                        fprintf(stderr, "Robot reached the end of the hull: %d,%d\n", x, y);
                        exit(EXIT_FAILURE);
                    }
                    output_type = 0;
                }
                pos += 2;
                break;
            case 5: // jump-if-true
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                
                if(param1 != 0) {
                    pos = param2;
                } else {
                    pos += 3;
                }
                break;
            case 6: // jump-if-false
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                
                if(param1 == 0) {
                    pos = param2;
                } else {
                    pos += 3;
                }
                break;
            case 7: // less-than
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    output_pos = instructions[pos+3];
                } else if(mode == 1) { // Immediate mode
                } else if (mode == 2) { // Relative mode
                    output_pos = rel_base+instructions[pos+3];
                }
                
                if(param1 < param2) {
                    instructions[output_pos] = 1;
                } else {
                    instructions[output_pos] = 0;
                }
                pos += 4;
                break;
            case 8: // equals
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param2 = instructions[instructions[pos+2]];
                } else if(mode == 1) { // Immediate mode
                    param2 = instructions[pos+2];
                } else if (mode == 2) { // Relative mode
                    param2 = instructions[rel_base+instructions[pos+2]];
                }
                parameter_types/=10;
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    output_pos = instructions[pos+3];
                } else if(mode == 1) { // Immediate mode
                } else if (mode == 2) { // Relative mode
                    output_pos = rel_base+instructions[pos+3];
                }
                
                if(param1 == param2) {
                    instructions[output_pos] = 1;
                } else {
                    instructions[output_pos] = 0;
                }
                pos += 4;
                break;
            case 9: // Relative base offset instruction
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                rel_base += param1;
                pos += 2;
                break;
            case 99: // Exit instruction
                done = 1;
                pos += 1;
                break;
            default:
                break;
        }
    }
    
    int n_painted = 0;
    printf("Hull looks like this:\n");
    for(int y_ = 0; y_ < hull_size; y_++) {
        for(int x_ = 0; x_ < hull_size; x_++) {
            printf("%c", (hull[x_][y_]==1?'#':'.'));
            if(hull[x_][y_] != -1) {
                n_painted++;
            }
        }
        printf("\n");
    }
    printf("Number of panels that were painted at least once: %d\n", n_painted);
}
