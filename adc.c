/**
 * @file adc.c
 * @brief  this file handles the ADC module configuracion and features
*/

#include "LPC17xx.h"
#include "lpc17xx_adc.h"    /* ADC */

/* Pin Definitions */
#define ADC_CHANNEL_0 ((uint32_t)(1 << 23)) /* P0.23 connected to ADC Channel 0 */
#define ADC_CHANNEL_1 ((uint32_t)(1 << 24)) /* P0.24 connected to ADC Channel 1 */

/* GPIO Direction Definitions */
#define INPUT  0
#define OUTPUT 1

/* Define frequency variables */
#define ADC_FREQ 100000 /* 100 kHz */

/* Boolean Values */
#define TRUE  1
#define FALSE 0

static uint32_t adc_read_value = 0;

/**
 * @brief Configure the ADC to sample the signal to measure at 100 kHz.
 */
void configure_adc(void)
{
    ADC_Init(LPC_ADC, ADC_FREQ); /* Initialize the ADC peripheral with a 100 kHz sampling frequency */
    ADC_ChannelCmd(LPC_ADC, ADC_CHANNEL_0, ENABLE); /* Enable ADC channel 0 */
    ADC_IntConfig(LPC_ADC, ADC_CHANNEL_0, ENABLE); /* Enable interrupt for ADC channel 0 */
}

// ----------------- Interrupt Handler Functions -----------------

/**
 * @brief ADC Interrupt Handler.
 *        
 */
void ADC_IRQHandler()
{
    NVIC_DisableIRQ(ADC_IRQn); /* Disable the ADC interrupt */
    /*
    *   Code goes here
    *
    * */
    NVIC_EnableIRQ(ADC_IRQn); /* Enable the ADC interrupt */
}