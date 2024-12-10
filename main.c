#include "my_74hc595_driver.h"
#include "my_8bit_lib.h"
#include "my_drivertest.h"

int main() {
    // Define GPIO pin numbers
    const char *data_pin = "16"; // Data pin
    const char *clk_pin = "21"; // Clock pin
    const int delay = 10;

    // Turn on all LEDs
    printf("Turning on all LEDs...\n");
    turn_on_all();
    usleep(2000000); // Wait for 2 seconds

/*    // Shift a byte of data to the right
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
*/
/*
    // Test with different data values
    printf("Testing set_reg_byte with different values:\n");

    // Test with all bits set (0xFF)
    printf("Setting register to 0xFF (All LEDs ON):\n");
    set_reg_byte(0xFF, true, true );
    usleep(2000000); // Wait for 2 seconds

    // Test with alternating bits (0xAA)
    printf("Setting register to 0xAA (Alternating ON):\n");
    set_reg_byte(0xAA, true, true );
    usleep(2000000); // Wait for 2 seconds

    // Test with a single bit set (0x01)
    printf("Setting register to 0x01 (Only first LED ON):\n");
    set_reg_byte(0x01, true, true );
    usleep(2000000); // Wait for 2 seconds

    // Test with no bits set (0x00)
    printf("Setting register to 0x00 (All LEDs OFF):\n");
    set_reg_byte(0x00, true, true );
    usleep(2000000); // Wait for 2 seconds
    
    // Clear all LEDs
    printf("Clearing all LEDs...\n");
    clear_all();

    turn_on_all();
    usleep(2000000);

    my_counter(delay);
    clear_all();*/

    turn_on_all();

    unsigned char *data_to_flip = 0b11111111;

    my_flip(data_to_flip, 3);

    return 0;
}
