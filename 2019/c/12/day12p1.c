/*
 * Advent of Code 2019 day 12 part 1
 */

#include <stdio.h>
#include <stdlib.h>

#define N_MOONS 4

typedef struct Vector_3D {
    int x, y, z;
} Vector_3D;

typedef struct Moon {
    Vector_3D pos, vel;
} Moon;

typedef struct State {
    Moon **moons;
} State;

State *file_get_state(FILE *infile);
Moon *file_get_moon(FILE *infile);
Vector_3D file_get_vector(FILE *infile);
void print_state(State *s);
void print_moon(Moon *m);
void print_vector(Vector_3D v);
void update_velocities(Moon *m1, Moon *m2);
void update_position(Moon *m);
unsigned int get_state_energy(State *s);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    // Get starting state
    State *current_state = file_get_state(infile);
    fclose(infile);
    
    const int time_steps = 1000;
    for(int t = 0; t < time_steps; t++) {
        /*
        const int print_interval = 10;
        if(t % print_interval == 0) {
            printf("After %d steps:\n", t);
            print_state(current_state);
            printf("\n");
        }
        */
        
        for(int i = 0; i < N_MOONS; i++) {
            for(int j = i+1; j < N_MOONS; j++) {
                // Update the velocities of both moons
                update_velocities(current_state->moons[i], current_state->moons[j]);
            }
        }
        
        for(int i = 0; i < N_MOONS; i++) {
            // Update moon i's position
            update_position(current_state->moons[i]);
        }
    }
    
    printf("After %d steps:\n", time_steps);
    print_state(current_state);
    printf("\n");
    
    // Calculate energy
    printf("Energy after %d steps:\n", time_steps);
    unsigned int system_total = get_state_energy(current_state);
    
    printf("Total energy in the system: %d\n", system_total);
    
    return 0;
}

void print_state(State *s) {
    for(int i = 0; i < N_MOONS; i++) {
        print_moon(s->moons[i]);
    }
}

void print_moon(Moon *m) {
    printf("Pos: ");
    print_vector(m->pos);
    printf(", ");
    printf("Vel: ");
    print_vector(m->vel);
    printf("\n");
}

void print_vector(Vector_3D v) {
    printf("x=%3d, y=%3d, z=%3d", v.x, v.y, v.z);
}

State *file_get_state(FILE *infile) {
    State *s = malloc(sizeof(State));
    if(s == NULL) {
        perror("file_get_state (s)");
        exit(EXIT_FAILURE);
    }
    
    s->moons = malloc(sizeof(Moon*) * N_MOONS);
    if(s->moons == NULL) {
        perror("file_get_state (s->moons)");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < N_MOONS; i++) {
        s->moons[i] = file_get_moon(infile);
    }
    return s;
}

Moon *file_get_moon(FILE *infile) {
    Moon *m = malloc(sizeof(Moon));
    if(m == NULL) {
        perror("file_get_moon (m)");
        exit(EXIT_FAILURE);
    }
    m->pos = file_get_vector(infile);
    m->vel.x = 0;
    m->vel.y = 0;
    m->vel.z = 0;
    return m;
}

Vector_3D file_get_vector(FILE *infile) {
    Vector_3D v = {0,0,0};
    if(fscanf(infile, "<x=%d, y=%d, z=%d>\n", &v.x, &v.y, &v.z) != 3) {
        fprintf(stderr, "Could not read position\n");
        exit(EXIT_FAILURE);
    }
    return v;
}

void update_velocities(Moon *m1, Moon *m2) {
    // Update x
    if(m1->pos.x < m2->pos.x) {
        m1->vel.x+=1;
        m2->vel.x-=1;
    } else if(m1->pos.x > m2->pos.x) {
        m1->vel.x-=1;
        m2->vel.x+=1;
    }
    
    // Update y
    if(m1->pos.y < m2->pos.y) {
        m1->vel.y+=1;
        m2->vel.y-=1;
    } else if(m1->pos.y > m2->pos.y) {
        m1->vel.y-=1;
        m2->vel.y+=1;
    }
    
    // Update z
    if(m1->pos.z < m2->pos.z) {
        m1->vel.z+=1;
        m2->vel.z-=1;
    } else if(m1->pos.z > m2->pos.z) {
        m1->vel.z-=1;
        m2->vel.z+=1;
    }
}

void update_position(Moon *m) {
    m->pos.x += m->vel.x;
    m->pos.y += m->vel.y;
    m->pos.z += m->vel.z;
}

unsigned int get_state_energy(State *s) {
    unsigned int system_total = 0;
    for(int i = 0; i < N_MOONS; i++) {
        Moon *m = s->moons[i];
        int pot, kin, tot;
        pot = abs(m->pos.x) + abs(m->pos.y) + abs(m->pos.z);
        kin = abs(m->vel.x) + abs(m->vel.y) + abs(m->vel.z);
        tot = pot * kin;
        system_total += tot;
        printf("pot: %d,  kin: %d,  tot: %d\n", pot, kin, tot);
    }
    return system_total;
}