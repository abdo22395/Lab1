#ifndef MY_74HC595_DRIVER_H
#define MY_74HC595_DRIVER_H

#include <stdbool.h>
#include <stdint.h>
#include "my_8bit_lib.h"

// Funktion för att ställa in registret enligt data
void set_reg_byte(uint8_t data, bool endian, bool dir);

// Funktion för att stegvis flytta en bit med fördröjning
int step_reg_bit(int data, int ms_delay);

#endif // MY_74HC595_DRIVER_H