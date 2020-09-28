/*
							Author : Nadir Osman Al-Wattar
*/
#define LED_GREEN PB5    // AVR pin where green LED is connected
#define SHORT_DELAY 1000  // Delay in milliseconds
#define LONG_DELAY 3000
#define SPACE 3000
#ifndef  F_CPU
#define F_CPU 16000000   // CPU frequency in Hz required for delay
#endif
#include <util/delay.h>  // Functions for busy-wait delay loops
#include <avr/io.h>

                                           
void dot()
{
	PORTB = PORTB | (1<<LED_GREEN); // Turn ON LED PB5
	
	_delay_ms(SHORT_DELAY);
	PORTB = PORTB & ~(1<<LED_GREEN); //LED off
	//_delay_ms(SHORT_DELAY); // Delay between two symbols
}

void dash()
{
	PORTB = PORTB | (1<<LED_GREEN); // LED on
	_delay_ms(LONG_DELAY);
	PORTB = PORTB & ~(1<<LED_GREEN); // LED off
	//_delay_ms(SHORT_DELAY); 
}

void space()// Delay between two letters
{
	PORTB = PORTB & ~(1<<LED_GREEN); //LED off
	_delay_ms(SPACE);
}

void D()
{
	dash();
	_delay_ms(SHORT_DELAY);
	dot();
	_delay_ms(SHORT_DELAY);
	dot();
	
}

void E()
{
	dot();

}

void two()
{
	dot();
	_delay_ms(SHORT_DELAY);// Delay between two symbols
	dot();
	_delay_ms(SHORT_DELAY);// Delay between two symbols
	dash();
	_delay_ms(SHORT_DELAY);// Delay between two symbols
	dash();
	_delay_ms(SHORT_DELAY);// Delay between two symbols
	dash();
}

int main(void)
{
	// DDRB = DDRB or 0010 0000
    // DDRB = 0b00100000 ; // set the pin 5 '1'
	 DDRB = DDRB | (1<<LED_GREEN); //Set pin as output in Data Direction Register

	// PORTB = PORTB and 1101 1111
	PORTB = PORTB & ~(1<<LED_GREEN); //LED off
		
		while (1)
		{	         	
			D(),space(),E(),space(),two(),_delay_ms(7000);  //(DE2 = -.. . ..---       )
        }
	return 0;  // Will never reach this
}

