#include "my_74hc595_driver.h"

void set_reg_byte(unsigned char *register_pointer, unsigned char data_value, bool is_little_endian, bool is_normal_order) {
    // Set the register bits based on the data value and specified endianess and direction
    if (is_little_endian) {
        if (is_normal_order) {
            *register_pointer = data_value; // Little-endian normal order
        } else {
            *register_pointer = (data_value & 0x01) << 7 | (data_value & 0x02) << 5 | 
                                (data_value & 0x04) << 3 | (data_value & 0x08) << 1 |
                                (data_value & 0x10) >> 1 | (data_value & 0x20) >> 3 |
                                (data_value & 0x40) >> 5 | (data_value & 0x80) >> 7; // Little-endian reverse order
        }
    } else {
        if (is_normal_order) {
            *register_pointer = data_value; // Big-endian normal order
        } else {
            *register_pointer = (data_value & 0x80) >> 7 | (data_value & 0x40) >> 5 | 
                                (data_value & 0x20) >> 3 | (data_value & 0x10) >> 1 |
                                (data_value & 0x08) << 1 | (data_value & 0x04) << 3 |
                                (data_value & 0x02) << 5 | (data_value & 0x01) << 7; // Big-endian reverse order
        }
    }
}

int step_reg_bit(int data_value, int delay_ms) {
    // Validate input as an 8-bit value
    if (data_value < 0 || data_value > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // Return error if out of range
    }

    while (1) {
        printf("%08d\n", data_value); // Display binary representation

        usleep(delay_ms * 1000); // Delay in microseconds

        data_value >>= 1; // Shift the bit one step to the right

        if (data_value == 0) {
            data_value = 0b10000000; // Reset to 10000000
        }
    }

    return 0; // Will not be reached
}
