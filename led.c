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
    uint8_t hours = (uint8_t)((value &= 0b1111000000000000) >> 8);
    uint8_t minutes = (uint8_t)((value &= 0b0000111111000000) >> 6);
    uint8_t seconds = ~(uint8_t) value &= 0b0000000000111111; 
    
    PINA &= seconds;
    PINA |= 0b11000000;
    PINA &= ~(minutes << 6);
    PIND &= ~(minutes >> 2);
    PIND &= ~(hours << 4);
}
