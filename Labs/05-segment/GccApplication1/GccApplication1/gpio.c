

			/********************************************//**
			*         Nadir Osman Al-Wattar
							gpio.c
			 ***********************************************/
			
/* Includes ----------------------------------------------------------*/
#include "gpio.h"


/* Function definitions ----------------------------------------------*/
void GPIO_config_output(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name | (1<<pin_num);
}

/*--------------------------------------------------------------------*/
/* GPIO_config_input_nopull */

/*--------------------------------------------------------------------*/
void GPIO_config_input_pullup(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
    *reg_name++;                    // Change pointer to Data Register(if we increment the pointer then the pointer point the PORT register)
    *reg_name = *reg_name | (1<<pin_num);   // Data Register 
}

void GPIO_config_input_nopull(volatile uint8_t *reg_name, uint8_t pin_num)
{
  *reg_name = *reg_name & ~(1<<pin_num);  // Data Direction Register
  *reg_name++;                    // Change pointer to Data Register(if we increment the pointer then the pointer point the PORT register)
  *reg_name = *reg_name & ~(1<<pin_num);   // Data Register
}
/*--------------------------------------------------------------------*/

void GPIO_write_low(volatile uint8_t *reg_name, uint8_t pin_num)
{
    *reg_name = *reg_name & ~(1<<pin_num);// Clear bit (and not)
}

/*--------------------------------------------------------------------*/
/* GPIO_write_high */
void GPIO_write_high (volatile uint8_t *reg_name, uint8_t pin_num)
{
	 *reg_name = *reg_name | (1<<pin_num);// Set bit
}

/*--------------------------------------------------------------------*/
/* GPIO_toggle */

void GPIO_toggle (volatile uint8_t *reg_name, uint8_t pin_num)
{
 *reg_name = *reg_name ^ (1<<pin_num);	//Toggle bit(XOR)
}
/*--------------------------------------------------------------------*/
/* GPIO_read */

uint8_t GPIO_read(volatile uint8_t *reg_name, uint8_t pin_num)
{
   
	
	 if (bit_is_set(*reg_name,pin_num))
	{
	
	    return 1;// if the button is not pressed it returns the value 1
	} 	
	
	else
	{
		return 0; // if the button is pressed it returns the value 0
	}
}
