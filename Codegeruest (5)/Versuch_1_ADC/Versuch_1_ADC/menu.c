#include "menu.h"

#include "adc.h"
#include "bin_clock.h"
#include "lcd.h"
#include "led.h"
#include "os_input.h"

#include <avr/io.h>
#include <stdint.h>

/*!
 *  Hello world program.
 *  Shows the string 'Hello World!' on the display.
 */
void helloWorld(void) {
// Repeat until ESC gets pressed

    while((os_getInput &= 0b00001000) >> 3 == 0b00000000){  //solange wie esc nicht gedrückt wird 
        lcd_line1();
        lcd_writeString("Hello World!");    //Schreibe String
        _delay_ms(500); //warte 500ms
        lcd_clear(); //lösche Zeichenkette
        _delay_ms(500); //warte 500ms
    }
    showMenu();
}

/*!
 *  Shows the clock on the display and a binary clock on the led bar.
 */
void displayClock(void) {
    while((os_getInput &= 0b00001000) >> 3 == 0b00000000){
    uint16_t clockVal = 0b1111111111111111 && (((uint16_t) getTimeHours() <<12) ||  ((uint16_t)getTimeMinutes() <<8) || ((uint16_t)getTimeSeconds())); 
    setLedBar(clockVal);

    char minuteString[2];
    char sekundeString[2];
    char stundeString[2];
    char milliString[3];
    char uhrzeit[12];
    sprintf(minuteString, "%d", getTimeMinutes());
    sprintf(sekundeString,"%d", getTimeSeconds());
    sprintf(stundeString,"%d",getTimeHours());
    char null[] = "0";
    char nullnull[] = "00";
    if(getTimeMinutes() < 10) {
        minuteString = strcat(null,minuteString);
    }
    if(getTimeSeconds() <10){
        sekundeString = strcat(null,sekundeString);
    }
    if(getTimeHours() <10 ){
        stundeString = strcat(null,stundeString);
    }
    if(getTimeMilliseconds()<10){
        milliString = strcat(nullnull,milliString);
    }else if(getTimeMilliseconds()<100){
        milliString = strcat(null,milliString);
    }
    strcat(uhrzeit,stundeString);
    strcat(uhrzeit,":");
    strcat(uhrzeit, minuteString);
    strcat(uhrzeit, ":");
    strcat(uhrzeit, sekundeString);
    strcat(uhrzeit, ":");
    strcat(uhrzeit,milliString);
    lcd_writeString(uhrzeit);
}
}

/*!
 *  Shows the stored voltage values in the second line of the display.
 */
void displayVoltageBuffer(uint8_t displayIndex) {
#warning IMPLEMENT STH. HERE
}

/*!
 *  Shows the ADC value on the display and on the led bar.
 */
void displayAdc(void) {
#warning IMPLEMENT STH. HERE
}

/*! \brief Starts the passed program
 *
 * \param programIndex Index of the program to start.
 */
void start(uint8_t programIndex) {
    // Initialize and start the passed 'program'
    switch (programIndex) {
        case 0:
            lcd_clear();
            helloWorld();
            break;
        case 1:
            activateLedMask = 0xFFFF; // Use all LEDs
            initLedBar();
            initClock();
            displayClock();
            break;
        case 2:
            activateLedMask = 0xFFFE; // Don't use LED 0
            initLedBar();
            initAdc();
            displayAdc();
            break;
        default:
            break;
    }

    // Do not resume to the menu until all buttons are released
    os_waitForNoInput();
}

/*!
 *  Shows a user menu on the display which allows to start subprograms.
 */
void showMenu(void) {
    uint8_t pageIndex = 0;

    while (1) {
        lcd_clear();
        lcd_writeProgString(PSTR("Select:"));
        lcd_line2();

        switch (pageIndex) {
            case 0:
                lcd_writeProgString(PSTR("1: Hello world"));
                break;
            case 1:
                lcd_writeProgString(PSTR("2: Binary clock"));
                break;
            case 2:
                lcd_writeProgString(PSTR("3: Internal ADC"));
                break;
            default:
                lcd_writeProgString(PSTR("----------------"));
                break;
        }

        os_waitForInput();
        if (os_getInput() == 0b00000001) { // Enter
            os_waitForNoInput();
            start(pageIndex);
        } else if (os_getInput() == 0b00000100) { // Up
            os_waitForNoInput();
            pageIndex = (pageIndex + 1) % 3;
        } else if (os_getInput() == 0b00000010) { // Down
            os_waitForNoInput();
            if (pageIndex == 0) {
                pageIndex = 2;
            } else {
                pageIndex--;
            }
        }
    }
}
