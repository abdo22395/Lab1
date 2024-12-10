#include <stdio.h>

void my_flip(void *data, int bit) {
    // Beräkna vilken byte och vilken bit inom den byten som ska flipas
    unsigned char *bytePtr = (unsigned char *)data;
    int byteIndex = bit / 8; // Hela byten
    int bitIndex = bit % 8;   // Specifik bit inom byten

    // Flippar biten genom att använda XOR med en mask
    bytePtr[byteIndex] ^= (1 << bitIndex);
}