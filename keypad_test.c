#include <msp430.h> 
#include<inttypes.h>

/*
 * main.c
 */

char pressed = '0';
uint8_t ip = 0;

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1DIR = 0x07;
//	P1REN = ~(0x07);
//	P1DIR |=
	P1OUT = 0x07;
//	P1OUT = 0x05;
	while (1) {
		key_pressed();
	}
}

void key_pressed() {
	P1OUT = 0x06;
	ip = (0xF0 & P1IN);
	if (ip == 0xE0) {
		pressed = '1';
		return;
	} else if (ip == 0xD0) {
		pressed = '4';
		return;
	} else if (ip == 0xB0) {
		pressed = '7';
		return;
	} else if (ip == 0x70) {
		pressed = '*';
		return;
	}

	P1OUT = 0x05;
	ip = (0xF0 & P1IN);
	if (ip == 0xE0) {
		pressed = '2';
		return;
	} else if (ip == 0xD0) {
		pressed = '5';
		return;
	} else if (ip == 0xB0) {
		pressed = '8';
		return;
	} else if (ip == 0x70) {
		pressed = '0';
		return;
	}
	P1OUT = 0x03;
	ip = (0xF0 & P1IN);
	if (ip == 0xE0) {
		pressed = '3';
		return;
	} else if (ip == 0xD0) {
		pressed = '6';
		return;
	} else if (ip == 0xB0) {
		pressed = '9';
		return;
	} else if (ip == 0x70) {
		pressed = '#';
		return;
	}else{
		pressed = 'n';
	}
	P1OUT = 0x07;
}
