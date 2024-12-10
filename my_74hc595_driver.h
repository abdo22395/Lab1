// my_74hc595_driver.h
#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// Function declarations
int step_reg_bit(int data, int ms_delay);
void set_reg_byte(unsigned char *reg, unsigned char data, bool endian, bool dir);

#endif // MY_74HC595_DRIVER_H
