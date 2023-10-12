#include "datatypes.h"

#include "lcd.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void loop(void){
    uint8_t result =0;
    for(uint8_t i = 5; i >= 0; i--){
        result += i* 2+2;
    }
    lcd_writeProgString(PSTR("LOOp finished:"));
    lcd_writeDec(result);
}
