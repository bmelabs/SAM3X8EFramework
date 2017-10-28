#include <xc.h>
#include <string.h>
#include "definitions.h"

void initCommand(char theCommand) {
    LCDCOMMAND = theCommand; //put command on PORTD
    RS = RS_COMMAND; // Select Command Register
    RWn = WRITE; // Write Mode
    E = 1;
    //delay(1); 				 //enable pulse width >= 300ns
    E = 0; //Clock enable: falling edge
}

void delay1ms(void) {
    unsigned int i;
    for (i = 0; i < 68; i++) {
    }
}

void delay(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {
        delay1ms();
    }
}

void waitForNotBusy(void) {
    unsigned char BF;
    RS = RS_COMMAND; // Select Command Register
    RWn = READ; // Read Mode
    BF = 0b10000000;
    TRISD = 0b11111111;
    while (BF == 0b10000000) {
        delay(1); //wait at least 80us before reading busy flag
        E = 1;      // Enable reading
        BF = LCDDATA & 0b10000000;
        E = 0;      // Disable reading
    }
    TRISD = 0b00000000;
}

void writeChar(char theData) {
    waitForNotBusy();
    LCDDATA = theData; //put data on PORTD
    RS = RS_DATA; // Select Data Register
    RWn = WRITE; // Write Mode
    E = 1; //enable pulse width >= 300ns
    E = 0; //Clock enable: falling edge
}

void writeString(char * theString) {
    unsigned char i;
    for (i = 0; i < strlen(theString); i++) {
        waitForNotBusy();
        LCDDATA = theString[i]; //put data on PORTD
        RS = RS_DATA; // Select Data Register
        RWn = WRITE; // Write Mode
        E = 1; //enable pulse width >= 300ns
        E = 0; //Clock enable: falling edge
    }
}

void command(char theCommand) {
    waitForNotBusy();
    LCDCOMMAND = theCommand; //put command on PORTD
    RS = RS_COMMAND; // Select Command Register
    RWn = WRITE; // Write Mode
    E = 1;
    //delay(1); 				 //enable pulse width >= 300ns
    E = 0; //Clock enable: falling edge
}

void clearDisplay(void) {
    command(0x01); //Clear Display
}

void returnHome(void) {
    command(0x02); //Return Home
}

void setDisplayLine(unsigned char line, unsigned char position) {

    switch (line) {
        case 1:
            command(0b10000000);
            break;
   
        case 2:
            command(0b11000000);
            break;
            
    }
    if (position > 0){
        for(signed char i=0;i<position;i++){ 
        command(0b00010100);
        }
    }
    else if (position < 0){
        for(signed char i=0;i>position;i--){ 
        command(0b00010000);
        }
    }
}


void LCDInit(void) {
    E = 0;
    delay(15); //Wait >15 msec after power is applied
    initCommand(0x30); //command 0x30 = Wake up
    delay(5); //must wait 5ms, busy flag not available
    initCommand(0x30); //command 0x30 = Wake up #2
    delay(1); //must wait 160us, busy flag not available
    initCommand(0x30); //command 0x30 = Wake up #3
    delay(1); //must wait 160us, busy flag not available
    command(0x38); //Function set: 8-bit/2-line
    command(0x10); //Cursor shift mode, S/C to the Left
    command(0x0C); //1DCB: Display ON; Cursor OFF; Blink OFF
    command(0x06); //Entry mode: Inc cursor and display shift off
    clearDisplay();
    returnHome();
}
