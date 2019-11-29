#include <stdio.h>
#include <stdlib.h>

#define FABRIC_SIZE 1200

int main(int argc, char const *argv[]) {
    FILE *infile = fopen(argv[1], "r");
    if(infile == NULL) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }
    
    unsigned char square_inches[FABRIC_SIZE][FABRIC_SIZE];
    for(int i = 0; i < FABRIC_SIZE; i++) {
        for(int j = 0; j < FABRIC_SIZE; j++) {
            square_inches[i][j] = 0;
        }
    }
    
    while(!feof(infile)) {
        
        int claim_id, left_offset, top_offset, width, height;
        fscanf(infile, "#%d @ %d,%d: %dx%d\n", &claim_id, &left_offset, &top_offset, &width, &height);
        printf("claim_id: %4d left_offset: %3d top_offset: %3d width: %2d height: %2d\n", claim_id, left_offset, top_offset, width, height);
    }
    
    fclose(infile);
    return 0;
}