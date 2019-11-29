#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    FILE *infile = fopen(argv[1], "r");
    
    // An array storing the strings of all box ID's
    char *box_ids[1024];
    int row = 0;
    
    // Read all box id's from file
    while(!feof(infile)) {
        
        // the ID string
        char box_id[50];
        fscanf(infile, "%s\n", box_id);
        //printf("Box ID: %s\n", box_id);
        for(int i = 0; i < 50; i++) {
            char c = box_id[i];
            if(c == '\0') {
                break;
            }
        }
        // Duplicate string to array
        box_ids[row++] = strdup(box_id);
    }
    /*
    for(int i = 0; i < row; i++) {
        printf("%s\n", box_ids[i]);
    }
    */
    
    int id_length = strlen(box_ids[0]);
    for(int i = 0; i < row; i++) {
        for(int j = i+1; j < row; j++) {
            if(i == j) continue;
            int n_diff_letters = 0;
            for(int k = 0; k < id_length; k++) {
                if(box_ids[i][k] != box_ids[j][k]) {
                    n_diff_letters++;
                }
            }
            if(n_diff_letters == 1) {
                printf("These two IDs differ in 1 letter:\n\t%s\n\t%s\n", box_ids[i], box_ids[j]);
                char *common = malloc(id_length);
                
                int d = 0;
                for(int k = 0; k < id_length; k++) {
                    if(box_ids[i][k] == box_ids[j][k]) {
                        common[k-d] = box_ids[i][k];
                    } else {
                        d++;
                    }
                }
                
                printf("These are the common letters:\n\t%s\n", common);
                free(common);
            }
        }
    }
    
    
    for(int i = 0; i < row; i++) {
        free(box_ids[i]);
    }
    
    fclose(infile);
    return 0;
}