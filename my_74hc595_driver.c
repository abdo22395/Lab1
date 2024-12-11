// my_74hc595_driver.c
// Abdulmajid Alsisi / Osama Wahbi

#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"

/**
 * Sets the 74HC595 shift register to a given byte value.
 *
 */
void set_reg_byte(unsigned char data, bool endian, bool dir) {
    // Define the GPIO pins connected to the 74HC595
    const char *data_PinAB = "16"; // Data pin
    const char *clk_PinAB = "21"; // Clock pin
    unsigned char reg = 0; // Register to hold the shifted data

    // Set the register according to the bits
    if (endian) {
        // Little-endian: set bits from least significant to most significant
        if (dir) {
            // Normal order
            reg = data; // Assign data to the register
        } else {
            // Reversed order
            reg = (data & 0x01) << 7 | (data & 0x02) << 5 | (data & 0x04) << 3 | (data & 0x08) << 1 |
                  (data & 0x10) >> 1 | (data & 0x20) >> 3 | (data & 0x40) >> 5 | (data & 0x80) >> 7;
        }
    } else {
        // Big-endian: opposite of little-endian
        if (dir) {
            // Normal order
            reg = data; // Assign data to the register
        } else {
            // Reversed order
            reg = (data & 0x80) >> 7 | (data & 0x40) >> 5 | (data & 0x20) >> 3 | (data & 0x10) >> 1 |
                  (data & 0x08) << 1 | (data & 0x04) << 3 | (data & 0x02) << 5 | (data & 0x01) << 7;
        }
    }
    my_shift(reg, data_PinAB, clk_PinAB, true); // Shift the register with the prepared data
}

/**
 * Steps the 74HC595 shift register through a sequence of values.
 *
 */
int step_reg_bit(int data, int ms_delay) {
    // Check if the data is an 8-bit value otherwise error
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; 
    }

    while (1) {
        // Print the current value of the data
        printf("%08d\n", data);
        my_shift(data, 16, 21, true); // Shift out the current value to the register

        // Delay in milliseconds
        usleep(ms_delay * 1000);

        // Shift one step to the right
        data >>= 1;

        // If data is 0, reset to 10000000 (1 in the most significant bit)
        if (data == 0) {
            data = 0b10000000; // Reset to 10000000
        }
    }

    return 0;
}