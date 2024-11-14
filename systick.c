/**
 * @file systick.c
 * @brief File that handles systick module in the project, generates an interrumption
 * as a way to make the channel selection LEDs blink with a 200ms frequency
*/

#include "LPC17xx.h"
#include "lpc17xx_systick.h" 
#include "lpc17xx_adc.h"

/* Pin Definitions */
#define RED_LED_PIN    ((uint32_t)(1 << 0))   /* Define the pin for the red LED */
#define GREEN_LED_PIN  ((uint32_t)(1 << 1))   /* Define the pin for the green LED */

/* Define time variables */
#define SYSTICK_TIME 200 /* Expressed in milliseconds */

/* Function Prototypes */
/**
* @brief Basic configuration for the Systick module
*/
void configure_systick(void);

/**
* @brief Overwrites the interrumption handler
*/
void SysTick_Handler(void);


void configure_systick()
{
    SYSTICK_InternalInit(SYSTICK_TIME); /* Initialize the SysTick timer with a time interval of 200 ms */
}

// Overwrite the interrupt handler routine for SysTick
void SysTick_Handler(void)
{
    SYSTICK_ClearCounterFlag(); /* Clear interrupt flag */

    // Check if the RED LED should toggle (only if ADC channel 0 is active)
    if (ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_0, 1))  // Verifies if channel 0 is active
    {
        if (GPIO_ReadValue(PINSEL_PORT_0) & RED_LED_PIN)
        {
            GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN); /* Turn off Red LED */
        }
        else
        {
            GPIO_SetValue(PINSEL_PORT_0, RED_LED_PIN); /* Turn on Red LED */
        }
    }

    // Check if the GREEN LED should toggle (only if ADC channel 1 is active)
    if (ADC_ChannelGetStatus(LPC_ADC, ADC_CHANNEL_1, 1))  // Verifies if channel 1 is active
    {
        if (GPIO_ReadValue(PINSEL_PORT_0) & GREEN_LED_PIN)
        {
            GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN); /* Turn off Green LED */
        }
        else
        {
            GPIO_SetValue(PINSEL_PORT_0, GREEN_LED_PIN); /* Turn on Green LED */
        }
    }
}