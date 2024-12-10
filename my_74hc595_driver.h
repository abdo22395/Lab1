// my_74hc595_driver.h
#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_8bit_lib.h"

// Function declarations
void set_reg_byte(unsigned char data, bool endian, bool dir);
int step_reg_bit(int data, int ms_delay);

#endif // MY_74HC595_DRIVER_H
