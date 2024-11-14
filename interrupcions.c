/**
 * @file interruptions.c
 * @brief File to manage interruptions in the project
 * 
*/


#include "LPC17xx.h"
<<<<<<< Updated upstream
#include "lpc17xx_exti.h"    /* External interrupt handling */

/* Pin Definitions */
#define FREQ_PIN ((uint32_t)(1 << 10))  /* P2.10 connected to switch */
#define SCALE_PIN ((uint32_t)(1 << 10))  /* P2.11 connected to switch */
=======
#include "lpc17xx_exti.h"   
#include "lpc17xx_adc.h"
#include "gpio.c"

/* Pin Definitions */
#define FREQ_PIN ((uint32_t)(1 << 10))  /* P2.10 connected to switch */
>>>>>>> Stashed changes

/* GPIO Direction Definitions */
#define INPUT  0
#define OUTPUT 1

/* Boolean Values */
#define TRUE  1
#define FALSE 0

<<<<<<< Updated upstream
=======
/* Variables */ 
volatile uint8_t adc_current_channel = 0;

>>>>>>> Stashed changes
/* Function prototypes */

/**
 * @brief Initialize the external interrupt
 */
void configure_external_interrupt(void);

/**
 * @brief Overwrite the interrupt handle routine for GPIO (EINT0)
 * Exchanges the ADC Channel that shows in the output
 */
void EINT0_IRQHandler(void);

/**
<<<<<<< Updated upstream
 * @brief Overwrite the interrupt handle routine for GPIO (EINT1)
 * Changes the scale 
 */
void EINT1_IRQHandler(void);
=======
 * @brief Overwrite the interrupt handle routine for GPIO (EINT3)
 *  
 */
void EINT3_IRQHandler(void);
>>>>>>> Stashed changes



void configure_external_interrupt(void)
{
    EXTI_InitTypeDef exti_cfg;
    
    /* Configure EINT0 as falling edge */
	exti_cfg.EXTI_Line = EXTI_EINT0;
	exti_cfg.EXTI_Mode = EXTI_MODE_EDGE_SENSITIVE;
	exti_cfg.EXTI_polarity = EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE;
	EXTI_Config(&exti_cfg);

<<<<<<< Updated upstream
    /* Configure EINT1 as falling edge */
    exti_cfg.EXTI_Line = EXTI_EINT1;
    EXTI_Config(&exti_cfg);
=======
>>>>>>> Stashed changes
}	

// Overwrite the interrupt handle routine for EINT0
void EINT0_IRQHandler(void)
{
<<<<<<< Updated upstream
    EXTI_ClearEXTIFlag(EXTI_EINT0); /* Clear the interrupt flag */
    
}

// Overwrite the interrupt handle routine for EINT1
void EINT0_IRQHandler(void)
{
    EXTI_ClearEXTIFlag(EXTI_EINT1); /* Clear the interrupt flag */
=======
    // Alterna el canal entre 0 y 1
    adc_current_channel = (adc_current_channel == 0) ? 1 : 0;
    
    // Cambia el canal del ADC
    ADC_ChannelCmd(LPC_ADC, adc_current_channel, ENABLE);  // Activa el nuevo canal
    ADC_ChannelCmd(LPC_ADC, !adc_current_channel, DISABLE);  // Desactiva el canal anterior
    
    toggle_leds();

    EXTI_ClearEXTIFlag(EXTI_EINT0); /* Clear the interrupt flag */
}

// Overwrite the interrupt handle routine for EINT3
void EINT3_IRQHandler(void)
{
    EXTI_ClearEXTIFlag(EXTI_EINT3); /* Clear the interrupt flag */
>>>>>>> Stashed changes
    
}

