

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
    cosnt char *data_pin = "16";
    cosnt char *clk_pin = "21";
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
    const int bits = sizeof(data) * 8;  // antal bitar i input datan 
    unsigned char shifted_data; // håller värdet till  den shifted.
for (int i = 0; i < bits ; i++) // går lika många varv som antal bitar 
{
    shifted_data = (unsigned char) (data >> i);  // skifta biten till höger av i 

    set_reg_byte(shifted_data,true,true); // Skickar datan till reg genom att använda big endian och framåt riktningen 
    usleep(ms_delay * 1000);  // delay och convertera millisekunder till microsekunder. 

}

}
