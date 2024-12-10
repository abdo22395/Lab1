
//Abdullah Alhafari, Mustafa Nejm, Grupp18

#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"
#include "my_drivertest.h"

int main() {
    // Define GPIO pin numbers for data and clock (used for communication with the shift register)
    const char *gpio_data_pin = "16";  // GPIO pin for data
    const char *gpio_clock_pin = "21"; // GPIO pin for clock
    const int time = 10; // Time delay in seconds

    // Turn on all LEDs connected to the shift register
    printf("Turning on all LEDs...\n");
    turn_on_all();
    usleep(2000000); // Wait for 2 seconds

    // Shift a byte of data to the right, lighting LEDs sequentially
    unsigned char led_data = 0b11111111; // Start with all LEDs on
    printf("Shifting data to the right:\n");
    for (int i = 0; i < 8; i++) {
        my_shift(led_data, gpio_data_pin, gpio_clock_pin, true); // Shift right
        usleep(1000000); // Wait for 1 second between shifts
        led_data >>= 1; // Prepare next data pattern by shifting the bits to the right
    }

    // Shift a byte of data to the left, lighting LEDs sequentially in the opposite direction
    led_data = 0b00000001; // Start with the first LED on
    printf("Shifting data to the left:\n");
    for (int i = 0; i < 8; i++) {
        my_shift(led_data, gpio_data_pin, gpio_clock_pin, true); // Shift left
        usleep(1000000); // Wait for 1 second between shifts
        led_data <<= 1; // Prepare next data pattern by shifting the bits to the left
    }

    // Turn off all LEDs
    printf("Clearing all LEDs...\n");
    clear_all();

    // Turn on all LEDs again
    printf("Turning on all LEDs again...\n");
    turn_on_all();
    usleep(2000000); // Wait for 2 seconds

    // Execute a counter sequence, cycling through all possible LED states
    my_counter(time);

    // Turn off all LEDs at the end
    clear_all();
    return 0;
}
