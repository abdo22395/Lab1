// my_drivertest.c
// Abdulmajid Alsisi / Osama Wahbi

#include "my_drivertest.h"

#define GPIO_CHIP_NUMBER 0 // GPIO chip number 0 is the default

/**
 * Shifts an 8-bit value to the 74HC595 shift register.
 *
 */
int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir) {
    struct gpiod_chip *chip;
    struct gpiod_line *data_line;
    struct gpiod_line *clk_line;
    struct gpiod_line *latch_line;

    // Open the GPIO chip
    chip = gpiod_chip_open_by_number(GPIO_CHIP_NUMBER);
    if (!chip) {
        perror("Open chip failed"); // Error
        return -1;
    }

    // Get lines for data, clock, and latch pins (hardcoded due to function call limitations)
    data_line = gpiod_chip_get_line(chip, data_pin);
    clk_line = gpiod_chip_get_line(chip, clk_pin);
    latch_line = gpiod_chip_get_line(chip, 20); // Latch pin
    if (!data_line || ! clk_line || !latch_line) {
        perror("Get line failed"); // Error getting lines
        gpiod_chip_close(chip); // Close
        return -1;
    }

    // Set lines as output
    gpiod_line_request_output(data_line, "my_shift", 0);
    gpiod_line_request_output(clk_line, "my_shift", 0);
    gpiod_line_request_output(latch_line, "my_shift", 0);

    if (dir) {
        // Shift left
        for (int i = 0; i < 8; i++) {
            
            gpiod_line_set_value(data_line, (data & 0x80) != 0);
            // Toggle clock pin
            gpiod_line_set_value(clk_line, 1);
            usleep(1000); // Delay for clock cycle
            gpiod_line_set_value(clk_line, 0);
            usleep(1000); // Delay for clock cycle
            // Shift data left
            data <<= 1;
        }
    } else {
        // Shift right
        for (int i = 0; i < 8; i++) {
            
            gpiod_line_set_value(data_line, (data & 0x01) != 0);
            // Toggle clock pin
            gpiod_line_set_value(clk_line, 1);
            usleep(1000); // Delay for clock cycle
            gpiod_line_set_value(clk_line, 0);
            usleep(1000); // Delay for clock cycle
            // Shift data right
            data >>= 1;
        }
    }

    // Latch output to display values on the leds
    gpiod_line_set_value(latch_line, 1); // Latch high
    usleep(10); // Short delay
    gpiod_line_set_value(latch_line, 0); // Latch low

    // Release lines and close chip to minimeze errors
    gpiod_line_release(data_line);
    gpiod_line_release(clk_line);
    gpiod_line_release(latch_line);
    gpiod_chip_close(chip);

    return 0; 
}

/**
 * Counts from 0 to 255 and shifts each value to the 74HC595 shift register after every counting.
 *
 */
void my_counter(int delay) {
    for (int i = 0; i <= 255; i++) {
        my_shift(i, "16", "21", true); // Shift out the current value
        usleep(delay * 1000); // Delay in milliseconds
    }
}

/**
 * Clears all LEDs by shifting a value of 0 to the 74HC595 shift register.
 */
void clear_all() {
    unsigned char data = 0x00; // All LEDs off
    my_shift(data, "16", "21", false); // Shift out data to turn off LEDs
}

/**
 * Turns on all LEDs by shifting a value of 255 to the 74HC595 shift register.
 */
void turn_on_all() {
    unsigned char data = 0xFF; // All LEDs on
    my_shift(data, "16", "21", false); // Shift out data to turn on LEDs
}