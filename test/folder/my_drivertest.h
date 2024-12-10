#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <stdint.h>
#include <stdbool.h>
#include "my_74hc595_driver.h"

// Function declarations
int my_shift(uint8_t data, uint8_t data_pin, uint8_t clk_pin, bool dir);
void my_counter(int delay);
void clear_all();
void turn_on_all();

#endif // MY_DRIVERTEST_H