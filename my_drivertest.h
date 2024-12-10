#ifndef MY_DRIVERTEST_H
#define MY_DRIVERTEST_H

#include <stdint.h>
#include <stdbool.h>
#include <gpiod.h>
#include "my_74hc595_driver.h"

// Funktion för att skifta ut en byte till en datapin
int my_shift( unsigned int data, const int  data_pin, const int clk_pin, bool dir);

// Funktion för att räkna från 0 till 255 och visa binärt på registret
void my_counter(int delay);

// Funktion för att sätta registret till 0 (alla LEDs av)
void clear_all();

// Funktion för att sätta registret till 255 (alla LEDs på)
void turn_on_all();

#endif // MY_DRIVERTEST_H