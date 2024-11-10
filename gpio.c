/** 
 * @file gpio.c
 * @brief Configure the ports that are going to be use in this project.
 * There's two GPIO pins, P0.0 and P0.1, on each one there's an LED, 
 * and two External Interrupt pins P2.10 and P2.11, to interact with the ADC module.
*/

#include "LPC17xx.h"
#include "lpc17xx_gpio.h"   /* GPIO handling */
#include "lpc17xx_pinsel.h" /* Pin function selection */

/* Pin Definitions */
#define CHANNEL_PIN   ((uint32_t)(1 << 10)) /* P2.10 connected to button */
#define SCALE_PIN ((uint32_t)(1 << 11))  /* P2.11 connected to button */
#define RED_LED_PIN ((uint32_t)(1 << 0))  /* P0.0 connected to Red LED */
#define GREEN_LED_PIN ((uint32_t)(1 << 1))  /* P0.1 connected to Green LED */


/* GPIO Direction Definitions */
#define INPUT  0
#define OUTPUT 1

/* Boolean Values */
#define TRUE  1
#define FALSE 0

/**
 * @brief Initialize the GPIO peripheral
 *
 */
void configure_ports(void)
{
    PINSEL_CFG_Type pin_cfg; /* Create a variable to store the configuration of the pin */

    /* Configure the pin P0.0 as GPIO */
    pin_cfg.Portnum = PINSEL_PORT_0;           /* The port number is 0 */
    pin_cfg.Pinnum = PINSEL_PIN_0;            /* The pin number is 0 */
    pin_cfg.Funcnum = PINSEL_FUNC_0;           /* The function number is 0 */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLUP;   /* The pin mode is pull-up */
    pin_cfg.OpenDrain = PINSEL_PINMODE_NORMAL; /* The pin is in the normal mode */
    PINSEL_ConfigPin(&pin_cfg);

    /* Configure the pin P0.1 as GPIO */
    pin_cfg.Pinnum = PINSEL_PIN_1;            /* The pin number is 0 */
    PINSEL_ConfigPin(&pin_cfg);

    /* Configure the pin P0.26 as DAC */
    pin_cfg.Pinnum = PINSEL_PIN_26;            /* The pin number is 26 */
    pin_cfg.Funcnum = PINSEL_FUNC_2;           /* The function number is 2 */
    pin_cfg.Pinmode = PINSEL_PINMODE_TRISTATE;   /* The pin mode is nor pull-up or pull-down */
    PINSEL_ConfigPin(&pin_cfg);
     
    /* Configure the pin P2.10 as EINT0 */
    pin_cfg.Portnum = PINSEL_PORT_2;           /* The port number is 2 */
    pin_cfg.Pinnum = PINSEL_PIN_10;            /* The pin number is 10 */
    pin_cfg.Funcnum = PINSEL_FUNC_1;           /* The function number is 1 */
    pin_cfg.Pinmode = PINSEL_PINMODE_PULLUP;   /* The pin mode is pull-up */
    PINSEL_ConfigPin(&pin_cfg);

    /* Configure the pin P2.10 as EINT1 */
    pin_cfg.Pinnum = PINSEL_PIN_11;            /* The pin number is 11 */
    PINSEL_ConfigPin(&pin_cfg);

    /* Set the pins as P.0 and P0.1 as outputs */
    GPIO_SetDir(PINSEL_PORT_0, RED_LED_PIN | GREEN_LED_PIN, OUTPUT);  
}


/**
 * @brief function to toggle between one or the other LED
 * as a way to know what ADC channel or oscilloscope channel is active.
 */
void toggle_leds(void){
    if (GPIO_ReadValue(PINSEL_PORT_0) & RED_LED_PIN)
    {
        GPIO_ClearValue(PINSEL_PORT_0, RED_LED_PIN); /* Turn off Red LED */
        GPIO_SetValue(PINSEL_PORT_0, GREEN_LED_PIN); /* Turn on Green LED */
    }
    else
    {
        GPIO_ClearValue(PINSEL_PORT_0, GREEN_LED_PIN); /* Turn off Green LED */
        GPIO_SetValue(PINSEL_PORT_0, RED_LED_PIN); /* Turn on Red LED */
    }

}
