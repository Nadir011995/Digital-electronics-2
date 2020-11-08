/***********************************************************************
 * 
 * Decimal counter with 7-segment output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "segment.h"        // Seven-segment display library for AVR-GCC


/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Display decimal 
 * counter values on SSD (Seven-segment display) when 16-bit 
 * Timer/Counter1 overflows.
 */

/*Global variable*/


uint8_t cnt0 = 0;	// Decimal counter value
uint8_t cnt1 = 0;

int main(void)
{	
	
	^ // Configure SSD signals
		SEG_init();


 
     /* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
		TIM1_overflow_262ms();
		TIM1_overflow_interrupt_enable();
   

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
 * ISR starts when Timer/Counter1 overflows. Increment decimal counter
 * value and display it on SSD.
 */

ISR(TIMER1_OVF_vect)	
{
	//snake on one Display  
	cnt0++;
	if (cnt0>=6)  // if we reach the 6 segment the counter gets the value 0 and from that point will start again!
	 
	cnt0=0;
    SEG_update_shift_regs(cnt0,0);

}
