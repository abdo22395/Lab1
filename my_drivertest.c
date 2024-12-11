// my_drivertest.c
// Abdulmajid Alsisi / Osama Wahbi
#include "my_drivertest.h"

#define GPIO_CHIP_NUMBER 0

int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir) {
    struct gpiod_chip *chip;
    struct gpiod_line *data_line;
    struct gpiod_line *clk_line;
    struct gpiod_line *latch_line;

    // oppna gpio chippen
    chip = gpiod_chip_open_by_number(GPIO_CHIP_NUMBER);
    if (!chip) {
         // om error
        perror("Open chip failed");
        return -1;
    }

    // fa linjarna till data, clk och latch pinnen(den ar hardkodad pga funktionens anrop begransningar)
    data_line = gpiod_chip_get_line(chip, atoi(data_pin));
    clk_line = gpiod_chip_get_line(chip, atoi(clk_pin));
    latch_line = gpiod_chip_get_line(chip, 20);
    if (!data_line || !clk_line || !latch_line) {
        // om error
        perror("Get line failed");
        // stanga chippen om error
        gpiod_chip_close(chip);
        return -1;
    }

    // fa linjerna som output
    gpiod_line_request_output(data_line, "my_shift", 0);
    gpiod_line_request_output(clk_line, "my_shift", 0);
    gpiod_line_request_output(latch_line, "my_shift", 0);

    if (dir) {
        // Shifta vanster
        for (int i = 0; i < 8; i++) {
            // skicka datan till MSB
            gpiod_line_set_value(data_line, (data & 0x80) != 0);
            // Toggla clock pin
            gpiod_line_set_value(clk_line, 1);
            usleep(1000); // Delay for clock cycel
            gpiod_line_set_value(clk_line, 0);
            usleep(1000); // Delay for clock cycel
            // Shifta data vanster
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

    // Latcha output
    gpiod_line_set_value(latch_line, 1); // latch hog
    usleep(10); // kort delay
    gpiod_line_set_value(latch_line, 0); // lathc lag

    // slappa linjarna och stanga chippen
    gpiod_line_release(data_line);
    gpiod_line_release(clk_line);
    gpiod_line_release(latch_line);
    gpiod_chip_close(chip);

    return 0; // hurra
}

void my_counter(int delay) {
    for (int i = 0; i <= 255; i++) {
        my_shift(i, "16", "21", true); // shift ut nuvarande vardet
        usleep(delay / 1000); // delay i ms sekunder
    }
}

void clear_all() {
    unsigned char data = 0x00; // All LEDs av
    my_shift(data, "16", "21", false); // shifta ut datan for att slacka leds
}

void turn_on_all() {
    unsigned char data = 0xFF; // All LEDs pa
    my_shift(data, "16", "21", false); // shifta ut datan for att satta pa leds
}
