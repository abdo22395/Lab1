// my_74hc595_driver.h
// Abdulmajid Alsisi / Osama Wahbi
#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"


void set_reg_byte(unsigned char data, bool endian, bool dir) {
     const char *data_PinAB = "16"; // Data pin
     const char *clk_PinAB = "21"; // Clock pin
    // satter registret enligt bittarna
    unsigned char reg = 0; // int reg

    if (endian) {
        // Little-endian: satta bittarna fran minst viktigt to mest viktig
        if (dir) {
            // Normal order
            reg = data; // ass datan till registret
        } else {
            // bakat order
            reg = (data & 0x01) << 7 | (data & 0x02) << 5 | (data & 0x04) << 3 | (data & 0x08) << 1 |
                  (data & 0x10) >> 1 | (data & 0x20) >> 3 | (data & 0x40) >> 5 | (data & 0x80) >> 7;
        }
    } else {
        // Big-endian: motsatsen till little endian
        if (dir) {
            // Normal order
            reg = data; // ass data to registret
        } else {
            // bakat order
            reg = (data & 0x80) >> 7 | (data & 0x40) >> 5 | (data & 0x20) >> 3 | (data & 0x10) >> 1 |
                  (data & 0x08) << 1 | (data & 0x04) << 3 | (data & 0x02) << 5 | (data & 0x01) << 7;
        }
    }
    my_shift(reg, data_PinAB, clk_PinAB, true);
   
}

int step_reg_bit(int data, int ms_delay) {
    // kollar om datan ar 8 bitar varde
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // ERROR
    }

    while (1) {
        // printa vardet av datan
        printf("%08d\n", data);
         my_shift(data, 16, 21, true);

        // Delay i milliseconder
        usleep(ms_delay * 1000); // usleep tar mikrosekonder

        // shifta en steg at hoger
        data >>= 1;

        // om data ar 0, reseta till 10000000 (1 i den mest viktiga bitten)
        if (data == 0) {
            data = 0b10000000; // Reseta till 10000000
        }
    }

    return 0;
}
