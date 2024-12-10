#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "my_74hc595_driver.h"

// Function declarations
int my_shift(unsigned char led_data, const char *gpio_data_pin, const char *gpio_clk_pin, const char *gpio_latch_pin, bool is_shift_left);
void my_counter(int delay_ms);
void clear_all();
void turn_on_all();

#endif // MY_DRIVERTEST_H
