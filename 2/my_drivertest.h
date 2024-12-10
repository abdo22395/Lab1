#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <stdint.h>
#include <stdbool.h>
#include "my_74hc595_driver.h"

// Funktion för att skifta ut en byte till en datapin
int my_shift(uint8_t data, uint8_t data_pin, uint8_t clk_pin, bool dir);

// Funktion för att räkna från 0 till 255 och visa binärt på registret
void my_counter(int delay);

// Funktion för att sätta registret till 0 (alla LEDs av)
void clear_all(void);

// Funktion för att sätta registret till 255 (alla LEDs på)
void turn_on_all(void);

#endif // MY_DRIVERTEST_H