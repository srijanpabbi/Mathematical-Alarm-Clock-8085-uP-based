#include <msp430.h> 
#include <inttypes.h>

#define CS BIT0
#define AS BIT1
#define WR BIT2
#define RD BIT3
#define RST BIT4
#define IRQ BIT5
#define RCLR BIT6
#define SQW BIT7
#define R_A 0x0A
#define R_B 0x0B
#define R_SEC 0x00
#define R_SEC_A 0x01
#define R_MIN 0x02
#define R_MIN_A 0x03
#define R_HR 0x04
#define R_HR_A 0x05
#define R_DAY_WEEK 0x06
#define R_DAY_MONTH 0x07
#define R_MO 0x08
#define R_YR 0x09

#define oscillator 0x20
#define rtc_rb 0x82


//unsigned char add;
volatile int rdata;
//unsigned char wdata;

void read(unsigned char raddress);
void write(unsigned char waddress, unsigned char wdata);

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P2DIR &= 0x00;
	P2DIR |= CS + AS + WR + RD + RST + RCLR;
	P2OUT &= ~AS;
	P2OUT |= WR + RD + RST + RCLR;

	//write(R_B, 0x87);
	//write(R_SEC , 0x32);
	//write(R_MIN , 0x28);
	//write(R_HR , 0x14);
	//write(R_DAY_WEEK, 0x01);
	//write(R_DAY_MONTH, 0x0B);
	//write(R_MO, 0x02);
	//write(R_YR, 0x12);
	//write(R_YR , 18);
	//write(R_B , 0x07);

	while(1)
	{
		read(R_DAY_WEEK);
		read(R_DAY_MONTH);
		read(R_MO);
		read(R_YR);
		read(R_HR);
		read(R_MIN);
		read(R_SEC);
		read(R_B);
	};

}

void read(unsigned char raddress)
{
	P2OUT |= AS;
	P1DIR = 0xFF;
	P1OUT = raddress;
	__delay_cycles(1);
	P2OUT &= ~CS;
	P2OUT &= ~AS;
	__delay_cycles(1);
	P2OUT &= ~RD;
	__delay_cycles(1);
	P1DIR = 0x00;
	rdata = P1IN;
	__delay_cycles(1);
	P2OUT |= RD;
	P2OUT |= CS;
}

void write(unsigned char waddress, unsigned char wdata)
{
	P2OUT |= AS;
	P1DIR = 0xFF;
	P1OUT = waddress;
	__delay_cycles(1);
	P2OUT &= ~CS;
	P2OUT &= ~AS;
	__delay_cycles(1);
	P2OUT &= ~WR;
	P1OUT = wdata;
	__delay_cycles(1);
	P2OUT |= WR;
	P2OUT |= CS;

}
