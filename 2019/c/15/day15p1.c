/*
 * Advent of Code 2019 day 15 part 1
 */

#include <stdio.h>
#include <stdlib.h>

void intcode_computer(long instructions[]);

const int memory_size = 10000;

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    if(infile == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    long instructions[memory_size];
    for(int i = 0; i < memory_size; i++) {
        instructions[i] = 0;
    }
    long size = 0;

    // Read instructions from file
    while(!feof(infile)) {
        if(size >= memory_size) {
            fprintf(stderr, "Array is too small\n");
        }
        long code;
        fscanf(infile, "%ld,", &code);
        instructions[size++] = code;
    }
    fclose(infile);

    intcode_computer(instructions);

    return 0;
}

void intcode_computer(long instructions[]) {

    const int maze_size = 50;
    int maze[maze_size][maze_size];
    for(int j = 0; j < maze_size; j++) {
        for(int i = 0; i < maze_size; i++) {
            maze[i][j] = -1; // unknown status
        }
    }

    // x and y goes from 0 to maze_size
    int x = maze_size/2, y = maze_size/2;
    maze[x][y] = 3; // Staring position

    int last_input;

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


                for(int j = 0; j < maze_size; j++) {
                    for(int i = 0; i < maze_size; i++) {
                        if(j == y && i == x) {
                            printf("D");
                            continue;
                        }
                        if(maze[i][j] == -1) {
                            printf(" ");
                        } else if(maze[i][j] == 0) {
                            printf("#");
                        } else if(maze[i][j] == 1) {
                            printf(".");
                        } else if(maze[i][j] == 2) {
                            printf("\x1B[41m"); // red background
                            printf("O");
                            printf("\x1B[0m"); // reset
                        } else if(maze[i][j] == 3) {
                            printf("\x1B[42m"); // green background
                            printf(".");
                            printf("\x1B[0m"); // reset
                        }
                    }
                    printf("\n");
                }
                printf("\n");


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
                long input = 0;
                //scanf("%ld", &input);

                int correct = 0;
                while(!correct) {
                    char c = getchar();
                    // Read newline
                    getchar();

                    //printf("Read char: %c\n", c);

                    switch(c) {
                        case 'w':
                            printf("North\n");
                            input = 1;
                            correct = 1;
                            break;
                        case 's':
                            printf("South\n");
                            input = 2;
                            correct = 1;
                            break;
                        case 'a':
                            printf("West\n");
                            input = 3;
                            correct = 1;
                            break;
                        case 'd':
                            printf("East\n");
                            input = 4;
                            correct = 1;
                            break;
                        default:
                            printf("Other input: %d\n", (int)c);
                            input = 0;
                            break;
                    }
                }

                last_input = input;

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

                if(x < 0 || x >= maze_size || y < 0 || y >= maze_size) {
                    fprintf(stderr, "robot moved too far away: %d,%d\n", x, y);
                    exit(EXIT_FAILURE);
                }

                switch(last_input) {
                    case 1:
                        maze[x][y-1] = maze[x][y-1] == 3?3:param1;
                        if(param1 != 0) {
                            y--;
                        }
                        break;
                    case 2:
                        maze[x][y+1] = maze[x][y+1] == 3?3:param1;
                        if(param1 != 0) {
                            y++;
                        }
                        break;
                    case 3:
                        maze[x-1][y] = maze[x-1][y] == 3?3:param1;
                        if(param1 != 0) {
                            x--;
                        }
                        break;
                    case 4:
                        maze[x+1][y] = maze[x+1][y] == 3?3:param1;
                        if(param1 != 0) {
                            x++;
                        }
                        break;
                    default:
                        break;
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
}