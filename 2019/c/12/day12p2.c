/*
 * Advent of Code 2019 day 12 part 2
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

unsigned long lcm_2(unsigned long n1, unsigned long n2);
unsigned long lcm_3(unsigned long n1, unsigned long n2, unsigned long n3);
unsigned long gcd_2(unsigned long n1, unsigned long n2);
State *file_get_state(FILE *infile);
Moon *file_get_moon(FILE *infile);
Vector_3D file_get_vector(FILE *infile);
void print_state(State *s);
void print_vector(Vector_3D v);
void print_moon(Moon *m);
void update_velocities(Moon *m1, Moon *m2);
void update_position(Moon *m);
State *state_copy(State *s);
Moon *moon_copy(Moon *m);
int compare_states(State *s1, State *s2, int axis);
int compare_moons(Moon *m1, Moon *m2, int axis);
int compare_vetors(Vector_3D v1, Vector_3D v2, int axis);

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    // Get starting state
    State *starting_state = file_get_state(infile);
    fclose(infile);
    
    State *current_state = state_copy(starting_state);

    unsigned long time_steps = 0;
    const unsigned long max_time_steps = 1000000000000000;
    unsigned long x_steps = 0, y_steps = 0, z_steps = 0;
    while(1) {
        // If all have been found
        if(x_steps > 0 && y_steps > 0 && z_steps > 0) {
            break;
        }
        
        if(time_steps >= max_time_steps) {
            fprintf(stderr, "Too many time steps\n");
            exit(EXIT_FAILURE);
        }
        
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
        
        time_steps++;
        
        //printf("State after %ld steps:\n", time_steps);
        //print_state(current_state);
        
        // Compare to starting state
        if(x_steps == 0) {
            if(compare_states(starting_state, current_state, 0)) {
                x_steps = time_steps;
                //printf("X repeated after %ld steps\n", x_steps);
            }
        }
        if(y_steps == 0) {
            if(compare_states(starting_state, current_state, 1)) {
                y_steps = time_steps;
                //printf("Y repeated after %ld steps\n", y_steps);
            }
        }
        if(z_steps == 0) {
            if(compare_states(starting_state, current_state, 2)) {
                z_steps = time_steps;
                //printf("Z repeated after %ld steps\n", z_steps);
            }
        }
    }
    
    printf("System state repeated after %ld steps\n", lcm_3(x_steps,y_steps,z_steps));
    
    return 0;
}

unsigned long lcm_3(unsigned long n1, unsigned long n2, unsigned long n3) {
    return lcm_2(lcm_2(n1,n2),n3);
}

unsigned long lcm_2(unsigned long n1, unsigned long n2) {
    unsigned long lcm, gcd;

    gcd = gcd_2(n1,n2);

    lcm = (n1*n2) / gcd;
    return lcm;
}

unsigned long gcd_2(unsigned long n1, unsigned long n2) {
    unsigned long temp;
    
    while (n2 != 0) {
        temp = n2;
        n2 = n1 % n2;
        n1 = temp;
    }
    return n1;
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

State *state_copy(State *s) {
    State *new = malloc(sizeof(State));
    if(new == NULL) {
        perror("state_copy malloc state");
        exit(EXIT_FAILURE);
    }
    
    new->moons = malloc(sizeof(Moon*) * N_MOONS);
    if(new->moons == NULL) {
        perror("state_copy malloc moons");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < N_MOONS; i++) {
        new->moons[i] = moon_copy(s->moons[i]);
    }
    return new;
}

Moon *moon_copy(Moon *m) {
    Moon *new = malloc(sizeof(Moon));
    if(new == NULL) {
        perror("moon_copy (new)");
        exit(EXIT_FAILURE);
    }
    new->pos = m->pos;
    new->vel = m->vel;
    return new;
}

int compare_states(State *s1, State *s2, int axis) {
    for(int i = 0; i < N_MOONS; i++) {
        if(!compare_moons(s1->moons[i], s2->moons[i], axis)) {
            return 0;
        }
    }
    return 1;
}

int compare_moons(Moon *m1, Moon *m2, int axis) {
    return (compare_vetors(m1->pos, m2->pos, axis) && compare_vetors(m1->vel, m2->vel, axis));
}

int compare_vetors(Vector_3D v1, Vector_3D v2, int axis) {
    int res;
    switch(axis) {
        case 0:
            res = v1.x == v2.x;
            break;
        case 1:
            res = v1.y == v2.y;
            break;
        case 2:
            res = v1.z == v2.z;
            break;
        default:
            fprintf(stderr, "Unknown axis: %d\n", axis);
            exit(EXIT_FAILURE);
            break;
    }
    return res;
}


