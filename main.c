#include <stdio.h>
#include <gpiod.h>
#include <unistd.h>
#include <time.h>
#include "./src/my_drivertest.h"

//const char *gpiochip = "gpiochip0";
unsigned int data_pin = 17;
unsigned int latch_pin = 27;
unsigned int clk_pin = 22;



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
