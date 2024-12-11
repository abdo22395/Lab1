// my_8bit_lib.h
// Abdulmajid Alsisi / Osama Wahbi

#ifndef MY_8BIT_LIB_H
#define MY_8BIT_LIB_H

#include <stdio.h>

/**
 * Flips a single bit in a byte array.
 *
 * This function takes a pointer to a byte array and an index of the bit to flip.
 * It modifies the byte array in place by flipping the specified bit using the XOR operation with a help of a mask.
 *
 */
void my_flip(void *data, int bit);

#endif // MY_8BIT_LIB_H