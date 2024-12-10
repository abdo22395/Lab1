#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"
#include "my_drivertest.h"

int main() {
    // Define GPIO pin numbers
    const char *data_pin = "16"; // Data pin
    const char *clk_pin = "21"; // Clock pin

    // Turn on all LEDs
    printf("Turning on all LEDs...\n");
    turn_on_all();
    usleep(2000000); // Wait for 2 seconds

    // Shift a byte of data to the right
unsigned char data = 0b11111111; // Start with all bits set
printf("Shifting data to the right:\n");
for (int i = 0; i < 8; i++) {
    my_shift(data, data_pin, clk_pin, true); // Shift right
    usleep(1000000); // Wait for 1 second
    data >>= 1; // Shift right
}

// Shift a byte of data to the left
data = 0b00000001; // Start with the least significant bit set
printf("Shifting data to the left:\n");
for (int i = 0; i < 8; i++) {
    my_shift(data, data_pin, clk_pin, true); // Shift left
    usleep(1000000); // Wait for 1 second
    data <<= 1; // Shift left
}

    // Clear all LEDs
    printf("Clearing all LEDs...\n");
    clear_all();

    void my_counter(10);
    clear_all();

    return 0;
}
