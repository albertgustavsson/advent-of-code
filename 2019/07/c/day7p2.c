/*
 * Advent of Code 2019 day 7 part 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int int_code_amplifier(int id, int state[5], int instructions[5][10000], int setting, int input);

int setting_read[5];
unsigned int pos[5];
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
    
    int instructions_copy[5][10000];
    for(int j = 0; j < 5; j++) {
        for(int i = 0; i < size; i++) {
            instructions_copy[j][i]=instructions[i];
        }
    }
    
    int output_max = INT_MIN;
    int state[5] = {0,0,0,0,0};
    
    for(int s1 = 5; s1 < 10; s1++) {
        for(int s2 = 5; s2 < 10; s2++) {
            if(s2==s1) continue; // Each setting is only used once
            for(int s3 = 5; s3 < 10; s3++) {
                if(s3==s2 || s3==s1) continue;
                for(int s4 = 5; s4 < 10; s4++) {
                    if(s4==s3 || s4==s2 || s4==s1) continue;
                    for(int s5 = 5; s5 < 10; s5++) {
                        if(s5==s4 || s5==s3 || s5==s2 || s5 == s1) continue;
                        //printf("Trying setting: %d %d %d %d %d\n", s1, s2, s3, s4, s5);
                        
                        // Reset
                        for(int i = 0; i < 5; i++) {
                            setting_read[i] = 0;
                            pos[i] = 0;
                            state[i] = 0;
                        }
                        for(int j = 0; j < 5; j++) {
                            for(int i = 0; i < size; i++) {
                                instructions_copy[j][i]=instructions[i];
                            }
                        }
                        int output = 0;
                        
                        while(1) {
                            
                            int output_temp;
                            output_temp = int_code_amplifier(0, state, instructions_copy, s1, output);
                            if(state[0]==1) {
                                break;
                            } else {
                                output = output_temp;
                            }
                            output_temp = int_code_amplifier(1, state, instructions_copy, s2, output);
                            if(state[1]==1) {
                                break;
                            } else {
                                output = output_temp;
                            }
                            output_temp = int_code_amplifier(2, state, instructions_copy, s3, output);
                            if(state[2]==1) {
                                break;
                            } else {
                                output = output_temp;
                            }
                            output_temp = int_code_amplifier(3, state, instructions_copy, s4, output);
                            if(state[3]==1) {
                                break;
                            } else {
                                output = output_temp;
                            }
                            output_temp = int_code_amplifier(4, state, instructions_copy, s5, output);
                            if(state[4]==1) {
                                break;
                            } else {
                                output = output_temp;
                                //printf("Output: %d\n", output);
                                output_max = (output>output_max?output:output_max);
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("Maximum output was: %d\n", output_max);
    
    return 0;
}

int int_code_amplifier(int id, int state[5], int instructions[5][10000], int setting, int input) {
    //printf("Running amplifier %d\n", id);
    
    int next_input;
    if(setting_read[id] == 0) {
        next_input = setting;
    } else {
        next_input = input;
    }
    
    int exit = 0;
    while(!exit) {
        int param1, param2;
        int operation = instructions[id][pos[id]]%100;
        int parameter_types = instructions[id][pos[id]]/100;
        switch(operation) {
            case 1: // Add instruction
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
            
                instructions[id][instructions[id][pos[id]+3]] = param1 + param2;
                pos[id] += 4;
                break;
            case 2: // Multiply instruction
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
                
                instructions[id][instructions[id][pos[id]+3]] = param1 * param2;
                pos[id] += 4;
                break;
            case 3:
                // Input
                //printf("Input: ");
                //int input = 0;
                //scanf("%d", &input);
                param1 = instructions[id][pos[id]+1];
                instructions[id][param1] = next_input;
                setting_read[id] = 1;
                next_input = input;
                pos[id] += 2;
                break;
            case 4:
                // Output
                //printf("Output: ");
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                //printf("%d\n", param1);
                pos[id] += 2;
                return param1;
                break;
            case 5: // jump-if-true
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
                
                if(param1 != 0) {
                    pos[id] = param2;
                } else {
                    pos[id] += 3;
                }
                break;
            case 6: // jump-if-false
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
                
                if(param1 == 0) {
                    pos[id] = param2;
                } else {
                    pos[id] += 3;
                }
                break;
            case 7: // less-than
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
                
                if(param1 < param2) {
                    instructions[id][instructions[id][pos[id]+3]] = 1;
                } else {
                    instructions[id][instructions[id][pos[id]+3]] = 0;
                }
                pos[id] += 4;
                break;
            case 8: // equals
                if(parameter_types%10 == 0) {
                    param1 = instructions[id][instructions[id][pos[id]+1]];
                } else {
                    param1 = instructions[id][pos[id]+1];
                }
                parameter_types/=10;
                if(parameter_types%10 == 0) {
                    param2 = instructions[id][instructions[id][pos[id]+2]];
                } else {
                    param2 = instructions[id][pos[id]+2];
                }
                
                if(param1 == param2) {
                    instructions[id][instructions[id][pos[id]+3]] = 1;
                } else {
                    instructions[id][instructions[id][pos[id]+3]] = 0;
                }
                pos[id] += 4;
                break;
            case 99: // Exit instruction
                exit = 1;
                pos[id] += 1;
                break;
            default:
                break;
        }
    }
    
    state[id] = 1;
    //printf("Halted\n");
    
    return 0;
}
