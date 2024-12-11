// my_drivertest.h
// Abdulmajid Alsisi / Osama Wahbi

#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "my_74hc595_driver.h"

/**
 * Shifts an 8-bit value to the 74HC595 shift register.
 *
 *
 */
int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir);

/**
 * Counts from 0 to 255 and shifts each value to the 74HC595 shift register after every count.
 *
 */
void my_counter(int delay);

/**
 * Clears all LEDs by shifting a value of 0 to the 74HC595 shift register.
 */
void clear_all();

/**
 * Turns on all LEDs by shifting a value of 255 to the 74HC595 shift register.
 */
void turn_on_all();

#endif // MY_DRIVERTEST_H