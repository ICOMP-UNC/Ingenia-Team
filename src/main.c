/**
 * @file main.c
 * @brief Main Function in our project
 * Compiles all the different files and calls its functions to deliver the project.
 */

#include "LPC17xx.h"
#include "gpio.h"
#include "systick.h"
#include "timers.h"
#include "uart.h"
#include "dac.h"
#include "adc.h"
#include "interruptions.h"
#include "gdma.h"
#include "lpc17xx_gpdma.h"


/**
 * @brief Main Function
 */
int main(void)
{
	SystemInit();                /* Initialize system clock */
    configure_ports();            /* Configures GPIO ports */
    configure_systick();			/* Configures the SysTick module */
    configure_timer();				/* Configures the Timer module */
    configure_external_interrupt(); /* Configures External Interrupt module */
    setup_dac();                 /* Configures the DAC module */
    dma_setup();                 /* Initializes the DMA module */
    configure_adc();             /* Configures the ADC module */
    uart_init();                 /* Initializes the UART module */

    systick_enable();			/* Enables SysTick interrupts */


    GPDMA_ChannelCmd(1, ENABLE);  /* Activates the DAC channel with DMA */


    while (1)
        {
            __WFI();  // Espera una interrupción (bajo consumo)
        }

    return 0;
}

