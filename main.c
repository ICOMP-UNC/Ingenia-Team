/**
 * @file main.c
 * @brief Funcion principal de nuestro programa
 * Se encarga de adjuntar todos los diferentes modulos y llamar a sus funciones 
 */

#include "LPC17xx.h"
#include "gpio.c"
#include "dac.c"
#include "adc.c"
#include "interruptions.c"
#include "gdma.c"
#include "uart.c"


/**
 * @brief Funcion principal
 */
int main(void)
{
    SystemInit();                /* Initialize system clock */
    configure_ports();            /* Configuro los puertos GPIO */
    configure_adc();             /* Configuro el modulo ADC */
    setup_dac();                 /* Configuro el modulo DAC */
    dma_setup();                 /* Inicializo el modulo DMA */
    uart_init();                 /* Inicializo el modulo UART */

    while (1)
    {
        transfer_adc_to_uart(0);  // Envía datos del canal ADC predeterminado (0) por UART
    }

    return 0;
}