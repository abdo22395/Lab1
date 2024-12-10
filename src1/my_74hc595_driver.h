
//Abdullah Alhafari, Mustafa Nejm, Grupp18

#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_8bit_lib.h"

// Function declarations for the 74HC595 driver
void set_reg_byte(unsigned char data_value, bool is_little_endian, bool is_normal_order);
int step_reg_bit(int data_value, int delay_ms);

#endif // MY_74HC595_DRIVER_H
