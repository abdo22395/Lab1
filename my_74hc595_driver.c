#include "my_74hc595_driver.h"

v#include "my_74hc595_driver.h"

void set_reg_byte(unsigned char data, bool endian, bool dir) {
     const char *data_pin = "16"; // Data pin
     const char *clk_pin = "21"; // Clock pin
    // This function sets the register according to the bit arrangement in "data"
    unsigned char reg = 0; // Initialize the register

    if (endian) {
        // Little-endian: set bits in order from least to most significant
        if (dir) {
            // Normal order
            reg = data; // Directly assign data to reg
        } else {
            // Reverse order
            reg = (data & 0x01) << 7 | (data & 0x02) << 5 | (data & 0x04) << 3 | (data & 0x08) << 1 |
                  (data & 0x10) >> 1 | (data & 0x20) >> 3 | (data & 0x40) >> 5 | (data & 0x80) >> 7;
        }
    } else {
        // Big-endian: set bits in order from most to least significant
        if (dir) {
            // Normal order
            reg = data; // Directly assign data to reg
        } else {
            // Reverse order
            reg = (data & 0x80) >> 7 | (data & 0x40) >> 5 | (data & 0x20) >> 3 | (data & 0x10) >> 1 |
                  (data & 0x08) << 1 | (data & 0x04) << 3 | (data & 0x02) << 5 | (data & 0x01) << 7;
        }
    }
    my_shift(reg, data_pin, clk_pin, true);
   
}

int step_reg_bit(int data, int ms_delay) {
    // Check that data is an 8-bit value
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // Return an error value
    }

    while (1) {
        // Print the current value of data
        printf("%08d\n", data);

        // Delay in milliseconds
        usleep(ms_delay * 1000); // usleep takes microseconds

        // Shift the bit one step to the right
        data >>= 1;

        // If data becomes 0, reset to 10000000 (1 in the most significant bit)
        if (data == 0) {
            data = 0b10000000; // Reset to 10000000
        }
    }

    return 0; // This will never be reached, but it's good to have
}
