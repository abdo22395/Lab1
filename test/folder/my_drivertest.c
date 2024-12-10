#include "my_drivertest.h"
#include "my_74hc595_driver.h"
#include <unistd.h>

int my_shift(uint8_t data, uint8_t data_pin, uint8_t clk_pin, bool dir) {
    for (int i = 0; i < 8; i++) {
        if (dir) {
            // Shift out from least significant bit to most significant bit
            gpiod_line_set_value(data_line, (data >> i) & 0x01);
        } else {
            // Shift out from most significant bit to least significant bit
            gpiod_line_set_value(data_line, (data >> (7 - i)) & 0x01);
        }
        clock_P(); // Pulse the clock
    }
    return 0; // Return 0 for success
}

void my_counter(int delay) {
    for (uint8_t i = 0; i < 256; i++) {
        set_reg_byte(i, true, true); // Set register with current count
        usleep(delay * 1000); // Delay in microseconds
    }
}

void clear_all() {
    set_reg_byte(0x00, true, true); // Set the register to 0 (all LEDs off)
}

void turn_on_all() {
    set_reg_byte(0xFF, true, true); // Set the register to 255 (all LEDs on)
}