#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"
#include "my_drivertest.h"

int main() {
    // Define GPIO pin numbers (constants for pin configuration)
    const char *gpio_data_pin = "16";  // GPIO pin for data
    const char *gpio_latch_pin = "20"; // GPIO pin for latch
    const char *gpio_clock_pin = "21"; // GPIO pin for clock

    // Turn on all LEDs
    printf("Turning on all LEDs...\n");
    turn_on_all(); // Function to turn all LEDs on
    usleep(2000000); // Wait for 2 seconds

    // Shift a byte of data to the right
    unsigned char led_data = 0b11111111; // Start with all bits set (all LEDs on)
    printf("Shifting data to the right:\n");
    for (int i = 0; i < 8; i++) {
        my_shift(led_data, gpio_data_pin, gpio_clock_pin, gpio_latch_pin, true); // Shift right
        usleep(1000000); // Wait for 1 second
        led_data >>= 1; // Right-shift data for the next iteration
    }

    // Shift a byte of data to the left
    led_data = 0b00000001; // Start with the least significant bit set
    printf("Shifting data to the left:\n");
    for (int i = 0; i < 8; i++) {
        my_shift(led_data, gpio_data_pin, gpio_clock_pin, gpio_latch_pin, true); // Shift left
        usleep(1000000); // Wait for 1 second
        led_data <<= 1; // Left-shift data for the next iteration
    }

    // Clear all LEDs
    printf("Clearing all LEDs...\n");
    clear_all(); // Function to turn all LEDs off

    return 0;
}
