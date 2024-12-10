

#include <stdio.h>
#include <stdint.h>

void my_flip(uint8_t *data, int bit )
{
    // data är pointer till bit-strängen
// bit är indexen av biten som ska flippas 
    if (bit < 0 || bit > 7 )
    {
        return 0;
    }

*data ^= (1 << bit); 
}