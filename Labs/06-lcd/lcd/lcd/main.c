/*
 * lcd.c
 *
 * Created: 05.11.2020 18:45:58
 * Author : osman
 */ 
/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function



/* Variables ---------------------------------------------------------*/


uint8_t customChar[] = {
	

	// addr 0: ....
	0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
	// addr 1 |....
	0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
	// addr 2
	0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
	// addr 3
	0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,
	// addr 4
	0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,
	// addr 5
	0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,
	// left bracket for the designing
    0b01111,0b01000, 0b01000, 0b01000, 0b01000, 0b01000, 0b01111, 0b00000,
	// right bracket for the designing
    0b01111, 0b00001, 0b00001, 0b00001, 0b00001, 0b00001, 0b01111, 0b00000

};



/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Put string(s) at LCD display
  	
	
	lcd_command(1 << LCD_CGRAM);
	
	for (uint8_t i = 0; i < 64; i++)
	 {
		 // Store all new chars to memory line by line
		 lcd_data(customChar[i]);
	 }

	 // Set pointer to beginning of CGRAM memory
 	 lcd_command(1 << LCD_DDRAM);
  
	 lcd_gotoxy(1, 0);		// column: 1, line: 0
	 lcd_puts("00:00.0");	// put string: all zero(s)

	 lcd_gotoxy(0,0);
	 lcd_putc(6);
	 lcd_gotoxy(8,0);
	 lcd_putc(7);
	 lcd_gotoxy(11, 1);		// column: 11, row: 1
	 lcd_putc('c');			// put character 'c'
 
 

     // Configure 8-bit Timer/Counter2 for Stopwatch
     // Enable interrupt and set the overflow prescaler to 16 ms

	 TIM2_overflow_16ms();
	 TIM2_overflow_interrupt_enable();

     TIM0_overflow_16ms();
	 TIM0_overflow_interrupt_enable();

     // Enables interrupts by setting the global interrupt mask
     sei();

     // Infinite loop
     while (1)
     {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
     }

     // Will never reach this
     return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * IS R starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */




ISR(TIMER2_OVF_vect)
{
	
	static uint8_t number_of_overflows = 0;
	static uint8_t tens = 0;        // Tenths of a second
	static uint8_t seconds = 0;		// Seconds
	static uint8_t minutes = 0;		// Minutes
	static uint16_t  square_seconds = 0;
	char lcd_string[2] = "00";      // String for converting numbers by itoa()

	

	number_of_overflows++;
	if (number_of_overflows > 5)
	{
		// Do this every 6 x 16 ms = 100 ms
		number_of_overflows = 0;
		tens++;
		
		if(tens > 9)	// If we reach the maximum of the Tenths 
							// then we have to reset and Update seconds
		{
			tens = 0;
			
			seconds++;


			if(seconds < 10)
			{
				
				lcd_gotoxy(4, 0);
				itoa(seconds, lcd_string, 10);
				lcd_putc('0');
				lcd_puts(lcd_string);
				
			}
			else
			{
				lcd_gotoxy(4, 0);
				itoa(seconds, lcd_string, 10);
				lcd_puts(lcd_string);
				
			}
			if (seconds > 59)
			{
				seconds=0;
				
				lcd_gotoxy(4, 0);
				itoa(seconds, lcd_string, 10);
				lcd_puts(lcd_string);
				
				// Update minutes
				minutes++;
					
				if(minutes < 10)
				{
					lcd_gotoxy(1,0);
					lcd_putc('0');
					itoa(minutes, lcd_string, 10);
					lcd_puts(lcd_string);
					
				}
				else
				{
					lcd_gotoxy(1,0);
					itoa(minutes, lcd_string, 10);
					lcd_puts(lcd_string);
				}
				
				if (minutes > 59)
				{
					
					minutes = 0;
					lcd_gotoxy(1,0);
					lcd_puts("00");
					
				}
				
				// Clearing the square of Second
				lcd_gotoxy(12, 0);
				lcd_putc(' ');
				lcd_gotoxy(13, 0);
				lcd_putc(' ');
				lcd_gotoxy(14, 0);
				lcd_putc(' ');
					
				
					
				
			}
			
			
		}
		
		// Displaying the square of seconds
		square_seconds= seconds*seconds;
		lcd_gotoxy(11, 0);
		itoa(square_seconds, lcd_string, 10);
		lcd_puts(lcd_string);
		
		
		// Display hundredths of seconds
		lcd_gotoxy(7, 0);
		// Convert the value in decimal to string
		itoa(tens, lcd_string, 10);
		lcd_puts(lcd_string);
		// Update the tenths of second
		
	}

}



ISR(TIMER0_OVF_vect)
{
	static uint8_t symbol = 0;
	static uint8_t position = 0;
	uint8_t i = 0;


	
	symbol++;
	if(symbol > 5)
	{
		symbol = 0;
		position++;
		if(position > 9)
		{
			position = 0;	
			lcd_gotoxy(1+i,1);	
			while(i < 10) 
			{
				
				lcd_putc(' ');
				i++;
			 }
		}
		
	}
	
	lcd_gotoxy(1 + position, 1);
	lcd_putc(symbol);
	
}

