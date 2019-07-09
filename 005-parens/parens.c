#define _GNU_SOURCE

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
    an array is valid if:
        for all x[0], x[1]...x[i]
            x[i] < i
        and
        for all x[i]
            x[i+1] >= x[i]

    for length 3, there are 5 valid arrays:
        0 0 0
        0 0 1
        0 0 2
        0 1 1
        0 1 2

illustration using full-on trees

0 0 0
<<< >>>
      r
     / \
    o   o
   / \
  o   o
 / \
o   o


0 0 1
<<><>>
    r
   / \
  o   o
 / \
o   o
   / \
  o   o



0 0 2
<<>><>
     r
   /   \
  o     o
 / \   / \
o   o o   o


0 1 1
<><<>>
  r
 / \
o   o
   / \
  o   o
 / \
o   o


0 1 2
<> <> <>
  r
 / \
o   o
   / \
  o   o
     / \
    o   o
*/

/* this function changes the array in-place.
   it either advances it to the next valid state and returns true
   or it returns false (when there are no more valid states)

    this function will be call C(n) times, where C is the function that returns the catalan number at n
 */

int current_index; // use global for fastiness
bool next_valid_array(int * array, int length) {
    int end = length-1;

    while (current_index > 0) {
        if (array[current_index] < current_index) {
            array[current_index]++;
            return true;
        } else {
            current_index--;
            if (array[current_index] < current_index) {
                array[current_index]++;
                for (int i = current_index+1; i < length; i++) {
                    array[i] = array[current_index];
                }
                current_index = end;
                return true;
            }
        }
    }
    return false;
}

int * first_valid_array(int input) {
    int * array = calloc(input, sizeof(int));
    current_index = input - 1;
    return array;
}

void draw_array(int * array, int length) {
    int current_count = 0;

    for (int i = 0; i < length; ) {
        if (array[i] == current_count) {
            putchar_unlocked('<');
            i++;
        } else {
            while (array[i] > current_count) {
                putchar_unlocked('>');
                current_count++;
            }
        }
    }

    while (current_count < length) {
        putchar_unlocked('>');
        current_count++;
    }

    putchar_unlocked('\n');
}

void fail(void) {
    puts("argument must be a natural number");
    exit(EXIT_FAILURE);
}


int get_input(const char* arg) {
    char * status = NULL;

    long input = strtol(arg, &status, 10);

    if ('\0' != *status) {
        fail();
    }

    if (input < 1) {
        fail();
    }

    if (input > INT_MAX) {
        puts("wtf why");
        fail();
    }

    return (int) input;
}

int main(int argc, char * args[]) {
    if (argc < 2) {
        puts("argument required.");
        fail();
    }

    int input = get_input(args[1]);

    int * array = first_valid_array(input);

    draw_array(array, input);

    while (next_valid_array(array, input)) {
        draw_array(array, input);
    }

    return 0;
}
