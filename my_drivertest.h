// my_drivertest.h
// Abdulmajid Alsisi / Osama Wahbi
#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include "my_74hc595_driver.h"

int my_shift(unsigned char data, const char *data_pin, const char *clk_pin, bool dir);
void my_counter(int delay);
void clear_all();
void turn_on_all();

#endif // MY_DRIVERTEST_H
