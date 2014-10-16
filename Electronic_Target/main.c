#define RAND_MAX 255
#define BAUD 57600

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/twi.h>
#include <util/setbaud.h>



uint16_t deviceID;
uint8_t pkt[23];
uint64_t time1, time2, time3;
uint8_t o1, o2, o3, o4;

void genPkt(void) {
    uint32_t tmpSum = 0;
    int i;
    pkt[0] = 0xAA;
    pkt[1] = 0xAA;
    pkt[2] = rand();
    pkt[3] = deviceID >> 8;
    pkt[4] = deviceID & 0x00FF;
    for (i = 0; i <= 3; i++) {
        pkt[i+5] = ((uint64_t)time1 >> (i*8)) & 0x000000FF; //Timer1 Bits Breakdown
    }
    for (i = 0; i <= 3; i++) {
        pkt[i+9] = ((uint64_t)time2 >> (i*8)) & 0x000000FF; //Timer2 Bits Breakdown
    }
    for (i = 0; i <= 3; i++) {
        pkt[i+13] = ((uint64_t)time3 >> (i*8)) & 0x000000FF; //Timer3 Bits Breakdown
    }
    for (i=5; i <= 16; i++) {
        tmpSum += pkt[i];
    }
    pkt[17] = tmpSum % 256;
    pkt[18] = (o1 << 6) | (o2 << 4) | (o3 << 2) | (o4);
    pkt[19] = 0;
    pkt[20] = 0;
    tmpSum = 0;
    for (i = 0; i<=20; i++) {
        tmpSum += pkt[i];
    }
    pkt[21] = tmpSum % 256;
    pkt[22] = 0;
}

void initSerial(void) {
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
#if USE_2X
    UCSRA |= (1 << U2X);
#else
    UCSRA &= ~(1 << U2X);
#endif
    UCSRB = (1 << TXEN) | (1 << RXEN);
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0); //8-bit data, 1-bit stop
}

void txByte(uint8_t data) {
    while (~((UCSRA >> UDRE) & 0b00000001));
    UDR = data;
}

void txBlock(void) {
    uint8_t i = 0;
    while (pkt[i]) {
        txByte(pkt[i]);
        i++;
    }
}

void initIO(void) {
    
}

void initWDT(void) {
    
}


int main(void) {
	initIO();
    
	while (1) {
	}
	return 0; // never reached
}
