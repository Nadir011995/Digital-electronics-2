/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/

#define LED_RED    PC0
#define LED_GREEN  PB5    
#define LED_YELLOW PB4 
#define LED_ORANGE PB3 
#define LED_BLUE   PB2 
#define BTN		   PD0


#define BLINK_DELAY 500
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif


/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions


/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle two LEDs 
 * when a push button is pressed.
 */
int main(void)
{
   
    
    DDRB = DDRB | (1<<LED_GREEN);
	DDRB = DDRB | (1<<LED_ORANGE); 
	DDRB = DDRB | (1<<LED_BLUE);
    DDRB = DDRB | (1<<LED_YELLOW);
    DDRC = DDRC | (1 << LED_RED );  
   	
	  
	PORTB = PORTB & ~(1<<LED_GREEN);
    PORTB = PORTB & ~(1<<LED_ORANGE);
    PORTB = PORTB & ~(1<<LED_BLUE);
   	PORTB = PORTB & ~(1<<LED_YELLOW);
	PORTC = PORTC & ~(1<<LED_RED);   
	   
	   
	   DDRD = DDRD & ~(1<<BTN); //Turn OFF
	   PORTD = PORTD | (1<<BTN);
 
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
    
//1	
if (bit_is_clear(PIND, BTN))
	{
		PORTC=PORTC ^ (1<<LED_RED);
		_delay_ms(BLINK_DELAY);
		PORTC = PORTC & ~(1<<LED_RED);
	}
//2		 
if (bit_is_clear(PIND, BTN))
	{
		PORTB=PORTB ^ (1<<LED_GREEN);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
	}
//3
if (bit_is_clear(PIND, BTN))
{
		PORTB=PORTB ^ (1<< LED_YELLOW);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB & ~(1<<LED_YELLOW);
}
//4
if (bit_is_clear(PIND, BTN))
{
		PORTB=PORTB ^ (1<< LED_ORANGE);
		 _delay_ms(BLINK_DELAY);
		 PORTB = PORTB & ~(1<<LED_ORANGE);
}
//5
if (bit_is_clear(PIND, BTN))
{
		 PORTB=PORTB ^ (1<< LED_BLUE);
		 _delay_ms(BLINK_DELAY);
		 PORTB = PORTB & ~(1<<LED_BLUE);
}
//4		 
if (bit_is_clear(PIND, BTN))
{
		PORTB=PORTB ^ (1<< LED_ORANGE);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB & ~(1<<LED_ORANGE);
}
//3		  
if (bit_is_clear(PIND, BTN))
{
		PORTB=PORTB ^ (1<< LED_YELLOW);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB & ~(1<<LED_YELLOW);
}
//2			
if (bit_is_clear(PIND, BTN))
{
		PORTB=PORTB ^ (1<<LED_GREEN);
		_delay_ms(BLINK_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
}
_delay_ms(50);



	
	}
    // Will never reach this
    return 0;
}