#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    
    FILE *infile = fopen(argv[1], "r");
    long result = 0;
    
    while(!feof(infile)) {
        long temp;
        fscanf(infile, "%ld\n", &temp);
        result += temp;
    }
    printf("%ld\n", result);
    fclose(infile);
    
    return 0;
}