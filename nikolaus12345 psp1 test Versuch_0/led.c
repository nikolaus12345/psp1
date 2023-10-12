#include "button.h"
#include "led.h"
#include "lcd.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void led_init(void){
	DDRD |= 0b11111111;
	PORTD |= 0b11111111;
}
void led_fun(void){
	while(true){
		if(getInput() &= 0b00000001 == 0b00000001){ //prüft ob 1. button gedrückt wurde
			if(PORTD &= 0b00000001 == 0b00000001){  // gucke ob licht aus
				PORTD &= 0b11111110;//licht an
			}
			if(PORTD |= 0b11111110 == 0b11111110){ //guck ob licht an
				PORTD |= 0b00000001; // licht aus
			}
		}
	
		if(getInput() &= 0b00000010 == 0b00000010){
			if(PORTD >>7 == 0b00000001){
				PORTD <<1;
				PORTD |= 0b00000001;
			}
			else{
				PORTD <<1;
			}
		}
	}
		if(getInput() &= 0b00000100 == 0b00000100){
			~ PORTD
		}
}