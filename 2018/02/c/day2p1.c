#include <stdio.h>
#include <stdlib.h>

#define LETTERS 26

int main(int argc, char const *argv[]) {
    FILE *infile = fopen(argv[1], "r");
    
    int repetitions[2]; // twice, thrice
    for(int i = 0; i < 2; i++) {
        repetitions[i] = 0;
    }
    while(!feof(infile)) {
        // Number of times every letter occurs in the ID
        int letter_repetitions[LETTERS];
        for(int i = 0; i < LETTERS; i++) {
            letter_repetitions[i] = 0;
        }
        
        // the ID string
        char box_id[50];
        fscanf(infile, "%s\n", box_id);
        printf("Box ID: %s\n", box_id);
        for(int i = 0; i < 50; i++) {
            char c = box_id[i];
            if(c == '\0') {
                break;
            }
            // increase counter for letter
            letter_repetitions[c-'a']++;
        }
        
        // Repetitions in the ID. 
        // index 0 is set to 1 if there is a letter that is repeated 2 times
        // index 1 is set to 1 if there is a letter that is repeated 3 times
        int id_repetitions[2];
        for(int i = 0; i < 2; i++) {
            id_repetitions[i] = 0;
        }
        
        for(int i = 0; i < LETTERS; i++) {
            if(letter_repetitions[i] > 1 && letter_repetitions[i] < 4) {
                //printf("The letter '%c' was repeated %d times\n", i+'a', letter_repetitions[i]);
                id_repetitions[letter_repetitions[i]-2] = 1;
            }
        }
        for(int i = 0; i < 2; i++) {
            if(id_repetitions[i] == 1) {
                printf("The Box ID contained a letter repeated %d times\n", i+2);
                repetitions[i]++;
            }
        }
    }
    
    long checksum = 1;
    for(int i = 0; i < 2; i++) {
        printf("repetitions[%d] (%d times): %d\n", i, i+2, repetitions[i]);
        if(repetitions[i] > 0) {
            checksum = checksum * repetitions[i];
        }
    }
    
    printf("Checksum: %ld\n", checksum);
    
    fclose(infile);
    return 0;
}