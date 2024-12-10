// main.c
#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>
#include "my_drivertest.h"

#define DATA_PIN 16  // Pin 16 for data
#define LATCH_PIN 20 // Pin 20 for latch
#define CLK_PIN 21   // Pin 21 for clock

struct gpiod_chip *chip;
struct gpiod_line *data_line;
struct gpiod_line *latch_line;
struct gpiod_line *clk_line;

void setup() {
    // Open the GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("Failed to open GPIO chip");
        return;
    }

    // Get the lines for data, latch, and clock
    data_line = gpiod_chip_get_line(chip, DATA_PIN);
    latch_line = gpiod_chip_get_line(chip, LATCH_PIN);
    clk_line = gpiod_chip_get_line(chip, CLK_PIN);

    // Request the lines as outputs
    gpiod_line_request_output(data_line, "my_program", 0);
    gpiod_line_request_output(latch_line, "my_program", 0);
    gpiod_line_request_output(clk_line, "my_program", 0);
}

void cleanup() {
    // Release the lines and close the chip
    gpiod_line_release(data_line);
    gpiod_line_release(latch_line);
    gpiod_line_release(clk_line);
    gpiod_chip_close(chip);
}

int main() {
    setup();

    // Test: Turn on all LEDs
    printf("Turning on all LEDs...\n");
    turn_on_all();
    usleep(2000000); // Wait for 2 seconds

    // Test: Clear all LEDs
    printf("Clearing all LEDs...\n");
    clear_all();
    usleep(2000000); // Wait for 2 seconds

    // Test: Count from 0 to 255
    printf("Counting from 0 to 255...\n");
    my_counter(100); // 100 ms delay between counts

    // Test: Step through bits
    printf("Stepping through bits...\n");
    step_reg_bit(0b11111111, 100); // Start with all LEDs on

    // Final clear
    printf("Final clear...\n");
    clear_all();

    cleanup();
    return 0;
}