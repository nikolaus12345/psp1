#include "os_input.h"

#include <avr/io.h>
#include <stdint.h>

/*! \file

Everything that is necessary to get the input from the Buttons in a clean format.

*/

/*!
 *  A simple "Getter"-Function for the Buttons on the evaluation board.\n
 *
 *  \returns The state of the button(s) in the lower bits of the return value.\n
 *  example: 1 Button:  -pushed:   00000001
 *                      -released: 00000000
 *           4 Buttons: 1,3,4 -pushed: 000001101
 *
 */
uint8_t os_getInput(void) {
    uint8_t pinState1 = (~PINC & 0b00000001); 
		uint8_t pinState2 = (~PINC & 0b00000010) ;
		uint8_t pinState3 = (~PINC & 0b01000000) >>4;
		uint8_t pinState4 = (~PINC & 0b10000000) >>4;
		uint8_t pinStateFinal = ( (pinState4 ) || (pinState3)||(pinState2)||pinState1 );
		return pinStateFinal;		 
}


/*!
 *  Initializes DDR and PORT for input
 */
void os_initInput() {
    DDRC &= 0b00111100;
	PORTC |= 0b11000011;
}

/*!
 *  Endless loop as long as at least one button is pressed.
 */
void os_waitForNoInput() {
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
void os_waitForInput() {
    bool input = false;
	while(!input){
		if(getInput() != 0b00000000){
			input = true;
		}
	}
}
