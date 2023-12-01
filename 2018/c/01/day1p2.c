#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000000

long visited[MAX];
size_t length = 0;

void add_freq_to_array(long f) {
    if(length >= MAX) {
        fprintf(stderr, "Error: array is full\n");
        exit(EXIT_FAILURE);
    }
    visited[length++] = f;
}

int freq_in_array(long f) {
    for(size_t i = 0; i < length; i++) {
        if(visited[i] == f) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    
    long result = 0;
    add_freq_to_array(result);
    
    while(1) {
        FILE *infile = fopen(argv[1], "r");
        
        while(!feof(infile)) {
            long d;
            fscanf(infile, "%ld\n", &d);
            result += d;
            if(freq_in_array(result) == 1) {
                printf("Visited twice: %ld\n", result);
                fclose(infile);
                exit(EXIT_SUCCESS);
            } else {
                add_freq_to_array(result);
            }
        }
        fclose(infile);
    }
    
    
    return 0;
}