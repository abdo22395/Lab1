#include <gpiod.h>
#include <stdio.h>
#include <unistd.h> // For usleep

#define LED_COUNT 8 // Number of LEDs
#define GPIO_CHIP_NUMBER 0 // Change to your GPIO chip number

int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir) {
    struct gpiod_chip *chip;
    struct gpiod_line *data_line;
    struct gpiod_line *clk_line;

    // Open the GPIO chip (0 is usually the default chip)
    chip = gpiod_chip_open_by_number(0); // Change to your GPIO chip number
    if (!chip) {
        perror("Open chip failed");
        return -1;
    }

    // Get the lines for data and clock pins
    data_line = gpiod_chip_get_line(chip, atoi(data_pin));
    clk_line = gpiod_chip_get_line(chip, atoi(clk_pin));
    if (!data_line || !clk_line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return -1;
    }

    // Request the lines as output
    gpiod_line_request_output(data_line, "my_shift", 0);
    gpiod_line_request_output(clk_line, "my_shift", 0);

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

    // Release the lines and close the chip
    gpiod_line_release(data_line);
    gpiod_line_release(clk_line);
    gpiod_chip_close(chip);

    return 0; // Indicate success
}

void clear_all() {
    struct gpiod_chip *chip;
    struct gpiod_line *lines[LED_COUNT];
    const int led_pins[LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7}; // Change to your actual GPIO pin numbers

    // Open the GPIO chip
    chip = gpiod_chip_open_by_number(GPIO_CHIP_NUMBER);
    if (!chip) {
        perror("Open chip failed");
        return;
    }

    // Request the lines for the LEDs as output
    for (int i = 0; i < LED_COUNT; i++) {
        lines[i] = gpiod_chip_get_line(chip, led_pins[i]);
        if (!lines[i]) {
            perror("Get line failed");
            gpiod_chip_close(chip);
            return;
        }
        gpiod_line_request_output(lines[i], "clear_all", 0); // Set initial value to 0
    }

    // Set all lines to low (turn off all LEDs)
    for (int i = 0; i < LED_COUNT; i++) {
        gpiod_line_set_value(lines[i], 0);
    }

    // Release the lines and close the chip
    for (int i = 0; i < LED_COUNT; i++) {
        gpiod_line_release(lines[i]);
    }
    gpiod_chip_close(chip);
}

void turn_on_all() {
    struct gpiod_chip *chip;
    struct gpiod_line *lines[LED_COUNT];
    const int led_pins[LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7}; // Change to your actual GPIO pin numbers

    // Open the GPIO chip
    chip = gpiod_chip_open_by_number(GPIO_CHIP_NUMBER);
    if (!chip) {
        perror("Open chip failed");
        return;
    }

    // Request the lines for the LEDs as output
    for (int i = 0; i < LED_COUNT; i++) {
        lines[i] = gpiod_chip_get_line(chip, led_pins[i]);
        if (!lines[i]) {
            perror("Get line failed");
            gpiod_chip_close(chip);
            return;
        }
        gpiod_line_request_output(lines[i], "turn_on_all", 1); // Set initial value to 1 (on)
    }

    // Set all lines to high (turn on all LEDs)
    for (int i = 0; i < LED_COUNT; i++) {
        gpiod_line_set_value(lines[i], 1);
    }

    // Release the lines and close the chip
    for (int i = 0; i < LED_COUNT; i++) {
        gpiod_line_release(lines[i]);
    }
    gpiod_chip_close(chip);
}