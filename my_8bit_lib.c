// my_8bit_lib.c
// Abdulmajid Alsisi / Osama Wahbi

#include "my_8bit_lib.h"

void my_flip(void *data, int bit) {
    // kalkylera vilekn bit i byten f;r att flippa
    unsigned char *byte_PtrAB = (unsigned char *)data;
    int byte_IAB = bit / 8; // hel byte
    int bit_IAB = bit % 8;   // hel bittar

    // flippa bitten med anv'ndning av XOR och en mask
    byte_PtrAB[byte_IAB] ^= (1 << bit_IAB);
}
