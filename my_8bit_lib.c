// my_8bit_lib.c
// Abdulmajid Alsisi / Osama Wahbi

#include "my_8bit_lib.h"

/**
 * Flips a single bit in a byte array.
 *
 * This function calculates the byte index and the bit index within that byte,
 * then uses the XOR operation to flip the specified bit.
 *
 */
void my_flip(void *data, int bit) {
    // Cast the data pointer to a pointer to unsigned char (byte)
    unsigned char *byte_PtrAB = (unsigned char *)data;
    
    // Calculate the byte index and the bit index within that byte
    int byte_IAB = bit / 8; 
    int bit_IAB = bit % 8;   // Determine the specific bit within the byte

    // Flip the specified bit using XOR and a bit mask
    byte_PtrAB[byte_IAB] ^= (1 << bit_IAB);
}