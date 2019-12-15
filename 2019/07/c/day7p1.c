/*
 * Advent of Code 2019 day 7 part 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int int_code_amplifier(int instruction[], int phase, int input);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    int instructions[10000];
    long size = 0;
    
    // Read instructions from file
    while(!feof(infile)) {
        if(size == 10000) {
            fprintf(stderr, "Array is too small\n");
        }
        int code;
        fscanf(infile, "%d,", &code);
        instructions[size++] = code;
    }
    fclose(infile);
    
    int instructions_copy[5][size];
    for(int j = 0; j < 5; j++) {
        for(int i = 0; i < size; i++) {
            instructions_copy[j][i]=instructions[i];
        }
    }
    
    int output_max = INT_MIN;
    
    for(int s1 = 0; s1 < 5; s1++) {
        for(int s2 = 0; s2 < 5; s2++) {
            if(s2==s1) continue; // Each setting is only used once
            for(int s3 = 0; s3 < 5; s3++) {
                if(s3==s2 || s3==s1) continue;
                for(int s4 = 0; s4 < 5; s4++) {
                    if(s4==s3 || s4==s2 || s4==s1) continue;
                    for(int s5 = 0; s5 < 5; s5++) {
                        if(s5==s4 || s5==s3 || s5==s2 || s5 == s1) continue;

                        int output = 0;
                        output = int_code_amplifier(instructions_copy[0], s1, output);
                        output = int_code_amplifier(instructions_copy[1], s2, output);
                        output = int_code_amplifier(instructions_copy[2], s3, output);
                        output = int_code_amplifier(instructions_copy[3], s4, output);
                        output = int_code_amplifier(instructions_copy[4], s5, output);
                        output_max = (output>output_max?output:output_max);
                    }
                }
            }
        }
    }
    
    printf("Maximum output was: %d\n", output_max);
    
    return 0;
}

int int_code_amplifier(int instructions[], int phase, int input) {
    int inputs[2] = {phase, input};
    int input_num = 0;
    
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
                //printf("Input: ");
                //int input = 0;
                //scanf("%d", &input);
                param1 = instructions[pos+1];
                instructions[param1] = inputs[input_num++];
                pos += 2;
                break;
            case 4:
                // Output
                //printf("Output: ");
                if(parameter_types%10 == 0) {
                    param1 = instructions[instructions[pos+1]];
                } else {
                    param1 = instructions[pos+1];
                }
                //printf("%d\n", param1);
                return param1;
                pos += 2;
                break;
            case 5: // jump-if-true
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
                
                if(param1 != 0) {
                    pos = param2;
                } else {
                    pos += 3;
                }
                break;
            case 6: // jump-if-false
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
                
                if(param1 == 0) {
                    pos = param2;
                } else {
                    pos += 3;
                }
                break;
            case 7: // less-than
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
                
                if(param1 < param2) {
                    instructions[instructions[pos+3]] = 1;
                } else {
                    instructions[instructions[pos+3]] = 0;
                }
                pos += 4;
                break;
            case 8: // equals
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
                
                if(param1 == param2) {
                    instructions[instructions[pos+3]] = 1;
                } else {
                    instructions[instructions[pos+3]] = 0;
                }
                pos += 4;
                break;
            case 99: // Exit instruction
                exit = 1;
                break;
            default:
                break;
        }
    }
    return INT_MIN;
}
