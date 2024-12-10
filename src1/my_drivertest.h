//Abdullah Alhafari, Mustafa Nejm, Grupp18

#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "my_74hc595_driver.h"

// Function declarations for LED control and testing
int my_shift(unsigned char led_data, const char *gpio_data_pin, const char *gpio_clk_pin, bool is_shift_left);
void my_counter(int delay_ms); // Outputs all 8-bit patterns with a delay
void clear_all(); // Turns off all LEDs
void turn_on_all(); // Turns on all LEDs

#endif // MY_DRIVERTEST_H
