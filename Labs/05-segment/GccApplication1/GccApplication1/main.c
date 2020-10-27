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
uint8_t cnt1 = 0;   // For the second Display we need to add an other global variable 

int main(void)
{	
    // Configure SSD signals
    SEG_init();

    // Test of SSD: display number '3' at position 0
	// SEG_update_shift_regs(3, 0);
 

   
	/* Configure 8-bit Timer/Counter0
     * Set prescaler and enable overflow interrupt */
	
    	TIM0_overflow_4ms();// we set an other timer and each 4ms we change the position
	    TIM0_overflow_interrupt_enable();
     
	/* Configure 16-bit Timer/Counter1
     * Set prescaler and enable overflow interrupt */
		TIM1_overflow_1s();
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

    cnt0++;
	 if(cnt0>=10){
		
		cnt0=0;// we have to reset it when the first Display reached the maximum

		cnt1++; //but in the same time we have to increment the next counter.
	 if(cnt1>=6){
		 
		 cnt1=0; //if the second Display reach the maximum as well it has to be reseted too.
	 } 
	}
}


 ISR(TIMER0_OVF_vect)
 {
	 //  SEG_clear();
 	static uint8_t pos = 0;//we use static variable to keep remember the current position
 	
	 //	uint8_t first_display= 0;
 	 //	uint8_t second_display=1;
		  
	
 		uint8_t display = 0; 
 	if(pos==0)
 	{
 		SEG_update_shift_regs(cnt0,display);
 		pos=1;
 	}
 	else
 	{  
 		display++;
 		SEG_update_shift_regs(cnt1,display);
 		pos=0;
 	}
 	
	 
  
 }
