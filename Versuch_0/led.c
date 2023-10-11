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
	
}