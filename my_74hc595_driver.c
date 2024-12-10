#include "my_74hc595_driver.h"

v#include "my_74hc595_driver.h"

void set_reg_byte(unsigned char data, bool endian, bool dir) {
    // This function sets the register according to the bit arrangement in "data"
    unsigned char reg = 0; // Initialize the register

    if (endian) {
        // Little-endian: set bits in order from least to most significant
        if (dir) {
            // Normal order
            reg = data; // Directly assign data to reg
        } else {
            // Reverse order
            reg = (data & 0x01) << 7 | (data & 0x02) << 5 | (data & 0x04) << 3 | (data & 0x08) << 1 |
                  (data & 0x10) >> 1 | (data & 0x20) >> 3 | (data & 0x40) >> 5 | (data & 0x80) >> 7;
        }
    } else {
        // Big-endian: set bits in order from most to least significant
        if (dir) {
            // Normal order
            reg = data; // Directly assign data to reg
        } else {
            // Reverse order
            reg = (data & 0x80) >> 7 | (data & 0x40) >> 5 | (data & 0x20) >> 3 | (data & 0x10) >> 1 |
                  (data & 0x08) << 1 | (data & 0x04) << 3 | (data & 0x02) << 5 | (data & 0x01) << 7;
        }
    }

   // Open the GPIO chip (0 is usually the default chip)
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0); // Change to your GPIO chip number
    if (!chip) {
        perror("Open chip failed");
        return;
    }

    // Get the lines for data, clock, and latch pins
    struct gpiod_line *data_line = gpiod_chip_get_line(chip, atoi(data_pin));
    struct gpiod_line *clk_line = gpiod_chip_get_line(chip, atoi(clk_pin));
    struct gpiod_line *latch_line = gpiod_chip_get_line(chip, atoi(latch_pin));
    if (!data_line || !clk_line || !latch_line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return;
    }

    // Request the lines as output
    gpiod_line_request_output(data_line, "set_reg_byte", 0);
    gpiod_line_request_output(clk_line, "set_reg_byte", 0);
    gpiod_line_request_output(latch_line, "set_reg_byte", 0);

    // Shift out the bits to the shift register
    for (int i = 0; i < 8; i++) {
        // Set data pin to the current bit
        gpiod_line_set_value(data_line, (reg & (1 << (7 - i))) != 0); // MSB first
        // Toggle clock pin
        gpiod_line_set_value(clk_line, 1);
        usleep(1); // Delay for clock cycle
        gpiod_line_set_value(clk_line, 0);
        usleep(1); // Delay for clock cycle
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
}

int step_reg_bit(int data, int ms_delay) {
    // Check that data is an 8-bit value
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // Return an error value
    }

    while (1) {
        // Print the current value of data
        printf("%08d\n", data);

        // Delay in milliseconds
        usleep(ms_delay * 1000); // usleep takes microseconds

        // Shift the bit one step to the right
        data >>= 1;

        // If data becomes 0, reset to 10000000 (1 in the most significant bit)
        if (data == 0) {
            data = 0b10000000; // Reset to 10000000
        }
    }

    return 0; // This will never be reached, but it's good to have
}
