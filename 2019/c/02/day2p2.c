/*
 * Advent of Code 2019 day 2 part 2
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
    
    int instructions_copy[1000];
    for(unsigned int i = 0; i < size; i++) {
        instructions_copy[i] = instructions[i];
    }
    
    // Try every combination of noun and verb
    for(int noun = 0; noun <= 99; noun++) {
        for(int verb = 0; verb <= 99; verb++) {
            // Reset memory
            for(unsigned int i = 0; i < size; i++) {
                instructions[i] = instructions_copy[i];
            }
            
            // Initialize program
            instructions[1] = noun;
            instructions[2] = verb;
            
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
            if(instructions[0] == 19690720) {
                printf("noun: %d verb: %d\n", noun, verb);
                printf("100 * noun + verb = %d\n", 100 * noun + verb);
                return 0;
            }
        }
    }
    return 0;
}