/*
 * Advent of Code 2019 day 2 part 1
 */

#include <stdio.h>
#include <stdlib.h>

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    int instructions[1000];
    unsigned long size = 0;
    
    // Read instructions from file
    while(!feof(infile)) {
        int code;
        fscanf(infile, "%d,", &code);
        instructions[size++] = code;
    }
    fclose(infile);
    
    // Initialize program
    instructions[1] = 12;
    instructions[2] = 2;    
    
    unsigned int pos = 0;
    int exit = 0;
    while(!exit) {
        int pos1, pos2, pos3;
        switch(instructions[pos]) {
            case 1: // Add instruction
                pos1 = instructions[pos+1];
                pos2 = instructions[pos+2];
                pos3 = instructions[pos+3];
                instructions[pos3] = instructions[pos1] + instructions[pos2];
                break;
            case 2: // Multiply instruction
                pos1 = instructions[pos+1];
                pos2 = instructions[pos+2];
                pos3 = instructions[pos+3];
                instructions[pos3] = instructions[pos1] * instructions[pos2];
                break;
            case 99: // Exit instruction
                exit = 1;
                break;
            default:
                break;
        }
        pos += 4;
    }
    
    printf("Value at position 0: %d\n", instructions[0]);
    return 0;
}