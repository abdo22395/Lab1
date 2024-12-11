#include <stdio.h>
#include <gpiod.h>
#include <unistd.h>
#include <time.h>
#include "./src/my_drivertest.h"

//const char *gpiochip = "gpiochip0";
unsigned int data_pin = 16;
unsigned int latch_pin = 20;
unsigned int clk_pin = 21;



void main()
{
    unsigned char dpin = (unsigned char)data_pin;
    unsigned char lpin = (unsigned char)latch_pin;
    unsigned char cpin = (unsigned char)clk_pin;
    unsigned char dummy_val = 36;
    unsigned char dummy_val2 = 219;
    int my_delay_ms = 1000;
    
    my_shift(dummy_val, dpin, cpin, 0);
    sleep(5);
    my_shift(dummy_val2, dpin, cpin, 0);
    sleep(5);
    printf("borde ha blinkat \n");
    printf("startar steppern\n");
    int doing_something =  step_reg_bit(dummy_val, my_delay_ms);
}
