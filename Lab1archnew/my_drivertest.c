#include "my_drivertest.h"

#define LED_TOTAL_COUNT 8 // Total number of LEDs
#define GPIO_DEVICE_NUMBER 0 // GPIO chip number

int my_shift(unsigned char led_data, const char *gpio_data_pin, const char *gpio_clk_pin, bool is_shift_left) {
    struct gpiod_chip *gpio_chip;
    struct gpiod_line *gpio_data_line;
    struct gpiod_line *gpio_clk_line;
    struct gpiod_line *gpio_latch_line;

    gpio_chip = gpiod_chip_open_by_number(GPIO_DEVICE_NUMBER);
    if (!gpio_chip) {
        perror("Open chip failed");
        return -1;
    }

    gpio_data_line = gpiod_chip_get_line(gpio_chip, atoi(gpio_data_pin));
    gpio_clk_line = gpiod_chip_get_line(gpio_chip, atoi(gpio_clk_pin));
    gpio_latch_line = gpiod_chip_get_line(gpio_chip, 20);
    if (!gpio_data_line || !gpio_clk_line || !gpio_latch_line) {
        perror("Get line failed");
        gpiod_chip_close(gpio_chip);
        return -1;
    }

    gpiod_line_request_output(gpio_data_line, "my_shift", 0);
    gpiod_line_request_output(gpio_clk_line, "my_shift", 0);
    gpiod_line_request_output(gpio_latch_line, "my_shift", 0);

    if (is_shift_left) {
        for (int i = 0; i < 8; i++) {
            gpiod_line_set_value(gpio_data_line, (led_data & 0x80) != 0);
            gpiod_line_set_value(gpio_clk_line, 1);
            usleep(1000);
            gpiod_line_set_value(gpio_clk_line, 0);
            usleep(1000);
            led_data <<= 1;
        }
    } else {
        for (int i = 0; i < 8; i++) {
            gpiod_line_set_value(gpio_data_line, (led_data & 0x01) != 0);
            gpiod_line_set_value(gpio_clk_line, 1);
            usleep(1000);
            gpiod_line_set_value(gpio_clk_line, 0);
            usleep(1000);
            led_data >>= 1;
        }
    }

    gpiod_line_set_value(gpio_latch_line, 1);
    usleep(10);
    gpiod_line_set_value(gpio_latch_line, 0);

    gpiod_line_release(gpio_data_line);
    gpiod_line_release(gpio_clk_line);
    gpiod_line_release(gpio_latch_line);
    gpiod_chip_close(gpio_chip);

    return 0;
}

void my_counter(int delay_ms) {
    for (int i = 0; i <= 255; i++) {
        my_shift(i, "16", "21", false);
        usleep(delay_ms * 1000);
    }
}

void clear_all() {
    unsigned char led_data = 0x00; // All LEDs off
    my_shift(led_data, "16", "21", false);
}

void turn_on_all() {
    unsigned char led_data = 0xFF; // All LEDs on
    my_shift(led_data, "16", "21", false);
}
