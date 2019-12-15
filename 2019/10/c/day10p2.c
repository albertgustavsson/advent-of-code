/*
 * Advent of Code 2019 day 10 part 2
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
    int total_asteroids = 0;
    
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
        
        if(c == '#') total_asteroids++;
        map[x++][y] = (char) c;
    }
    fclose(infile);
    
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
                                    float dir_ = atan2(dy_, dx_);
                                    if(dir_ == dir && dist_ < dist) {
                                        // Found closer asteroid
                                        closer_found = 1;
                                        break;
                                    }
                                }
                                if(closer_found) {
                                    break;
                                }
                            }
                            if(!closer_found) {
                                n++;
                            }
                        }
                    }
                }
                detected[x][y] = n;
            }
        }
    }
    
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
    
    int asteroids_to_vaporize = total_asteroids-1;
    int asteroids_destroyed = 0;
    float laser_dir = -0.5*PI;
    int laser_x = max_x, laser_y = max_y;
    printf("The monitoring station will be placed on the asteroid at %d,%d\n", laser_x, laser_y);
    
    /*
    printf("Map:\n");
    for(y = 0; y < actual_size; y++) {
        for(x = 0; x < actual_size; x++) {
            if(x == laser_x && y == laser_y) {
                printf("X");
            } else {
                printf("%c", map[x][y]);
            }
        }
        printf("\n");
    }
    printf("\n");
    */

    while(asteroids_to_vaporize > 0) {
        // Find next asteroid to vaporize
        int next_x, next_y;
        float next_dir, next_dist;
        float next_diff_dir = 2*PI;
        
        // Find the asteroid that is closest to the laser when rotating clockwise
        int next_found = 0;
        for(y = 0; y < actual_size; y++) {
            for(x = 0; x < actual_size; x++) {
                if(map[x][y] != '#') continue;
                // Ignore the asteroid where the monitoring station is
                if(x == laser_x && y == laser_y) continue;
                
                // Calculate the angle
                int dx = x - laser_x;
                int dy = y - laser_y;
                float dir = atan2(dy,dx);
                
                
                /* Check if the angle is closer to the laser
                 * If no asteroids have been destroyed yet: allow angles that are equal to the lasers angle
                 * otherwise: only allow angles that are not the same angle as the laser's current angle
                 */
                float diff_dir = dir - laser_dir;
                if(diff_dir < next_diff_dir && (diff_dir > 0 || (asteroids_destroyed == 0 && diff_dir >= 0))) {
                    // Update the direction
                    next_x = x;
                    next_y = y;
                    next_dir = dir;
                    next_dist = sqrt(dx*dx+dy*dy);
                    next_diff_dir = diff_dir;
                    next_found = 1;
                }
            }
        }
        
        /* If no asteroid was found with an angle greater than the lasers angle
         * we need to look for smaller angles since the angles are only in the 
         * range (-PI, PI). Because of this the algorithm above cannot rotate
         * further than PI or even less.
         */
        if(!next_found) {
            float min_dir = PI;
            // Find the smallest angle (furthest counterclockwise > -PI)
            for(y = 0; y < actual_size; y++) {
                for(x = 0; x < actual_size; x++) {
                    if(map[x][y] != '#') continue;
                    // Ignore the asteroid where the monitoring station is
                    if(x == laser_x && y == laser_y) continue;
                    
                    // Calculate the angle
                    int dx = x - laser_x;
                    int dy = y - laser_y;
                    float dir = atan2(dy,dx);
                    
                    if(dir < min_dir) {
                        // Update the direction
                        min_dir = dir;
                        next_x = x;
                        next_y = y;
                        next_dir = dir;
                        next_dist = sqrt(dx*dx+dy*dy);
                    }
                }
            }
        }
        
        //printf("Next asteroid to vaporize is i direction %fpi\n", next_dir/PI);
        
        // Check if another asteroid is closer at the same angle
        for(y = 0; y < actual_size; y++) {
            for(x = 0; x < actual_size; x++) {
                if(map[x][y] != '#') continue;
                // Ignore itself
                if(x == laser_x && y == laser_y) continue;
                
                int dx = x - laser_x;
                int dy = y - laser_y;
                float dist = sqrt(dx*dx+dy*dy);
                float dir = atan2(dy,dx);
                if(dir == next_dir && dist < next_dist) {
                    // Found closer asteroid
                    next_x = x;
                    next_y = y;
                    next_dist = dist;
                }
            }
        }
        
        // Vaporize it
        laser_dir = next_dir; // Aim
        map[next_x][next_y] = '.'; // FIRE
        asteroids_destroyed++; // Target defeated.
        asteroids_to_vaporize--;
        
        printf("The %dth asteroid to be destroyed was at %d,%d\n", asteroids_destroyed, next_x, next_y);
        if(asteroids_destroyed == 200) {
            //printf("The 200th asteroid to be destroyed was at %d,%d\n", next_x, next_y);
            //printf("100*x+y = %d\n", 100*next_x+next_y);
        }
    }
    
    return 0;
}