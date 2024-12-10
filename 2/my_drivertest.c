
#include <gpiod.h>
#include "my_74hc595_driver.h"


#define data_pin 16
#define clock_pin 21
#define latch_pin 20

// skickar en byte till reg genom data och clock pinnar 
int my_shift (unsigned byte data, unsigned byte data_pin, unsigned byte clk_pin, bool dir)
{
    
    struct gpiod_chip *chip; // skapar variable för chippen 
    struct gpiod_line *data_line, *clk_line, *latch_line; //varibler för data samt clock pinnar och latch
    int ret = 0; // return värdet 

    chip = gpiod_chip_open("/dev/gpiochip0");  // öpnnar gpio chippet
    if (!chip) // kontrollera om korrekt öppnat 
    {
        perror("gpiod_chip_open"); // fel meddelande om misslyckat 
 
        return -1;
    }
 // hämtar linjer för data och clock pin och latch
    data_line = gpiod_chip_get_line (chip,data_pin);
    clk_line = gpiod_chip_get_line (chip,clk_pin);
    latch_line = gpiod_chip_get_line (chip,20);
    if (!data_line || !clk_line || !latch_line)  // kolla om korrekt hämtade
    {
        perror("ERROR "); 
        gpiod_chip_close(chip); // stänger chippet
        return -1;
    }

gpiod_line_request_output(data_line,"my_shift", 0); // konfigurera linejer som output
gpiod_line_request_output(clk_line,"my_shift", 0); // konfig clock som output
gpiod_line_request_output(latch_line, "my_shift",0); // konfig latch som output

for (int i = 0; i < 8; i++) //för att gå igenom alla 8 bitar 
{
    unsigned byte bit = dir ? (data & (1 << (7-i))) : (data & (1 << i )); //extrahera biten beroende på riktning 
     gpiod_line_set_value(data_line, bit ? 1: 0); // data pinnen till 1 eller 0 
     gpiod_line_set_value(clk_line, 1); // clock puls skickas genom att skicka en hög (1)
     usleep(1); 
     gpiod_line_set_value (clk_line,0);  // klocka låg 
     gpiod_line_set_value (latch_line,1);
     gpiod_line_set_value (latch_line,0);

}

gpiod_line_release(data_line); // frigör resurserna i linjen 
gpiod_line_release(clk_line); // frigör resurserna i clock
gpiod_line_release(latch_line); 
gpiod_chip_close(chip); // stänger chippen 

return ret;  // returnerar framgångsvärdet
}
// sätter alla register till 1 
void turn_on_all() {
    // Pass 255 to my_shift to turn on all bits
    unsigned byte all_on = 255; // Binary 11111111
    my_shift(all_on, "16", "21", true); // Assuming 'true' is the default direction
}


void clear_all() {
    // Pass 0 to my_shift to clear all bits
    unsigned byte all_off = 0; // Binary 00000000
    my_shift(all_off, "16","21", true); // Assuming 'true' is the default direction
}

void my_counter(int delay_ms) {
    // Loop from 0 to 255
    for (unsigned byte i = 0; i <= 255; i++) {
        // Shift out the current value to the shift register
        my_shift(i, "16", "21", true); // Assuming 'true' for the default direction

        // Use usleep for the specified delay (convert milliseconds to microseconds)
        usleep(delay_ms * 1000);
    }
}