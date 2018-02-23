#include <msp430.h> 
#include<inttypes.h>

/*
 * main.c
 */
int i = 0;
char arr[301];
volatile uint8_t seed = 0xAE;
volatile uint8_t bits = 0x2D;
volatile uint8_t no = 0;
char a1;
char a2;
//uint8_t rv = 0;
volatile int value;

uint8_t lfsr() {
	volatile char num = seed & bits;
	volatile char ctr = 0;
	int i = 0;
	for (; i < 8; ++i) {
		ctr += (num & 0x01);
		num = num>>1;
	}
	ctr = ctr<<7;
	seed = seed>>1;
	seed = (seed | ctr);
	value = seed;
//	a1 = (0x0F & value);
//	a2 = value>>4;
	return value;
}

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

//	TACCR0 = 0x00FF;
//    TA1CCTL0 |= CCIE;
//	TA1CTL = TASSEL_2 + MC_1 + TACLR;
	while(1)
	{
		unsigned int i = 0;
		for(;i<301;++i){
			arr[i] = lfsr();
		}
	}
	return 0;
}
