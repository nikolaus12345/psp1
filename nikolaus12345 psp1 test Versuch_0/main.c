#include <avr/io.h>
#include "button.h"
#include "led.h"
#include "lcd.h"


int main(void) {
	initInput();
	buttonTest();
	led_init();
	lcd_init();
	return 0;
}
