#include "my_8bit_lib.h"

void my_flip(void *data, int bit) {
    // Calculate which byte and which bit within that byte to flip
    unsigned char *bytePtr = (unsigned char *)data;
    int byteIndex = bit / 8; // Whole bytes
    int bitIndex = bit % 8;   // Specific bit within the byte

    // Flip the bit using XOR with a mask
    bytePtr[byteIndex] ^= (1 << bitIndex);
}
