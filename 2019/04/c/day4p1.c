/*
 * Advent of Code 2019 day 4 part 1
 */

#include <stdio.h>
#include <stdlib.h>

int check_match(int num);

int main(void) {
    
    // input range: 367479-893698
    int lower = 367479;
    int upper = 893698;
    
    int num_matching = 0;
    
    int num = lower;
    
    while(num <= upper) {
        // check for match
        if(check_match(num)) {
            num_matching++;
        }
        num++;
    }
    
    printf("Number of matching passwords: %d\n", num_matching);
    
    return 0;
}

int check_match(int num) {
    int digits[6];
    for(int i = 5; i >= 0; i--) {
        digits[i] = num%10;
        num /= 10;
    }
    
    int adjacent = 0;
    for(int i = 0; i < 6; i++) {
        if(i <= 4 && digits[i] == digits[i+1]) {
            adjacent = 1;
        }
        if(i <= 4 && digits[i] > digits[i+1]) {
            return 0;
        }
    }
    
    return adjacent;
}