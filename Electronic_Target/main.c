#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/twi.h>


int device_id;

void initIO(void) {
    
}

void initWDT(void) {
    
}

void initTimer(void) {
    TCCR1 |= 1 << CS10; //Full Frequency
    TIMSK |= (1 << OCIE1A & 1 << OCIE1B & TOIE1);
}

int main(void) {
	initIO();
    initTimer();
    
	while (1) {
	}
	return 0; // never reached
}
