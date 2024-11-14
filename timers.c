/**
 * @file timers.c
 * @brief File to handle the timers module, it uses Timer2 with match
 * to save the ADC value of channel 0 at that moment and saves it into a 100 object index.
 */

#include "LPC17xx.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_adc.h"

/* Definir parámetros */
#define TRIGGER_RATE_HZ 30  // Frecuencia de la señal de trigger en Hz
#define MAX_SAMPLES 100     // Numero maximo de muestras a almacenar

/* Declarar arreglo de muestras */
uint16_t adc_samples[MAX_SAMPLES]; // Arreglo para almacenar los últimos 100 valores del ADC
uint8_t sample_index = 0;          // Indice para gestionar las muestras

/* Configures Timer2 */
void configure_timer_for_trigger(void);

/* Timer2 Interruption Handler Function */
void TIMER2_IRQHandler(void);

/* Function to handle trigger and save the data into an index */
void handle_trigger(void);

void configure_timer_for_trigger(void)
{
    TIM_TIMERCFG_Type timerConfig;
    TIM_MATCHCFG_Type matchConfig;

    // Timer Configuration
    timerConfig.PrescaleOption = TIM_PRESCALE_USVAL;
    timerConfig.PrescaleValue = 1;
    TIM_Init(LPC_TIM2, TIM_TIMER_MODE, &timerConfig);

    // Match configuration to generate interruptions at TRIGGER_RATE_HZ
    matchConfig.MatchChannel = 0;
    matchConfig.IntOnMatch = ENABLE;
    matchConfig.ResetOnMatch = ENABLE;
    matchConfig.StopOnMatch = DISABLE;
    matchConfig.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;  
    matchConfig.MatchValue = 1000000 / TRIGGER_RATE_HZ;  // Calculates the match for the desired frequency
    TIM_ConfigMatch(LPC_TIM2, &matchConfig);

    // Enables Timer2 Interruption
    NVIC_EnableIRQ(TIMER2_IRQn);

    // Starts the timer
    TIM_Cmd(LPC_TIM2, ENABLE);
}


void TIMER2_IRQHandler(void)
{
     // Clears the interruption flag
    TIM_ClearIntPending(LPC_TIM2, TIM_MR0_INT);
    
    // Calls the function
    handle_trigger();
}

void handle_trigger(void)
{
    // Reads ADC value of the channel 0 
    uint16_t adc_value = ADC_ChannelGetData(LPC_ADC, ADC_CHANNEL_0);

    // Stores the read value into an index
    adc_samples[sample_index] = adc_value;

    // Increases the index
    sample_index++;

    // If we've reached the limit, restarts the index to 0
    if (sample_index == MAX_SAMPLES)
    {
        sample_index = 0;  // Volver a empezar desde el inicio del arreglo
    }
}

