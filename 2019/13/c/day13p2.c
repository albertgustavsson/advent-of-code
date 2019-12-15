/*
 * Advent of Code 2019 day 13 part 2
 */

#include <stdio.h>
#include <stdlib.h>

void run_game(long instructions[]);

const int memory_size = 10000;

const int playable = 0; // Change to 1 if you want to play the game
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

    run_game(instructions);

    return 0;
}


void run_game(long instructions[]) {
    long x = 0, y = 0;
    const unsigned int screen_width = 42;
    const unsigned int screen_height = 24;
    int screen[screen_width][screen_height];
    for(unsigned int i = 0; i < screen_width; i++) {
        for(unsigned int j = 0; j < screen_height; j++) {
            screen[i][j] = 0;
        }
    }

    // output_type: 0 = x, 1 = y, 2 = id
    unsigned int output_type = 0;

    // play for free
    instructions[0] = 2;

    if(playable == 0) {
        // Overwrite instuctions to put a "floor" so that the game can't be lost
        for(unsigned int i = 1563; i < 1563+screen_width; i++) {
            instructions[i] = 1;
        }
    }

    int score = 0;

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

                // Draw the screen
                for(unsigned int j = 0; j < screen_height; j++) {
                    for(unsigned int i = 0; i < screen_width; i++) {
                        int id = screen[i][j];
                        switch (id) {
                            case 0: // empty
                                printf("  ");
                                break;
                            case 1: // wall
                                printf("\x1B[41m"); // red background
                                printf("  ");
                                printf("\x1B[0m"); // reset
                                break;
                            case 2: // block
                                printf("\x1B[42m"); // green background
                                printf("  ");
                                printf("\x1B[0m"); // reset
                                break;
                            case 3: // horizontal paddle
                                printf("--");
                                printf("\x1B[0m"); // reset
                                break;
                            case 4: // ball
                                printf("()");
                                printf("\x1B[0m"); // reset
                                break;
                            default:
                                printf("Unknown tile id: %d\n", id);
                                break;
                        }
                    }
                    printf("\n");
                }

                // Input
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[pos+1];
                } else if(mode == 1) { // Immediate mode
                } else if (mode == 2) { // Relative mode
                    param1 = rel_base+instructions[pos+1];
                }
                //printf("Input: ");
                //long input = 0;
                //scanf("%ld", &input);
                long input;
                char c;
                if(playable == 1) {
                    c = getchar();
                    // Read newline
                    getchar();

                    printf("Read char: %c\n", c);

                    switch(c) {
                        case 'd':
                            // code for right
                            printf("Right\n");
                            input = 1;
                            break;
                        case 'a':
                            // code for left
                            printf("Left\n");
                            input = -1;
                            break;
                        case 's':
                            // code for left
                            printf("Stay\n");
                            input = 0;
                            break;
                        default:
                            printf("Other input: %d\n", (int)c);
                            input = 0;
                            break;
                    }
                } else {
                    input = 0;
                }

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
                switch (output_type) {
                    case 0:
                        x = param1;
                        output_type = 1;
                        break;
                    case 1:
                        y = param1;
                        output_type = 2;
                        break;
                    case 2:
                        if(x == -1 && y == 0) {
                            // Output score
                            score = param1;
                            output_type = 0;
                            break;
                        }
                        if(x < 0 || x >= screen_width || y < 0 || y >= screen_height) {
                            printf("Position output value is outside the screen: %ld, %ld\n", x, y);
                            exit(EXIT_FAILURE);
                        }
                        screen[x][y] = param1;
                        output_type = 0;
                        break;
                    default:
                        printf("Unknown output type: %d\n", output_type);
                        exit(EXIT_FAILURE);
                }


                printf("Score: %d\n", score);

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