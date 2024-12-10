
//Abdullah Alhafari, Mustafa Nejm, Grupp18


#include "my_drivertest.h"

// Shifts data to LEDs using GPIO pins and a shift register
int my_shift(unsigned char led_data, const char *gpio_data_pin, const char *gpio_clk_pin, bool is_shift_left) {
    struct gpiod_chip *gpio_chip;
    struct gpiod_line *gpio_data_line;
    struct gpiod_line *gpio_clk_line;
    struct gpiod_line *gpio_latch_line;

    // Open the GPIO chip for interaction
    gpio_chip = gpiod_chip_open_by_number(GPIO_DEVICE_NUMBER);
    if (!gpio_chip) {
        perror("Could not open GPIO chip");
        return -1;
    }

    // Obtain GPIO lines for data, clock, and latch signals
    gpio_data_line = gpiod_chip_get_line(gpio_chip, atoi(gpio_data_pin));
    gpio_clk_line = gpiod_chip_get_line(gpio_chip, atoi(gpio_clk_pin));
    gpio_latch_line = gpiod_chip_get_line(gpio_chip, 20); // Assuming GPIO 20 for latch
    if (!gpio_data_line || !gpio_clk_line || !gpio_latch_line) {
        perror("Failed to get GPIO lines");
        gpiod_chip_close(gpio_chip);
        return -1;
    }

    // Configure the GPIO lines as outputs
    gpiod_line_request_output(gpio_data_line, "the_shift", 0);
    gpiod_line_request_output(gpio_clk_line, "the_shift", 0);
    gpiod_line_request_output(gpio_latch_line, "the_shift", 0);

    // Perform the shift operation
    if (is_shift_left) {
        for (int i = 0; i < 8; i++) {
            gpiod_line_set_value(gpio_data_line, (led_data & 0x80) != 0); // MSB first
            gpiod_line_set_value(gpio_clk_line, 1); // Clock rising edge
            usleep(1000);
            gpiod_line_set_value(gpio_clk_line, 0); // Clock falling edge
            usleep(1000);
            led_data <<= 1; // Shift data left
        }
    } else {
        for (int i = 0; i < 8; i++) {
            gpiod_line_set_value(gpio_data_line, (led_data & 0x01) != 0); // LSB first
            gpiod_line_set_value(gpio_clk_line, 1); // Clock rising edge
            usleep(1000);
            gpiod_line_set_value(gpio_clk_line, 0); // Clock falling edge
            usleep(1000);
            led_data >>= 1; // Shift data right
        }
    }

    // Latch the shifted data to output
    gpiod_line_set_value(gpio_latch_line, 1); // Latch high
    usleep(10);
    gpiod_line_set_value(gpio_latch_line, 0); // Latch low

    // Release GPIO lines and close the chip
    gpiod_line_release(gpio_data_line);
    gpiod_line_release(gpio_clk_line);
    gpiod_line_release(gpio_latch_line);
    gpiod_chip_close(gpio_chip);

    return 0;
}

// Cycles through all possible 8-bit states with a delay
void my_counter(int delay_ms) {
    for (int i = 0; i <= 255; i++) {
        my_shift(i, "16", "21", false); // Output current counter value to LEDs
        usleep(delay_ms * 1000); // Delay for specified time
    }
}

// Turns off all LEDs
void clear_all() {
    unsigned char led_data = 0x00; // All LEDs off
    my_shift(led_data, "16", "21", false);
}

// Turns on all LEDs
void turn_on_all() {
    unsigned char led_data = 0xFF; // All LEDs on
    my_shift(led_data, "16", "21", false);
}
