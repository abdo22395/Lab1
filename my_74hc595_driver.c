

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include "my_8bit_lib.h"
#include "my_74hc595_driver.h"

 // data är byten som ska skickas till registret 
 // endian är byteordning true för little endian(LSB) och false för big (MSB)
// dir är variablen för riktning där true är höger och false är vänster
void set_reg_byte(unsigned char data, bool endian, bool dir)
{
    const char *data_pin = "16";
    const char *clk_pin = "21";
    unsigned char result = 0;
    if (endian) // Least significant bit 
     {
        for (int i = 0; i < 8 ; i++) { // går igenom alla bitar i byten
        if (dir)  // om riktningen är höger 
        {
            result |= ((data >> i )& 1) << i; // då flytta varje bit i data till rätt plats i resultat
        }
        else // om det är vänster
        {
            result |= ((data << i) & 0x80) >> i; //flytta allt til rätt plats åt vänster
        }
     }
 }
else // MOST SIGNIFICANT BIT 
{ // om big-endian valt byten justeras beroende på riktning 
    if (dir) // 
{
result = data >> 1; // flyttrar alla bitar ett steg höger
}
else 
{
result << 1; // annars flytta allt till vänster 
}
my_shift(result,data_pin,clk_pin,true); 

}
}

int step_reg_bit(int data, int ms_delay)
{
    if (data < 0 || data > 255) {
        printf("Data must be an 8-bit value (0-255).\n");
        return -1; // ERROR
    }
while (1) {
        // printa vardet av datan
        printf("%08d\n", data);

        // Delay i milliseconder
        usleep(ms_delay * 1000); // usleep tar mikrosekonder

        // shifta en steg at hoger
        data >>= 1;

        // om data ar 0, reseta till 10000000 (1 i den mest viktiga bitten)
        if (data == 0) {
            data = 0b10000000; // Reseta till 10000000
        }
    }

    return 0;
}
