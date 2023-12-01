/*
 * Advent of Code 2019 day 9 part 1
 */

#include <stdio.h>
#include <stdlib.h>

void intcode_computer(long instructions[]);
void mem_write(long instructions[], int size, long pos, long value);
long mem_read(long instructions[], int size, long pos);

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

void mem_write(long instructions[], int size, long pos, long value) {
    if(pos < size) {
        instructions[pos] = value;
    } else {
        fprintf(stderr, "Invalid write to memory position %ld\n", pos);
    }
}

long mem_read(long instructions[], int size, long pos) {
    if(pos < size) {
        return instructions[pos];
    } else {
        fprintf(stderr, "Invalid read from memory position %ld\n", pos);
        return 0;
    }
}

void intcode_computer(long instructions[]) {
    
    int exit = 0, mode;
    long pos = 0, rel_base = 0;
    while(!exit) {
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
                printf("Input: ");
                long input = 0;
                scanf("%ld", &input);
                instructions[param1] = input;
                pos += 2;
                break;
            case 4:
                // Output
                printf("Output: ");
                mode = parameter_types%10;
                if(mode == 0) { // Position mode
                    param1 = instructions[instructions[pos+1]];
                } else if(mode == 1) { // Immediate mode
                    param1 = instructions[pos+1];
                } else if (mode == 2) { // Relative mode
                    param1 = instructions[rel_base+instructions[pos+1]];
                }
                printf("%ld\n", param1);
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
                exit = 1;
                pos += 1;
                break;
            default:
                break;
        }
    }
}
