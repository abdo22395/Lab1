

#include <stdio.h>
#include <stdint.h>
#include "my_8bit_lib.h"

void my_flip(void *data, int bit) 
{
    // räknar vilken är biten och vilken är byten
    unsigned char *bytePtr = (unsigned char *)data;
    int byteIndex = bit / 8; // Byten
    int bitIndex = bit % 8;   // Vilkeb bit i en byte

    // flippar biten utan avseende på storleken 
    bytePtr[byteIndex] ^= (1 << bitIndex); 
    
}