/*
 * Advent of Code 2019 day 5 part 1
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
    
    int instructions[10000];
    unsigned long size = 0;
    
    // Read instructions from file
    while(!feof(infile)) {
        int code;
        fscanf(infile, "%d,", &code);
        instructions[size++] = code;
    }
    fclose(infile); 
    
    unsigned int pos = 0;
    int exit = 0;
    while(!exit) {
        int param1, param2;
        int operation = instructions[pos]%100;
        int parameter_types = instructions[pos]/100;
        switch(operation) {
            case 1: // Add instruction
                if(parameter_types%10 == 0) {
                    param1 = instructions[instructions[pos+1]];
                } else {
                    param1 = instructions[pos+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[instructions[pos+2]];
                } else {
                    param2 = instructions[pos+2];
                }
            
                instructions[instructions[pos+3]] = param1 + param2;
                pos += 4;
                break;
            case 2: // Multiply instruction
                if(parameter_types%10 == 0) {
                    param1 = instructions[instructions[pos+1]];
                } else {
                    param1 = instructions[pos+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[instructions[pos+2]];
                } else {
                    param2 = instructions[pos+2];
                }
                
                instructions[instructions[pos+3]] = param1 * param2;
                pos += 4;
                break;
            case 3:
                // Input
                printf("Input: ");
                int input = 0;
                scanf("%d", &input);
                param1 = instructions[pos+1];
                instructions[param1] = input;
                pos += 2;
                break;
            case 4:
                // Output
                printf("Output: ");
                if(parameter_types%10 == 0) {
                    param1 = instructions[instructions[pos+1]];
                } else {
                    param1 = instructions[pos+1];
                }
                printf("%d\n", param1);
                pos += 2;
                break;
            case 99: // Exit instruction
                exit = 1;
                break;
            default:
                break;
        }
    }
    
    printf("Value at position 0: %d\n", instructions[0]);
    return 0;
}