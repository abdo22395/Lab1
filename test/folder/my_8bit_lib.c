#include "my_8bit_lib.h"

// Function to flip a specific bit in a bit string of unknown size
void my_flip(void *data, int bit) {
    uint8_t *byte_ptr = (uint8_t *)data; // Cast the void pointer to a uint8_t pointer
    int byte_index = bit / 8;             // Determine which byte to modify
    int bit_index = bit % 8;              // Determine which bit in that byte

    // Flip the specific bit using XOR
    byte_ptr[byte_index] ^= (1 << bit_index);
}