#include "my_8bit_lib.h"

void my_flip(void *data_pointer, int bit_index) {
    // Calculate which byte and which bit within that byte to flip
    unsigned char *byte_pointer = (unsigned char *)data_pointer;
    int byte_offset = bit_index / 8; // Determine which byte
    int bit_offset = bit_index % 8; // Determine which bit within the byte

    // Flip the bit using XOR with a mask
    byte_pointer[byte_offset] ^= (1 << bit_offset); // Toggle the specified bit
}
