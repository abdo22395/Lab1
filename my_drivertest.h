// my_drivertest.h
#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

// Function declarations
int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, const char *latch_pin, bool dir);
void clear_all();
void turn_on_all();

#endif // MY_DRIVERTEST_H
