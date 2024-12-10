#include "my_drivertest.h"

#define LED_COUNT 8 // Number of LEDs
#define GPIO_CHIP_NUMBER 0 // Change to your GPIO chip number

int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir) {
    struct gpiod_chip *chip;
    struct gpiod_line *data_line;
    struct gpiod_line *clk_line;
    struct gpiod_line *latch_line;

    // Open the GPIO chip (0 is usually the default chip)
    chip = gpiod_chip_open_by_number(GPIO_CHIP_NUMBER);
    if (!chip) {
        perror("Open chip failed");
        return -1;
    }

    // Get the lines for data, clock, and latch pins
    data_line = gpiod_chip_get_line(chip, atoi(data_pin));
    clk_line = gpiod_chip_get_line(chip, atoi(clk_pin));
    latch_line = gpiod_chip_get_line(chip, 20);
    if (!data_line || !clk_line || !latch_line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return -1;
    }

    // Request the lines as output
    gpiod_line_request_output(data_line, "my_shift", 0);
    gpiod_line_request_output(clk_line, "my_shift", 0);
    gpiod_line_request_output(latch_line, "my_shift", 0);

    if (dir) {
        // Shift left
        for (int i = 0; i < 8; i++) {
            // Set data pin to the MSB
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
            // Set data pin to the LSB
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

    // Latch the output
    gpiod_line_set_value(latch_line, 1); // Set latch pin high
    usleep(10); // Short delay
    gpiod_line_set_value(latch_line, 0); // Set latch pin low

    // Release the lines and close the chip
    gpiod_line_release(data_line);
    gpiod_line_release(clk_line);
    gpiod_line_release(latch_line);
    gpiod_chip_close(chip);

    return 0; // Indicate success
}

void my_counter(int delay) {
    for (int i = 0; i <= 255; i++) {
        my_shift(i, "16", "21", "20", false); // Shift out the current value
        usleep(delay * 1000); // Delay for the specified time
    }
}

void clear_all() {
    unsigned char data = 0x00; // All LEDs off
    my_shift(data, "16", "21", "20", false); // Shift out the data to clear all LEDs
}

void turn_on_all() {
    unsigned char data = 0xFF; // All LEDs on
    my_shift(data, "16", "21", "20", false); // Shift out the data to turn on all LEDs
}
