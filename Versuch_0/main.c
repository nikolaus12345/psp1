#include <avr/io.h>
#include "button.h"
#include "led.h"

int main(void) {
	initInput();
	buttonTest();
	led_init();
	return 0;
}
