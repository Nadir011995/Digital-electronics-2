/***********************************************************************
 * 
 * Control LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_D1  PB5
#define LED_D2  PB4
#define LED_D3  PB3
#define LED_D4  PB2
#define BIN		0
  
/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "gpio.h"           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle one LED
 * on the Multi-function shield using the internal 8- or 16-bit 
 * Timer/Counter.
 */

uint8_t LEDs_array[4] = {LED_D1,LED_D2,LED_D3,LED_D4};
	int LED= 0;
	int move= 0;
	
int main(void)
{
	int perform=0;
	
    /* Configuration of LED(s) */
  
  
    GPIO_config_output(&DDRB, LEDs_array[0]); // this led is going to blink first.
    GPIO_write_low(&PORTB, LEDs_array[0]);

    GPIO_config_output(&DDRB, LEDs_array[1]);
    GPIO_write_high(&PORTB, LEDs_array[1]);
	
	
	GPIO_config_output(&DDRB, LEDs_array[2]);
	GPIO_write_high(&PORTB, LEDs_array[2]);


	GPIO_config_output(&DDRB, LEDs_array[3]);
	GPIO_write_high(&PORTB, LEDs_array[3]);


	GPIO_config_input_pullup(&DDRD, BIN);

	   	/* Configuration of 16-bit Timer/Counter0
	     * Set prescaler and enable overflow interrupt */
		
			 
  
        // Enables interrupts by setting the global interrupt mask
		sei();
 	

    // Infinite loop
    while (1)
    {
		perform=GPIO_read(&PIND, BIN);

		if(perform==1)// if button is not pressed the Leds will blink slowly!
		{
			TIM1_overflow_1s(); 
			TIM1_overflow_interrupt_enable();
	  
		}
		else
		{
			TIM1_overflow_262ms();//if button is pressed the Leds will blink faster!
			TIM1_overflow_interrupt_enable();
			
		}

        
    }

    // Will never reach this
    return 0;
}


ISR(TIMER1_OVF_vect)
{	
    GPIO_toggle(&PORTB,LEDs_array[LED]);

	if(LED==0) //check for PB5
	{
		move=0; // it has to move down
	}else if(LED==3)
	{
		move=1; // it has to move up 
	}
	if(move==0) // moving in down direction 
	{
		LED++; 
		
	}
	else if(move==1)// moving in up direction
	{
		LED--;
	}
    GPIO_toggle(&PORTB,LEDs_array[LED]);
}


