#include "led.h"

#include <avr/io.h>

uint16_t activateLedMask = 0xFFFF;

/*!
 *  Initializes the led bar. Note: All PORTs will be set to output.
 */
void initLedBar(void) {
    DDRA |= 0b00000001;
    DDRD |= 0b00001000;
    PORTA |= 0b11111111;
    PORTD |= 0b11111111;
}

/*!
 *  Sets the passed value as states of the led bar (1 = on, 0 = off).
 */
void setLedBar(uint16_t value) { 
    uint8_t hours = (uint8_t)((value &= 0b1111000000000000) >> 7);
    uint8_t minutes1 = (uint8_t)((value &= 0b0000111100000000) >> 8);
    uint8_t minutes2 = (uint8_t) (value &= 0b0000000011000000 )
    uint8_t seconds = (uint8_t) (value &= 0b0000000000111111); 
    
    PINA = ~(seconds || minutes2) ;
    PIND = ~(minutes1 || hours);

}
