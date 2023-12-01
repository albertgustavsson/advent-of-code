/*
 * Advent of Code 2019 day 14 part 2
 *
 * Counting the amount of needed ore does not work for larger amounts of fuel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chemical {
    long amount;
    char *name;
} chemical;

typedef struct reaction {
    chemical **inputs; // an array of inputs chemicals
    int n_inputs; // the number of inputs
    chemical *output; // the output chemical
} reaction;

reaction *file_get_reaction(FILE *infile);
chemical *file_get_chemical(FILE *infile);
void print_reaction(reaction *r);
void print_chemical(chemical *c);
chemical *copy_chemical(chemical *c);


const char *filename = "input2.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");

    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }

    const int max_reactions = 100;
    reaction *reactions[max_reactions];
    int reactions_i = 0;

    while(!feof(infile)) {

        if(reactions_i >= max_reactions) {
            fprintf(stderr, "reactions index too high\n");
            exit(EXIT_FAILURE);
        }
        reactions[reactions_i++] = file_get_reaction(infile);
    }

    for(int i = 0; i < reactions_i; i++) {
        print_reaction(reactions[i]);
        printf("\n");
    }

    printf("\n");
    const unsigned long max_ore = 1000000000000;
    unsigned long max_fuel_amount;

    // this loop should be replaced with som kind of
    // binary search (divide and conquer) algorithm for higher performance
    for(unsigned long fuel_amount = 82892753; fuel_amount <= 82892753; fuel_amount++) {

        const int max_leftovers = 100;
        chemical *leftovers[max_leftovers];
        int leftovers_i = 0;

        const int max_needed = 100;
        chemical *needed[max_needed];
        int needed_i = 0;

        chemical *fuel = malloc(sizeof(chemical));
        fuel->name = strdup("FUEL");
        fuel->amount = fuel_amount;
        needed[needed_i++] = fuel;

        unsigned long ore_needed = 0;
        do {
            // produce the needed amount of the chemical
            // check if the chemical is ORE
            printf("Needed: \n");
            for(int j = 0; j < needed_i; j++) {
                print_chemical(needed[j]);
                printf("\n");
            }
            printf("\n");
            // Remove c from needed
            chemical *c = needed[0];
            for(int j = 0; j < needed_i-1; j++) {
                needed[j] = needed[j+1];
            }
            needed_i--;
            // check if the chemical is ORE
            if(strcmp(c->name, "ORE") == 0) {
                ore_needed += c->amount;
                free(c->name);
                free(c);
                continue;
            }
            for(int j = 0; j < reactions_i; j++) {
                // Find the reaction that produces the chemical
                if(strcmp(reactions[j]->output->name, c->name) == 0) {
                    printf("Reaction %d gives %s\n", j, c->name);
                    print_reaction(reactions[j]);
                    printf("\n");

                    // check for leftovers to use
                    printf("Leftovers:\n");
                    for(int k = 0; k < leftovers_i; k++) {
                        print_chemical(leftovers[k]);
                        printf("\n");
                    }
                    printf("\n");
                    int leftover = 0;
                    for(int k = 0; k < leftovers_i; k++) {
                        if(strcmp(leftovers[k]->name, c->name) == 0) {
                            leftover = leftovers[k]->amount;
                            break;
                        }
                    }
                    printf("Leftover from before: %d\n", leftover);

                    // calculate number of times to run the reaction
                    int n = 0;
                    int to_make = (c->amount-leftover);
                    int reaction_makes = reactions[j]->output->amount;
                    if(to_make > 0) {
                        if(to_make%reaction_makes == 0) {
                            //if needed is a multiple of what the reaction generates
                            n = (to_make/reaction_makes);
                        } else {
                            n = (to_make/reaction_makes) + 1;
                        }
                    }

                    if(n > 0) {
                        printf("Running reaction %d times\n", n);
                        // add all inputs to needed array
                        for(int k = 0; k < reactions[j]->n_inputs; k++) {
                            // Add chemical to array
                            if(needed_i >= max_needed) {
                                fprintf(stderr, "needed index too high\n");
                                exit(EXIT_FAILURE);
                            }
                            needed[needed_i] = copy_chemical(reactions[j]->inputs[k]);
                            needed[needed_i]->amount *= n;
                            needed_i++;
                        }
                    }

                    // calculate how much is not used
                    leftover = (n*reactions[j]->output->amount)-to_make;
                    printf("Leftover after this reaction: %d\n", leftover);
                    if(leftover > 0) {
                        // Put leftover in array
                        int found = 0;
                        for(int k = 0; k < leftovers_i; k++) {
                            if(strcmp(leftovers[k]->name, c->name) == 0) {
                                leftovers[k]->amount = leftover;
                                found = 1;
                                break;
                            }
                        }
                        if(!found) {
                            if(leftovers_i >= max_leftovers) {
                                fprintf(stderr, "leftovers index too high\n");
                                exit(EXIT_FAILURE);
                            }
                            leftovers[leftovers_i] = copy_chemical(reactions[j]->output);
                            leftovers[leftovers_i]->amount = leftover;
                            leftovers_i++;
                        }
                    } else {
                        // remove leftover from array
                        for(int k = 0; k < leftovers_i; k++) {
                            if(strcmp(leftovers[k]->name, c->name) == 0) {
                                free(leftovers[k]->name);
                                free(leftovers[k]);
                                for(int l = k; l < leftovers_i-1; l++) {
                                    leftovers[l] = leftovers[l+1];
                                }
                                leftovers_i--;
                                break;
                            }
                        }
                    }
                }
            }

            free(c->name);
            free(c);
        } while(needed_i > 0);
        // free all memory in needed array
        for(int i = 0; i < needed_i; i++) {
            free(needed[i]->name);
            free(needed[i]);
        }

        for(int i = 0; i < leftovers_i; i++) {
            free(leftovers[i]->name);
            free(leftovers[i]);
        }


        printf("Total ore needed for %ld fuel: %ld\n\n", fuel_amount, ore_needed);
        if(ore_needed <= max_ore) {
            max_fuel_amount = fuel_amount;
        } else {
            break;
        }
    }

    printf("Total amount of fuel that can be produced with %ld ore: %ld\n", max_ore, max_fuel_amount);

    for(int i = 0; i < reactions_i; i++) {
        for(int j = 0; j < reactions[i]->n_inputs; j++) {
            free(reactions[i]->inputs[j]->name);
            free(reactions[i]->inputs[j]);
        }
        free(reactions[i]->inputs);
        free(reactions[i]->output->name);
        free(reactions[i]->output);
        free(reactions[i]);
    }

    fclose(infile);
    return 0;
}

reaction *file_get_reaction(FILE *infile) {
    const int max_inputs = 20;
    chemical *inputs[max_inputs];
    int inputs_i = 0;

    do {
        // Read all input chemicals
        if(inputs_i >= max_inputs) {
            fprintf(stderr, "inputs index too high\n");
            exit(EXIT_FAILURE);
        }
        //printf("Read next input chemical\n");
        chemical *chem = file_get_chemical(infile);
        //print_chemical(chem);
        //printf("\n");
        inputs[inputs_i++] = chem;

        char c = fgetc(infile);
        if(c == ',') { // if first character after chemical name is ','
            fgetc(infile); // read ' '
            continue; // read next input chemical
        } else {// if first character after chemical name is ' '
            fgetc(infile); // read '='
            fgetc(infile); // read '>'
            fgetc(infile); // read ' '
            break; // read output chemical
        }
    } while(1);

    //printf("Read output chemical\n");
    chemical *chem = file_get_chemical(infile);
    //print_chemical(chem);
    //printf("\n");

    reaction *r = malloc(sizeof(reaction));
    r->n_inputs = inputs_i;
    r->inputs = malloc(sizeof(chemical*) * inputs_i);
    for(int i = 0; i < inputs_i; i++) {
        r->inputs[i] = inputs[i];
    }
    r->output = chem;

    return r;
}

chemical *file_get_chemical(FILE *infile) {
    const int max_buf = 10;
    char buf[max_buf];
    int buf_i = 0;

    chemical *chem = malloc(sizeof(chemical));
    fscanf(infile, "%ld ", &chem->amount);
    //printf("amount: %ld\n", chem->amount);

    // read chemical name
    int done = 0;
    do {
        int c = fgetc(infile);
        //printf("c: %c (%d)\n", c, c);
        if(c == ' ' || c == ',' || c == '\n') {
            ungetc(c, infile); // push back to file stream
            done = 1;
            break;
        } else if(c == EOF) {
            break;
        }

        if(buf_i >= max_buf) {
            fprintf(stderr, "buf index too high\n");
            exit(EXIT_FAILURE);
        }
        buf[buf_i++] = c;
    } while(!done);

    // End string with \0
    buf[buf_i] = '\0';
    chem->name = strdup(buf); // copy into chemical structure
    return chem;
}

void print_reaction(reaction *r) {
    for(int j = 0; j < r->n_inputs; j++) {
        print_chemical(r->inputs[j]);

        if(j < r->n_inputs-1) {
            printf(", ");
        }
    }
    printf(" => %ld %s", r->output->amount, r->output->name);
}

void print_chemical(chemical *c) {
    printf("%ld %s", c->amount, c->name);
}

chemical *copy_chemical(chemical *c) {
    chemical *new = malloc(sizeof(chemical));
    new->name = strdup(c->name);
    new->amount = c->amount;
    return new;
}