#include "button.h"

#include "lcd.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*! \file

Everything that is necessary to get the input from the Buttons in a clean format.

*/

/*!
 *  A simple "Getter"-Function for the Buttons on the evaluation board.\n
 *
 *  \returns The state of the button(s) in the lower bits of the return value.\n
 *  Example: 1 Button:  -pushed:   00000001
 *                      -released: 00000000
 *           4 Buttons: 1,3,4 -pushed: 00001101
 */
uint8_t getInput(void) {
		uint8_t pinState1 = (PINC & 0b00000001); 
		uint8_t pinState2 = (PINC & 0b00000010) >>1;
		uint8_t pinState3 = (PINC & 0b01000000) >>6;
		uint8_t pinState4 = (PINC & 0b10000000) >>7;
		uint8_t pinStateFinal = ( (pinState4 <<3) || (pinState3<<2)||(pinState2<<1)||pinState1 );
				pinStateFinal = ~pinStateFinal ;
				pinStateFinal = pinStateFinal & 0b00001111;
		return pinStateFinal;		 
}

/*!
 *  Initializes DDR and PORT for input
 */
void initInput(void) {
	DDRC &= 0b00111100;
	PORTC |= 0b11000011;
}

/*!
 *  Endless loop as long as at least one button is pressed.
 */
void waitForNoInput(void) {
	bool noInput = false;
	while(!noInput){
		if(getInput() == 0b00000000){
			noInput = true;
		}
	}	
}

/*!
 *  Endless loop until at least one button is pressed.
 */
void waitForInput(void) {
	bool input = false;
	while(!input){
		if(getInput() != 0b00000000){
			input = true;
		}
	}
}

/*!
 *  Tests all button functions
 */
void buttonTest(void) {
    // Init everything
    initInput();
    lcd_init();
    lcd_clear();
    lcd_writeProgString(PSTR("Initializing\nInput"));
    _delay_ms(1000);
    lcd_clear();
    if ((DDRC & 0b11000011) != 0) {
        lcd_writeProgString(PSTR("DDR wrong"));
        while (1) continue;
    } else {
        lcd_writeProgString(PSTR("DDR OK"));
        _delay_ms(1000);
    }

    lcd_clear();
    if ((PORTC & 0b11000011) != 0b11000011) {
        lcd_writeProgString(PSTR("Pullups wrong"));
        while (1) continue;
    } else {
        lcd_writeProgString(PSTR("Pullups OK"));
        _delay_ms(1000);
    }

    // Test all 4 buttons
    for (uint8_t i = 0; i < 4; i++) {
        lcd_clear();
        lcd_writeProgString(PSTR("Press Button "));
        lcd_writeDec(i + 1);
        uint8_t pressed = 0;
        while (!pressed) {
            waitForInput();
            uint8_t buttonsPressed = getInput();
            if (buttonsPressed != 1 << i) { // Not the right button pressed so show which ones were pressed and wait for release
                lcd_line2();
                lcd_writeProgString(PSTR("Pressed: "));
                lcd_writeHexByte(buttonsPressed);
                waitForNoInput();
                lcd_line2();
                lcd_writeProgString(PSTR("                "));
            } else { // Right button pressed so wait for release and continue to next one
                pressed = 1;
                lcd_clear();
                lcd_writeProgString(PSTR("Release Button "));
                lcd_writeDec(i + 1);
                waitForNoInput();
            }
        }
    }
    lcd_clear();
    lcd_writeProgString(PSTR("Test passed"));
    while (1) continue;
}
