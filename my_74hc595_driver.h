// my_74hc595_driver.h
// Abdulmajid Alsisi / Osama Wahbi

#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_8bit_lib.h"

/**
 * Sets the 74HC595 shift register to a given byte value.
 *
 */
void set_reg_byte(unsigned char data, bool endian, bool dir);

/**
 * Steps the 74HC595 shift register through a sequence of values.
 *
 */
int step_reg_bit(int data, int ms_delay);

#endif // MY_74HC595_DRIVER_H