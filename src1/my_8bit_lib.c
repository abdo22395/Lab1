//Abdullah Alhafari, Mustafa Nejm, Grupp18
#include "my_8bit_lib.h"

// Flips a specific bit in the provided data buffer
void my_flip(void *data_pointer, int bit_index) {
    // Cast the generic data pointer to a pointer to an unsigned char (byte)
    unsigned char *byte_pointer = (unsigned char *)data_pointer;

    // Calculate which byte contains the bit to flip and its position within the byte
    int byte_offset = bit_index / 8; // Determine which byte in the buffer
    int bit_offset = bit_index % 8; // Determine the bit's position in the byte

    // Toggle the specified bit using XOR with a mask
    byte_pointer[byte_offset] ^= (1 << bit_offset);
}
