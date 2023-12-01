/*
 * Advent of Code 2019 day 10 part 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  PI 3.14159265358979323846264338327950288419716939937510

const char *filename = "input.txt";

int main(void) {
    FILE *infile = fopen(filename, "r");
    
    if(infile == NULL) {
        perror(filename);
        return EXIT_FAILURE;
    }
    
    const int max_size = 50;
    char map[max_size][max_size];
    int actual_size = -1;
    
    int c, x = 0, y = 0;
    while((c=fgetc(infile)) != EOF) {
        if(c == '\n') {
            y++;
            actual_size = (actual_size==-1?x:actual_size);
            x = 0;
            continue;
        }
        
        if(x >= max_size) {
            printf("Map array is too small\n");
            return -1;
        }
        map[x++][y] = (char) c;
    }
    fclose(infile);
    
    /*
    printf("Map:\n");
    for(y = 0; y < actual_size; y++) {
        for(x = 0; x < actual_size; x++) {
            printf("%c", map[x][y]);
        }
        printf("\n");
    }
    printf("\n");
    */
    
    int detected[max_size][max_size];
    for(y = 0; y < max_size; y++) {
        for(x = 0; x < max_size; x++) {
            detected[x][y] = 0;
        }
    }

    // Count the number of detectable asteroids for every asteroid
    for(y = 0; y < actual_size; y++) {
        for(x = 0; x < actual_size; x++) {
            // If this is an asteroid
            if(map[x][y] == '#') {
                int n = 0;
                // Check if each asteroid is detectable from this asteroid
                for(int other_y = 0; other_y < actual_size; other_y++) {
                    for(int other_x = 0; other_x < actual_size; other_x++) {
                        // Ignore itself
                        if(other_x == x && other_y == y) continue;
                        // If the other position is an asteroid
                        if(map[other_x][other_y] == '#') {
                            // Check if the asteroid can be seen
                            int dx = other_x - x;
                            int dy = other_y - y;
                            float dist = sqrt(dx*dx+dy*dy);
                            float dir = atan2(dy,dx);
                            
                            //printf("Checking if asteroid at %d,%d can detect asteroid at %d,%d (distance %.3f in direction %.3fpi)\n", x, y, other_x, other_y, dist, dir/PI);
                            
                            // Check if an other asteroid is in the way
                            int closer_found = 0;
                            for(int inter_y = 0; inter_y < actual_size; inter_y++) {
                                for(int inter_x = 0; inter_x < actual_size; inter_x++) {
                                    if(map[inter_x][inter_y] != '#') continue;
                                    // Ignore itself
                                    if(inter_x == x && inter_y == y) continue;
                                    int dy_ = inter_y - y;
                                    int dx_ = inter_x - x;
                                    float dist_ = sqrt(dx_*dx_+dy_*dy_);
                                    float dir_ = atan2(dy_,dx_);
                                    if(dir_ == dir && dist_ < dist) {
                                        // Found closer asteroid
                                        //printf("Found closer asteroid at %d,%d (distance %.3f in direction %.3fpi)\n", inter_x, inter_y, dist_, dir_/PI);
                                        closer_found = 1;
                                        break;
                                    }
                                }
                                if(closer_found) {
                                    break;
                                }
                            }
                            if(!closer_found) {
                                //printf("Asteroid at %d,%d can detect asteroid at %d,%d\n", x, y, other_x, other_y);
                                n++;
                            }
                        }
                    }
                }
                detected[x][y] = n;
            }
        }
    }
    
    /*
    printf("Number of detected asteroids:\n");
    for(y = 0; y < actual_size; y++) {
        for(x = 0; x < actual_size; x++) {
            if(detected[x][y] == 0) {
                printf(".");
            } else {
                printf("%d", detected[x][y]);                
            }
        }
        printf("\n");
    }
    printf("\n");
    */
    
    int max_detected = 0, max_x, max_y;
    for(y = 0; y < actual_size; y++) {
        for(x = 0; x < actual_size; x++) {
            if(detected[x][y]>max_detected) {
                max_detected = detected[x][y];
                max_x = x;
                max_y = y;
            }    
        }
    }
    printf("Asteroid at %d,%d can detect the highest number of asteroids: %d\n", max_x, max_y, max_detected);
    
    return 0;
}