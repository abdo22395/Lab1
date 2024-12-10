
#include <gpiod.h>
#include "my_74hc595_driver.h"

#define LED_COUNT 8
#define DATA_PIN 16
#define CLK_PIN 21
#define LATCH_PIN 20
#define GPIO_CHIP_NUMBER 0

// skickar en byte till reg genom data och clock pinnar 
int my_shift (unsigned int data, const int data_pin, const int clk_pin, bool dir)
{
    
    struct gpiod_chip *chip; // skapar variable för chippen 
    struct gpiod_line *data_line, *clk_line, *latch_line; //varibler för data samt clock pinnar och latch
    int ret = 0; // return värdet 

    chip = gpiod_chip_open(GPIO_CHIP_NUMBER);  // öpnnar gpio chippet
    if (!chip) // kontrollera om korrekt öppnat 
    {
        perror("ERROR OPENING CHIP"); // fel meddelande om misslyckat 
 
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

if (dir) {
    // om riktningen är vänster

    for (int i = 0; i < 8; i++) //för att gå igenom alla 8 bitar
    {
        gpiod_line_set_value (data_line,(data & 0x80) != 0 ); // data pinnen till 1 eller 0 

     gpiod_line_set_value(clk_line, 1); // clock puls skickas genom att skicka en hög (1)
     usleep(1000);
     gpiod_line_set_value (clk_line,0);  // klocka låg 
    usleep(1000);

    data <<= 1; 
    }
}
else 
{
    //om riktning är på höger 
    for (int i = 0; i < 8; i++) //för att gå 
    
    {
        gpiod_line_set_value (data_line,(data & 0x80) !=0 )
           gpiod_line_set_value(clk_line, 1); // clock puls skickas genom att skicka en hög (1)
     usleep(1000);
     gpiod_line_set_value (clk_line,0);  // klocka låg 
    usleep(1000);

    data >> = 1; 

    }


}

     gpiod_line_set_value (latch_line,1); //latch hög 
     gpiod_line_set_value (latch_line,0); // latch låg 

    

    gpiod_line_release(data_line); // frigör resurserna i linjen 
    gpiod_line_release(clk_line); // frigör resurserna i clock
    gpiod_line_release(latch_line); // frigör latch 
    gpiod_chip_close(chip); // stänger chippen 

    return ret;  // returnerar framgångsvärdet
}




// sätter alla register till 1 
void turn_on_all() {
    // Pass 255 to my_shift to turn on all bits
    int all_on = 255; // Binary 11111111
    my_shift(all_on, "16", "21", false ); // Assuming 'true' is the default direction
}


void clear_all() {
    // Pass 0 to my_shift to clear all bits
   int all_off = 0; // Binary 00000000
    my_shift(all_off, "16","21", false); // Assuming 'true' is the default direction
}

void my_counter(int delay_ms) {
    // Loop from 0 to 255
    for ( int i = 0; i <= 255; i++) {
        // Shift out the current value to the shift register
        my_shift(i, "16", "21", true); // Assuming 'true' for the default direction

        // Use usleep for the specified delay (convert milliseconds to microseconds)
        usleep(delay_ms * 1000);
    }
}