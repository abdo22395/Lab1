#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <gpiod.h>
#include <stdint.h>
#include <stdbool.h>
#include "my_8bit_lib.h"

// Function declarations
void set_reg_byte(uint8_t data, bool endian, bool dir);
int step_reg_bit(int data, int ms_delay);

#endif // MY_74HC595_DRIVER_H