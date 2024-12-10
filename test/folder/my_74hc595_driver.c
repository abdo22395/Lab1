#include "my_74hc595_driver.h"
#include "my_74hc595_driver.h"

extern struct gpiod_line *data_line;
extern struct gpiod_line *clk_line;
extern struct gpiod_line *latch_line;

void set_reg_byte(uint8_t data, bool endian, bool dir) {
    if (endian) {
        for (int i = 0; i < 8; i++) {
            gpiod_line_set_value(data_line, (data >> i) & 0x01);
            clock_P();
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            gpiod_line_set_value(data_line, (data >> i) & 0x01);
            clock_P();
        }
    }
    latch_P(); // Låsa in data efter skiftning
}


int step_reg_bit(int data, int ms_delay) {
    for (int i = 0; i < 8; i++) {
        gpiod_line_set_value(data_line, (data >> (7 - i)) & 0x01);
        clock_P();
        usleep(ms_delay * 1000); // Delay in microseconds
    }
    return 0; // Return 0 for success
}



void latch_P() {
    gpiod_line_set_value(latch_line, 1); // Sätt latch hög
    usleep(1);                           // Kort fördröjning
    gpiod_line_set_value(latch_line, 0); // Sätt latch låg
}
