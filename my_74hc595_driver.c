#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void set_reg_byte(unsigned char *reg, unsigned char data, bool endian, bool dir) {
    // Om endian är true, använd little-endian, annars big-endian
    if (endian) {
        // Little-endian: sätt bitarna i ordning från lägsta till högsta
        if (dir) {
            // Sätt bitarna i normal ordning
            *reg = data;
        } else {
            // Sätt bitarna i omvänd ordning
            *reg = (data & 0x01) << 7 | (data & 0x02) << 5 | (data & 0x04) << 3 | (data & 0x08) << 1 |
                    (data & 0x10) >> 1 | (data & 0x20) >> 3 | (data & 0x40) >> 5 | (data & 0x80) >> 7;
        }
    } else {
        // Big-endian: sätt bitarna i ordning från högsta till lägsta
        if (dir) {
            // Sätt bitarna i normal ordning
            *reg = data;
        } else {
            // Sätt bitarna i omvänd ordning
            *reg = (data & 0x80) >> 7 | (data & 0x40) >> 5 | (data & 0x20) >> 3 | (data & 0x10) >> 1 |
                    (data & 0x08) << 1 | (data & 0x04) << 3 | (data & 0x02) << 5 | (data & 0x01) << 7;
        }
    }
}

int step_reg_bit(int data, int ms_delay) {
    // Kontrollera att data är en 8-bitars värde
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // Returnera ett felvärde
    }

    while (1) {
        // Skriv ut det aktuella värdet av data
        printf("%08d\n", data);

        // Fördröjning i millisekunder
        usleep(ms_delay * 1000); // usleep tar mikrosekunder

        // Flytta biten ett steg åt höger
        data >>= 1;

        // Om data blir 0, återställ till 10000000 (1 i den mest signifikanta biten)
        if (data == 0) {
            data = 0b10000000; // Återställ till 10000000
        }
    }

    return 0; // Detta kommer aldrig att nås, men det är bra att ha
}
