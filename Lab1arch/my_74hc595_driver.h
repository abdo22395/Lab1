#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_8bit_lib.h"

// Function declarations
// Configure a register with specific byte value
void set_reg_byte(unsigned char *register_pointer, unsigned char data_value, bool is_little_endian, bool is_normal_order);
// Shift a bit with delay
int step_reg_bit(int data_value, int delay_ms);

#endif // MY_74HC595_DRIVER_H
