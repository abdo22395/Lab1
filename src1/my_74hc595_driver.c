
//Abdullah Alhafari, Mustafa Nejm, Grupp18

#include "my_74hc595_driver.h"

// Configures a shift register with a specific byte of data
void set_reg_byte(unsigned char data_value, bool is_little_endian, bool is_normal_order) {
    if (is_little_endian) {
        // Little-endian configuration
        if (is_normal_order) {
            *register_pointer = data_value; // Store data in normal order
        } else {
            // Reverse bit order for little-endian
            *register_pointer = (data_value & 0x01) << 7 | (data_value & 0x02) << 5 |
                                (data_value & 0x04) << 3 | (data_value & 0x08) << 1 |
                                (data_value & 0x10) >> 1 | (data_value & 0x20) >> 3 |
                                (data_value & 0x40) >> 5 | (data_value & 0x80) >> 7;
        }
    } else {
        // Big-endian configuration
        if (is_normal_order) {
            *register_pointer = data_value; // Store data in normal order
        } else {
            // Reverse bit order for big-endian
            *register_pointer = (data_value & 0x80) >> 7 | (data_value & 0x40) >> 5 |
                                (data_value & 0x20) >> 3 | (data_value & 0x10) >> 1 |
                                (data_value & 0x08) << 1 | (data_value & 0x04) << 3 |
                                (data_value & 0x02) << 5 | (data_value & 0x01) << 7;
        }
    }
}

// Implements a step-by-step shift for an 8-bit value with a delay
int step_reg_bit(int data_value, int delay_ms) {
    // Ensure the data value is a valid 8-bit value
    if (data_value < 0 || data_value > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // Return error if input is invalid
    }

    // Loop to shift the data bit by bit
    while (1) {
        printf("%08d\n", data_value); // Display the current bit pattern
        usleep(delay_ms * 1000); // Delay to control shift speed

        data_value >>= 1; // Shift the bit to the right

        if (data_value == 0) {
            data_value = 0b10000000; // Reset to the initial value when all bits are shifted out
        }
    }

    return 0; // Should not reach here
}
